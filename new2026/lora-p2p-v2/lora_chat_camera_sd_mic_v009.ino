/*
 * LoRa P2P Chat + Camera + SD Card + Microphone     v009
 * XIAO ESP32-S3 Sense + Wio-SX1262
 *
 * Needs the <RadioLib.h> library.
 * Board package 3.0.0 or newer (tested on 3.0.7).
 * Tools --> USB CDC Enable On Boot --> Enabled
 * Tools --> PSRAM --> OPI PSRAM
 * Needs all 8 wires from the LoRa module connected to the XIAO.
 *
 * Shared SPI bus (LoRa + SD):
 *   SCK  = GPIO 7  (D8)
 *   MISO = GPIO 8  (D9)
 *   MOSI = GPIO 9  (D10)
 * Chip selects:
 *   LoRa NSS = D3
 *   SD CS    = GPIO 21 (B2B connector internal pin)
 * Microphone (onboard PDM): CLK = GPIO 42, DATA = GPIO 41 (no conflict)
 *
 * Commands:
 *   @photo        : Take a photo and save /test.jpg
 *   @mic [sec]    : Record microphone to /sample.wav (default 5 s, max 10 s)
 *   @<num>        : Switch channel live
 *   @name <name>  : Set call sign
 *   @encrypt on   : Enable AES-256-GCM encryption
 *   @encrypt off  : Disable encryption
 *   @seed <pass>  : Set encryption passphrase (use a long one!)
 *   @stats        : View statistics
 *   @help         : Show commands
 *   <text>        : Broadcast message
 *
 * Encrypted packet format (binary):
 *   [0xA9][12-byte random nonce][ciphertext][16-byte GCM tag]
 *   Key = 10,000 rounds of SHA-256 stretching of the passphrase.
 *   Wrong passphrase or tampered packets fail authentication and are rejected.
 *
 * NOTE: v009 encryption is NOT compatible with the older v00x shift cipher.
 * NOTE: LoRa receive is paused while recording (about 5 s); packets that
 *       arrive during a recording may be missed.
 */

// ============================================================
// LIBRARIES
// ============================================================

#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>

#include "esp_camera.h"
#include "ESP_I2S.h"
#include "FS.h"
#include "SD.h"

#include "mbedtls/gcm.h"
#include "mbedtls/sha256.h"


// ============================================================
// DEFINES
// ============================================================

// LoRa pins
#define LORA_SCK    D8
#define LORA_MISO   D9
#define LORA_MOSI   D10
#define LORA_NSS    D3
#define LORA_RST    D2
#define LORA_BUSY   D1
#define LORA_DIO1   D0

// Camera pins (XIAO ESP32-S3 Sense)
#define PWDN_GPIO_NUM   -1
#define RESET_GPIO_NUM  -1
#define XCLK_GPIO_NUM   10
#define SIOD_GPIO_NUM   40
#define SIOC_GPIO_NUM   39
#define Y9_GPIO_NUM     48
#define Y8_GPIO_NUM     11
#define Y7_GPIO_NUM     12
#define Y6_GPIO_NUM     14
#define Y5_GPIO_NUM     16
#define Y4_GPIO_NUM     18
#define Y3_GPIO_NUM     17
#define Y2_GPIO_NUM     15
#define VSYNC_GPIO_NUM  38
#define HREF_GPIO_NUM   47
#define PCLK_GPIO_NUM   13

// Camera settings
#define CAM_HMIRROR       1
#define CAM_VFLIP         1
#define CAM_BRIGHTNESS    1
#define CAM_AE_LEVEL      1
#define CAM_WARMUP_FRAMES 3

// SD card
#define SD_CS 21

// Microphone
#define MIC_CLK_PIN         42
#define MIC_DATA_PIN        41
#define MIC_SAMPLE_RATE     16000
#define MIC_DEFAULT_SECONDS 5
#define MIC_MAX_SECONDS     10
#define MIC_FILE            "/sample.wav"

// Serial / message sizes
#define MAX_MSG 200

// Encrypted packet layout
#define PKT_MAGIC      0xA9
#define PKT_NONCE_LEN  12
#define PKT_TAG_LEN    16
#define PKT_OVERHEAD   (1 + PKT_NONCE_LEN + PKT_TAG_LEN)
#define PKT_MAX        255

// Key derivation
#define KEY_SALT       "maker100-lora-v009"
#define KEY_ROUNDS     10000


// ============================================================
// FORWARD DECLARATIONS (functions)
// ============================================================

void IRAM_ATTR setFlag(void);
void myDeriveKey(void);
bool myEncryptPacket(const char *myPlain, uint8_t *myOut, size_t *myOutLen);
bool myDecryptPacket(const uint8_t *myIn, size_t myInLen, char *myOut, size_t myOutMax);
bool myCameraInit(void);
bool mySDInit(void);
void myTakePhoto(void);
void myRecordMic(int mySeconds);
void printMenu(void);
void printStats(void);
void mySendMessage(const char *myText);
void myHandleCommand(char *myCmd);
void myHandleReceive(void);
void myHandleSerial(void);


// ============================================================
// GLOBAL VARIABLES (all declared here, before any function)
// ============================================================

SX1262 radio = new Module(LORA_NSS, LORA_DIO1, LORA_RST, LORA_BUSY);

I2SClass myI2S;

volatile bool operationDone = false;
bool transmitFlag = false;
bool mySDavailable = false;

char lineBuf[MAX_MSG + 1];
int lineLen = 0;

float myBaseFreq = 915.0;
int myChannel = 0;
char myCallsign[20] = "Node";

bool myEncryptEnabled = false;
char myEncryptionSeed[32] = "maker100";
uint8_t myKey[32];

unsigned long myTxCount = 0;
unsigned long myRxCount = 0;
unsigned long myErrCount = 0;


// ============================================================
// LORA INTERRUPT
// ============================================================

void IRAM_ATTR setFlag(void) {
  operationDone = true;
}


// ============================================================
// ENCRYPTION  (AES-256-GCM via mbedtls, built into ESP32 core)
// ============================================================

void myDeriveKey(void) {
  uint8_t myHash[32];
  uint8_t myTmp[96];
  size_t mySaltLen = strlen(KEY_SALT);
  size_t mySeedLen = strlen(myEncryptionSeed);

  // First hash: salt || passphrase
  memcpy(myTmp, KEY_SALT, mySaltLen);
  memcpy(myTmp + mySaltLen, myEncryptionSeed, mySeedLen);
  mbedtls_sha256(myTmp, mySaltLen + mySeedLen, myHash, 0);

  // Stretch: hash = SHA256(hash || passphrase)
  for (int i = 0; i < KEY_ROUNDS; i++) {
    memcpy(myTmp, myHash, 32);
    memcpy(myTmp + 32, myEncryptionSeed, mySeedLen);
    mbedtls_sha256(myTmp, 32 + mySeedLen, myHash, 0);
  }

  memcpy(myKey, myHash, 32);
}


bool myEncryptPacket(const char *myPlain, uint8_t *myOut, size_t *myOutLen) {
  size_t myLen = strlen(myPlain);

  if (myLen + PKT_OVERHEAD > PKT_MAX) {
    return false;
  }

  myOut[0] = PKT_MAGIC;

  uint8_t *myNonce = myOut + 1;
  uint8_t *myCipher = myOut + 1 + PKT_NONCE_LEN;
  uint8_t *myTag = myCipher + myLen;

  // Fresh random 96-bit nonce for every packet
  for (int i = 0; i < PKT_NONCE_LEN; i += 4) {
    uint32_t myRand = esp_random();
    memcpy(myNonce + i, &myRand, 4);
  }

  mbedtls_gcm_context myCtx;
  mbedtls_gcm_init(&myCtx);

  int myRc = mbedtls_gcm_setkey(&myCtx, MBEDTLS_CIPHER_ID_AES, myKey, 256);

  if (myRc == 0) {
    myRc = mbedtls_gcm_crypt_and_tag(
      &myCtx,
      MBEDTLS_GCM_ENCRYPT,
      myLen,
      myNonce, PKT_NONCE_LEN,
      myOut, 1,                          // header byte is authenticated
      (const uint8_t *)myPlain,
      myCipher,
      PKT_TAG_LEN,
      myTag
    );
  }

  mbedtls_gcm_free(&myCtx);

  if (myRc != 0) {
    return false;
  }

  *myOutLen = myLen + PKT_OVERHEAD;
  return true;
}


bool myDecryptPacket(const uint8_t *myIn, size_t myInLen, char *myOut, size_t myOutMax) {
  if (myInLen < PKT_OVERHEAD || myIn[0] != PKT_MAGIC) {
    return false;
  }

  size_t myCipherLen = myInLen - PKT_OVERHEAD;

  if (myCipherLen + 1 > myOutMax) {
    return false;
  }

  const uint8_t *myNonce = myIn + 1;
  const uint8_t *myCipher = myIn + 1 + PKT_NONCE_LEN;
  const uint8_t *myTag = myCipher + myCipherLen;

  mbedtls_gcm_context myCtx;
  mbedtls_gcm_init(&myCtx);

  int myRc = mbedtls_gcm_setkey(&myCtx, MBEDTLS_CIPHER_ID_AES, myKey, 256);

  if (myRc == 0) {
    myRc = mbedtls_gcm_auth_decrypt(
      &myCtx,
      myCipherLen,
      myNonce, PKT_NONCE_LEN,
      myIn, 1,
      myTag, PKT_TAG_LEN,
      myCipher,
      (uint8_t *)myOut
    );
  }

  mbedtls_gcm_free(&myCtx);

  if (myRc != 0) {
    return false;
  }

  myOut[myCipherLen] = '\0';
  return true;
}


// ============================================================
// CAMERA INIT
// ============================================================

bool myCameraInit(void) {
  Serial.println(F("[CAM] Starting camera..."));

  camera_config_t myConfig = {};

  myConfig.ledc_channel = LEDC_CHANNEL_0;
  myConfig.ledc_timer = LEDC_TIMER_0;

  myConfig.pin_d0 = Y2_GPIO_NUM;
  myConfig.pin_d1 = Y3_GPIO_NUM;
  myConfig.pin_d2 = Y4_GPIO_NUM;
  myConfig.pin_d3 = Y5_GPIO_NUM;
  myConfig.pin_d4 = Y6_GPIO_NUM;
  myConfig.pin_d5 = Y7_GPIO_NUM;
  myConfig.pin_d6 = Y8_GPIO_NUM;
  myConfig.pin_d7 = Y9_GPIO_NUM;

  myConfig.pin_xclk = XCLK_GPIO_NUM;
  myConfig.pin_pclk = PCLK_GPIO_NUM;
  myConfig.pin_vsync = VSYNC_GPIO_NUM;
  myConfig.pin_href = HREF_GPIO_NUM;

  myConfig.pin_sccb_sda = SIOD_GPIO_NUM;
  myConfig.pin_sccb_scl = SIOC_GPIO_NUM;

  myConfig.pin_pwdn = PWDN_GPIO_NUM;
  myConfig.pin_reset = RESET_GPIO_NUM;

  myConfig.xclk_freq_hz = 20000000;
  myConfig.pixel_format = PIXFORMAT_JPEG;
  myConfig.frame_size = FRAMESIZE_240X240;
  myConfig.jpeg_quality = 12;
  myConfig.fb_count = 1;

  esp_err_t myCamErr = esp_camera_init(&myConfig);

  if (myCamErr != ESP_OK) {
    Serial.printf("[CAM] Camera init FAILED: 0x%x\n", myCamErr);
    return false;
  }

  sensor_t *mySensor = esp_camera_sensor_get();

  if (mySensor != NULL) {
    mySensor->set_hmirror(mySensor, CAM_HMIRROR);
    mySensor->set_vflip(mySensor, CAM_VFLIP);
    mySensor->set_brightness(mySensor, CAM_BRIGHTNESS);
    mySensor->set_ae_level(mySensor, CAM_AE_LEVEL);
  }

  // Camera warmup
  for (int myCount = 0; myCount < CAM_WARMUP_FRAMES; myCount++) {
    camera_fb_t *myWarmupFrame = esp_camera_fb_get();

    if (myWarmupFrame) {
      esp_camera_fb_return(myWarmupFrame);
    }

    delay(30);
  }

  Serial.println(F("[CAM] Camera initialized"));
  return true;
}


// ============================================================
// SD INIT
// ============================================================

bool mySDInit(void) {
  Serial.println(F("[SD] Starting SD card..."));

  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  // Explicitly deselect LoRa while initializing the SD card
  pinMode(LORA_NSS, OUTPUT);
  digitalWrite(LORA_NSS, HIGH);

  delay(100);

  mySDavailable = SD.begin(SD_CS, SPI, 400000, "/sd", 5, false);

  if (!mySDavailable) {
    SD.end();
    Serial.println(F("[SD] No SD card - continuing without it"));
    return false;
  }

  Serial.println(F("[SD] SD card mounted successfully"));

  uint64_t myCardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("[SD] Card size: %llu MB\n", (unsigned long long)myCardSize);

  return true;
}


// ============================================================
// TAKE PHOTO
// ============================================================

void myTakePhoto(void) {
  Serial.println(F("[PHOTO] Taking photo..."));

  if (!mySDavailable) {
    Serial.println(F("[PHOTO] ERROR: SD card is not available"));
    return;
  }

  camera_fb_t *myFb = esp_camera_fb_get();

  if (!myFb) {
    Serial.println(F("[PHOTO] ERROR: Camera capture failed"));
    return;
  }

  Serial.printf("[PHOTO] JPEG size: %u bytes\n", (unsigned)myFb->len);

  // Deselect LoRa before SD activity
  digitalWrite(LORA_NSS, HIGH);

  if (SD.exists("/test.jpg")) {
    SD.remove("/test.jpg");
  }

  File myFile = SD.open("/test.jpg", FILE_WRITE);

  if (!myFile) {
    Serial.println(F("[PHOTO] ERROR: Could not create /test.jpg"));
    esp_camera_fb_return(myFb);
    return;
  }

  size_t myJpegSize = myFb->len;
  size_t myWritten = myFile.write(myFb->buf, myJpegSize);

  myFile.close();
  esp_camera_fb_return(myFb);

  Serial.printf("[PHOTO] Written: %u bytes\n", (unsigned)myWritten);

  if (myWritten == myJpegSize) {
    Serial.println(F("[SUCCESS] /test.jpg saved to SD card"));
  } else {
    Serial.println(F("[ERROR] JPEG was not completely written"));
  }
}


// ============================================================
// RECORD MICROPHONE TO SD (WAV)
// ============================================================

void myRecordMic(int mySeconds) {
  Serial.println(F("[MIC] Starting microphone..."));

  if (!mySDavailable) {
    Serial.println(F("[MIC] ERROR: SD card is not available"));
    return;
  }

  if (mySeconds < 1) {
    mySeconds = 1;
  }

  if (mySeconds > MIC_MAX_SECONDS) {
    mySeconds = MIC_MAX_SECONDS;
  }

  myI2S.setPinsPdmRx(MIC_CLK_PIN, MIC_DATA_PIN);

  if (!myI2S.begin(I2S_MODE_PDM_RX, MIC_SAMPLE_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO)) {
    Serial.println(F("[MIC] ERROR: Failed to initialize I2S"));
    return;
  }

  Serial.printf("[MIC] Recording %d seconds (LoRa receive paused)...\n", mySeconds);

  size_t myWavSize = 0;
  uint8_t *myWavBuffer = myI2S.recordWAV(mySeconds, &myWavSize);

  myI2S.end();

  if (myWavBuffer == NULL || myWavSize == 0) {
    Serial.println(F("[MIC] ERROR: Recording failed (is OPI PSRAM enabled?)"));
    return;
  }

  Serial.printf("[MIC] Recorded %u bytes\n", (unsigned)myWavSize);

  // Deselect LoRa before SD activity
  digitalWrite(LORA_NSS, HIGH);

  if (SD.exists(MIC_FILE)) {
    SD.remove(MIC_FILE);
  }

  File myFile = SD.open(MIC_FILE, FILE_WRITE);

  if (!myFile) {
    Serial.println(F("[MIC] ERROR: Could not create " MIC_FILE));
    free(myWavBuffer);
    return;
  }

  size_t myWritten = myFile.write(myWavBuffer, myWavSize);

  myFile.close();
  free(myWavBuffer);

  Serial.printf("[MIC] Written: %u bytes\n", (unsigned)myWritten);

  if (myWritten == myWavSize) {
    Serial.println(F("[SUCCESS] " MIC_FILE " saved to SD card"));
  } else {
    Serial.println(F("[ERROR] WAV was not completely written"));
  }
}


// ============================================================
// SERIAL MENU
// ============================================================

void printMenu(void) {
  Serial.println(F("\n--- Serial Menu ---"));
  Serial.println(F("  @photo        : Take a photo and save /test.jpg"));
  Serial.println(F("  @mic [sec]    : Record mic to /sample.wav (default 5, max 10)"));
  Serial.println(F("  <text>        : Broadcast message"));
  Serial.println(F("  @<num>        : Switch channel"));
  Serial.println(F("  @name <name>  : Set call sign"));
  Serial.println(F("  @encrypt on   : Enable AES-256-GCM encryption"));
  Serial.println(F("  @encrypt off  : Disable encryption"));
  Serial.println(F("  @seed <pass>  : Set encryption passphrase"));
  Serial.println(F("  @stats        : View statistics"));
  Serial.println(F("  @help         : Show this menu"));
  Serial.println(F("-------------------"));
}


// ============================================================
// RADIO STATISTICS
// ============================================================

void printStats(void) {
  Serial.println(F("\n--- Radio Statistics ---"));

  Serial.print(F("  Call Sign   : "));
  Serial.println(myCallsign);

  Serial.print(F("  Channel     : "));
  Serial.print(myChannel);
  Serial.print(F(" ("));
  Serial.print(myBaseFreq + (myChannel * 0.1), 1);
  Serial.println(F(" MHz)"));

  Serial.print(F("  Encryption  : "));
  Serial.println(myEncryptEnabled ? F("ON (AES-256-GCM)") : F("OFF"));

  Serial.print(F("  Passphrase  : "));
  Serial.print(strlen(myEncryptionSeed));
  Serial.println(F(" characters"));

  Serial.print(F("  SD card     : "));
  Serial.println(mySDavailable ? F("OK") : F("not available"));

  Serial.print(F("  Sent Packets: "));
  Serial.println(myTxCount);

  Serial.print(F("  Recv Packets: "));
  Serial.println(myRxCount);

  Serial.print(F("  Error Count : "));
  Serial.println(myErrCount);

  Serial.println(F("------------------------"));
}


// ============================================================
// SEND A LORA MESSAGE
// ============================================================

void mySendMessage(const char *myText) {
  char myOutboundBuf[MAX_MSG + 32];
  uint8_t myPacket[PKT_MAX];
  size_t myPacketLen = 0;

  snprintf(myOutboundBuf, sizeof(myOutboundBuf), "%s: %s", myCallsign, myText);

  if (myEncryptEnabled) {
    if (!myEncryptPacket(myOutboundBuf, myPacket, &myPacketLen)) {
      Serial.println(F("[E] Encryption failed or message too long"));
      myErrCount++;
      return;
    }
  } else {
    myPacketLen = strlen(myOutboundBuf);
    memcpy(myPacket, myOutboundBuf, myPacketLen);
  }

  // Deselect SD before LoRa SPI activity
  digitalWrite(SD_CS, HIGH);

  radio.standby();

  Serial.print(F("[TX] Broadcasting"));
  Serial.print(myEncryptEnabled ? F(" (encrypted): ") : F(": "));
  Serial.println(myOutboundBuf);

  int myState = radio.startTransmit(myPacket, myPacketLen);

  if (myState == RADIOLIB_ERR_NONE) {
    transmitFlag = true;
    myTxCount++;
  } else {
    Serial.print(F("[E] Transmit start failed, code "));
    Serial.println(myState);
    myErrCount++;
    radio.startReceive();
  }
}


// ============================================================
// LOCAL @COMMANDS
// ============================================================

void myHandleCommand(char *myCmd) {

  if (strcasecmp(myCmd, "@help") == 0 || strcasecmp(myCmd, "@?") == 0) {
    printMenu();
  }

  else if (strcasecmp(myCmd, "@stats") == 0) {
    printStats();
  }

  else if (strcasecmp(myCmd, "@photo") == 0) {
    myTakePhoto();
  }

  else if (strncasecmp(myCmd, "@mic", 4) == 0 && (myCmd[4] == '\0' || myCmd[4] == ' ')) {
    int mySeconds = MIC_DEFAULT_SECONDS;

    if (myCmd[4] == ' ') {
      int myParsed = atoi(myCmd + 5);

      if (myParsed > 0) {
        mySeconds = myParsed;
      }
    }

    myRecordMic(mySeconds);
  }

  else if (strncasecmp(myCmd, "@name ", 6) == 0) {
    strncpy(myCallsign, myCmd + 6, sizeof(myCallsign) - 1);
    myCallsign[sizeof(myCallsign) - 1] = '\0';

    Serial.print(F("[OK] Call sign updated to: "));
    Serial.println(myCallsign);
  }

  else if (strncasecmp(myCmd, "@seed ", 6) == 0) {
    strncpy(myEncryptionSeed, myCmd + 6, sizeof(myEncryptionSeed) - 1);
    myEncryptionSeed[sizeof(myEncryptionSeed) - 1] = '\0';

    myDeriveKey();

    Serial.print(F("[OK] Passphrase updated ("));
    Serial.print(strlen(myEncryptionSeed));
    Serial.println(F(" characters)"));

    if (strlen(myEncryptionSeed) < 12) {
      Serial.println(F("[!] Short passphrase - 12+ characters recommended"));
    }
  }

  else if (strcasecmp(myCmd, "@encrypt on") == 0) {
    myEncryptEnabled = true;
    Serial.println(F("[OK] Encryption ENABLED (AES-256-GCM)"));
  }

  else if (strcasecmp(myCmd, "@encrypt off") == 0) {
    myEncryptEnabled = false;
    Serial.println(F("[OK] Encryption DISABLED"));
  }

  // Channel switch: @<number>
  else {
    char *myEndPtr;
    int myNewChannel = (int)strtol(myCmd + 1, &myEndPtr, 10);

    if (*myEndPtr == '\0' && myEndPtr != myCmd + 1 && myNewChannel >= 0) {
      myChannel = myNewChannel;

      float myNewFreq = myBaseFreq + (myChannel * 0.1);

      radio.standby();

      int myState = radio.setFrequency(myNewFreq);

      if (myState == RADIOLIB_ERR_NONE) {
        Serial.print(F("[OK] Switched live to Channel "));
        Serial.print(myChannel);
        Serial.print(F(" ("));
        Serial.print(myNewFreq, 1);
        Serial.println(F(" MHz)"));
      } else {
        Serial.print(F("[E] Frequency change failed, code "));
        Serial.println(myState);
        myErrCount++;
      }

      radio.startReceive();

    } else {
      Serial.println(F("[E] Unknown command. Type '@help' for available commands."));
    }
  }
}


// ============================================================
// SERIAL INPUT
// ============================================================

void myHandleSerial(void) {
  while (!transmitFlag && Serial.available()) {

    char myChar = (char)Serial.read();

    if (myChar == '\n') {

      if (lineLen > 0 && lineBuf[lineLen - 1] == '\r') {
        lineLen--;
      }

      if (lineLen > 0) {
        lineBuf[lineLen] = '\0';

        if (lineBuf[0] == '@') {
          myHandleCommand(lineBuf);
        } else {
          mySendMessage(lineBuf);
        }
      }

      lineLen = 0;
    }

    else if (lineLen < MAX_MSG) {
      lineBuf[lineLen++] = myChar;
    }
  }
}


// ============================================================
// RECEIVE HANDLER
// ============================================================

void myHandleReceive(void) {
  uint8_t myPacket[PKT_MAX + 1];
  char myText[PKT_MAX + 1];

  size_t myLen = radio.getPacketLength();

  if (myLen == 0 || myLen > PKT_MAX) {
    myErrCount++;
    radio.startReceive();
    return;
  }

  int myState = radio.readData(myPacket, myLen);

  if (myState == RADIOLIB_ERR_NONE) {
    myRxCount++;

    float myRssi = radio.getRSSI();
    bool myLooksEncrypted = (myLen >= PKT_OVERHEAD && myPacket[0] == PKT_MAGIC);

    if (myLooksEncrypted && myEncryptEnabled) {

      if (myDecryptPacket(myPacket, myLen, myText, sizeof(myText))) {
        Serial.print(F("[RX "));
        Serial.print(myRssi);
        Serial.print(F(" dBm, encrypted] "));
        Serial.println(myText);
      } else {
        Serial.println(F("[E] Encrypted packet rejected (wrong passphrase or tampered)"));
        myErrCount++;
      }
    }

    else if (myLooksEncrypted) {
      Serial.println(F("[RX] Encrypted packet received - type '@encrypt on' to read it"));
    }

    else {
      memcpy(myText, myPacket, myLen);
      myText[myLen] = '\0';

      Serial.print(F("[RX "));
      Serial.print(myRssi);
      Serial.print(F(" dBm"));
      Serial.print(myEncryptEnabled ? F(", PLAINTEXT - not encrypted!] ") : F("] "));
      Serial.println(myText);
    }
  }

  else if (myState != RADIOLIB_ERR_RX_TIMEOUT) {
    Serial.print(F("[E] Read error, code "));
    Serial.println(myState);
    myErrCount++;
  }

  radio.startReceive();
}


// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("XIAO ESP32-S3   v009"));
  Serial.println(F("LoRa + Camera + SD Card + Microphone"));
  Serial.println(F("========================================"));

  // Derive the AES key from the default passphrase
  myDeriveKey();

  // Shared SPI bus
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, -1);

  // Both SPI devices start deselected
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  pinMode(LORA_NSS, OUTPUT);
  digitalWrite(LORA_NSS, HIGH);

  // 1. SD card
  mySDInit();

  // 2. Camera
  myCameraInit();

  // 3. Re-establish shared SPI bus (SD / camera init may alter pin state)
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, -1);
  digitalWrite(SD_CS, HIGH);

  // 4. LoRa
  Serial.print(F("[SX1262] Initializing ... "));

  int state = radio.begin(myBaseFreq + (myChannel * 0.1));

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    myErrCount++;

    while (true) {
      delay(10);
    }
  }

  radio.setTCXO(1.8);
  radio.setDio2AsRfSwitch(true);
  radio.setBandwidth(125.0);
  radio.setSpreadingFactor(9);
  radio.setCodingRate(7);
  radio.setOutputPower(22);
  radio.setSyncWord(0x3444);
  radio.setDio1Action(setFlag);

  state = radio.startReceive();

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("[RX] Starting to listen ... success!"));
  } else {
    Serial.print(F("[E] RX start failed, code "));
    Serial.println(state);
    myErrCount++;
  }

  transmitFlag = false;

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("SYSTEM READY"));
  Serial.println(F("========================================"));
  Serial.println(F("Type @photo to take a picture"));
  Serial.println(F("Type @mic to record 5 seconds of audio"));
  Serial.println(F("Type @help for commands"));
  Serial.println(F("Type text to send by LoRa"));
  Serial.println(F("========================================"));
}


// ============================================================
// LOOP
// ============================================================

void loop() {

  myHandleSerial();

  if (operationDone) {
    operationDone = false;

    if (transmitFlag) {
      Serial.println(F("[OK] Sent!"));
      transmitFlag = false;
      radio.startReceive();
    } else {
      myHandleReceive();
    }
  }

  delay(5);
}
