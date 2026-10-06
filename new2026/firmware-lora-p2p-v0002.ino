/*
 * LoRa P2P Chat  -  XIAO ESP32-S3 + Seeed Wio-SX1262 (B2B connector)
 * -----------------------------------------------------------------
 * Broadcasts whatever you type in the Serial Monitor to every nearby
 * board running this same sketch, and prints everything it hears.
 *
 * HOW TO USE
 *   1. Flash two (or more) XIAO ESP32-S3 + Wio-SX1262 boards with this sketch.
 *   2. Open the Serial Monitor on each (115200 baud), USB-C cable plugged in.
 *   3. Type a line of text and press Enter -> it is sent to everyone in range.
 *   4. Incoming text shows as:  [RX <signal> dBm] <text>
 *
 * OPTIONAL PRIVACY / CHANNELS / ENCRYPTION  (compile-time settings)
 *   - CHANNEL            : pick another lane (0-9). Every 0.1 MHz step is a
 *                          separate channel; all nodes must match.
 *   - USE_PRIVATE_LINK   : uncomment to switch the LoRa sync word so radios
 *                          without the same flag will not decode you.
 *   - USE_ENCRYPTION     : uncomment + set PASSWORD to AES-256 encrypt all
 *                          messages (key = SHA-256 of PASSWORD). All nodes
 *                          must use the SAME password. Anyone else in range
 *                          only sees ciphertext (or nothing).
 *
 * Radio wiring (Wio-SX1262 stacked on the XIAO ESP32-S3 B2B connector):
 *   SPI:   SCK = GPIO7   MISO = GPIO8   MOSI = GPIO9
 *   Radio: NSS = GPIO41  RST = GPIO42   BUSY = GPIO40  DIO1 = GPIO39
 *   Module also needs: TCXO 1.8V, RF switch driven via DIO2 (set below).
 */

#include <SPI.h>
#include <RadioLib.h>

// ----------------------------------------------------------- radio pins
#define LORA_SCK   7
#define LORA_MISO  8
#define LORA_MOSI  9
#define LORA_NSS   41
#define LORA_RST   42
#define LORA_BUSY  40
#define LORA_DIO1  39

// ----------------------------------------------------------- link setup
//#define BASE_FREQ   868.5   // 868.x MHz band (EU). For US ISM use 915.0.
#define BASE_FREQ   915.0   // US ISM band 902-928 MHz
#define BANDWIDTH   125.0   // kHz: 125 / 250 / 500
#define SPREAD_FACT 9       // 7 = fast/short range .. 12 = slow/long range
#define CODING_RATE 7       // 4/5 forward error correction
#define TX_POWER    22      // dBm (module max)

// "Channel" = frequency offset in 0.1 MHz steps above BASE_FREQ.
// All nodes of a link MUST use the same channel. 0 = default / open lane.
#define CHANNEL 0

// ---- PRIVATE LINK  (uncomment to turn on) ------------------------------
// Switches the LoRa sync word to the private 0x1424 pattern; radios not
// programmed the same way will not decode this traffic.
// #define USE_PRIVATE_LINK 1

// ---- ENCRYPTION  (uncomment both lines and set your password) ----------
// AES-256 ECB + PKCS#7 padding, key = SHA-256(PASSWORD). Deliberately the
// simplest scheme; enough to hide the chat from casual listeners, NOT
// hardened crypto (repeating message lengths leak). Same password everywhere.
// #define USE_ENCRYPTION 1
// #define PASSWORD "change-me"

#define MAX_MSG   200         // max plain-text chars per message
#define TX_TIMEOUT 5000       // ms to wait for the radio to finish sending

// ----------------------------------------------------------- radio object
// RadioLib SX1262: Module(CS, DIO1, RST, BUSY)
SX1262 radio = new Module(LORA_NSS, LORA_DIO1, LORA_RST, LORA_BUSY);

volatile bool rxDone = false;
volatile bool txDone = false;

void IRAM_ATTR onRx() { rxDone = true; }
void IRAM_ATTR onTx() { txDone = true; }

#if defined(USE_ENCRYPTION) && USE_ENCRYPTION
#include "mbedtls/aes.h"
#include "mbedtls/sha256.h"
static uint8_t aesKey[32];
static int  encryptMsg(char *buf, int len);   // pad + encrypt in place
static int  decryptMsg(char *buf, int len);   // decrypt in place; -1 on fail
#endif

// ----------------------------------------------------------- radio state
static bool radioUp = false;                  // radio ready to use?
static unsigned long nextInitTry = 0;         // retry scheduler

// Bring the radio up: begin + per-module RF config. True on success.
static bool radioInit(void) {
  int st = radio.begin(BASE_FREQ + CHANNEL * 0.1);
  if (st != RADIOLIB_ERR_NONE) return false;

  radio.setTCXO(1.8);            // module uses a 1.8V TCXO: required for RX/TX
  radio.setDio2AsRfSwitch(true); // module RF switch is driven via DIO2
  radio.setBandwidth(BANDWIDTH);
  radio.setSpreadingFactor(SPREAD_FACT);
  radio.setCodingRate(CODING_RATE);
  radio.setOutputPower(TX_POWER);

#if defined(USE_PRIVATE_LINK) && USE_PRIVATE_LINK
  radio.setSyncWord(0x1424);  // private LoRa sync word
#else
  radio.setSyncWord(0x3444);  // public LoRa sync word (open lane)
#endif

  radio.setPacketSentAction(onTx);
  radio.setPacketReceivedAction(onRx);
  radio.startReceive();
  return true;
}

// ----------------------------------------------------------- sender state
// Non-blocking sender: 0 = idle, 1 = over the air. Keeps loop() snappy.
static int  txState = 0;
static unsigned long txStart = 0;

// Line buffer (head room = 16 bytes max PKCS#7 pad + NUL)
static char lineBuf[MAX_MSG + 16 + 1];
static int  lineLen = 0;

static void sendText(void);                  // defined below loop()

// ----------------------------------------------------------- setup
void setup() {
  Serial.begin(115200);
  Serial.setTxTimeoutMs(0);   // don't block the radio loop on full USB buffers
  delay(100);

  Serial.println();
  Serial.println("=== LoRa P2P Chat : XIAO ESP32-S3 + Wio-SX1262 ===");
  Serial.printf("Channel %d @ %.1f MHz | SF%d | BW%.0f kHz | %d dBm\n",
                CHANNEL, BASE_FREQ + CHANNEL * 0.1,
                (int)SPREAD_FACT, BANDWIDTH, (int)TX_POWER);

  // custom SPI pins for the stacked module
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);

#if defined(USE_ENCRYPTION) && USE_ENCRYPTION
  mbedtls_sha256((const unsigned char *)PASSWORD, strlen(PASSWORD), aesKey, 0);
  Serial.println("[I] Encryption: AES-256 ON  (same password on every node)");
#else
  Serial.println("[I] Encryption: OFF (plain text)");
#endif

#if defined(USE_PRIVATE_LINK) && USE_PRIVATE_LINK
  Serial.println("[I] Link: PRIVATE sync word enabled");
#else
  Serial.println("[I] Link: PUBLIC sync word");
#endif

  // First init attempt; on failure loop() keeps retrying every 5 s.
  if (radioInit()) {
    radioUp = true;
  } else {
    Serial.println("[E] Radio init failed - will keep retrying every 5s.");
    nextInitTry = millis() + 5000;
  }

  Serial.println("[I] Ready: type a message + Enter to broadcast to everyone.");
}

// ----------------------------------------------------------- loop
void loop() {
  // ---- keep trying to bring the radio up if it failed ----
  if (!radioUp) {
    if (millis() >= nextInitTry) {
      if (radioInit()) {
        radioUp = true;
        Serial.println("[OK] Radio initialized.");
      } else {
        Serial.println("[E] Radio init retry failed.");
        nextInitTry = millis() + 5000;
      }
    }
    return;                  // nothing else to do without the radio
  }

  // ---- SEND: grab complete lines from the Serial Monitor ----
  while (txState == 0 && Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n') {
      if (lineLen > 0 && lineBuf[lineLen - 1] == '\r') lineLen--;  // CRLF
      if (lineLen > 0) sendText();
      lineLen = 0;
    } else if (lineLen < MAX_MSG) {
      lineBuf[lineLen++] = c;                  // excess chars are dropped
    }
  }

  // ---- finish a transmit that is already over the air ----
  if (txState == 1) {
    if (txDone) {
      txDone = false;
      Serial.println("[OK] Sent");
      txState = 0;
      radio.startReceive();
    } else if (millis() - txStart >= TX_TIMEOUT) {
      Serial.println("[E] TX timeout");
      radio.standby();
      txState = 0;
      radio.startReceive();
    }
  }

  // ---- RECEIVE: a packet was heard while listening ----
  if (txState == 0 && rxDone) {
    rxDone = false;
    uint8_t rxBuf[MAX_MSG + 16 + 1];
    size_t len = sizeof(rxBuf);

    int st = radio.readData(rxBuf, len);       // radio -> standby afterwards
    if (st == RADIOLIB_ERR_NONE) {
      rxBuf[len] = '\0';
#if defined(USE_ENCRYPTION) && USE_ENCRYPTION
      int plainLen = decryptMsg((char *)rxBuf, (int)len);
      if (plainLen < 0) {
        Serial.println("[RX] decrypt failed - different password?");
      } else {
        Serial.printf("[RX %d dBm] %s\n", radio.getRSSI(), (char *)rxBuf);
      }
#else
      Serial.printf("[RX %d dBm] %s\n", radio.getRSSI(), (char *)rxBuf);
#endif
    } else {
      Serial.printf("[E] Packet error, code %d\n", st);
    }
    radio.startReceive();
  }
}

// ----------------------------------------------------------- sender
static void sendText(void) {
  int len = lineLen;

#if defined(USE_ENCRYPTION) && USE_ENCRYPTION
  len = encryptMsg(lineBuf, len);              // pad + encrypt in place
#endif

  txDone = false;
  int st = radio.startTransmit((uint8_t *)lineBuf, (size_t)len);
  if (st != RADIOLIB_ERR_NONE) {
    Serial.printf("[E] TX start failed, code %d\n", st);
    txState = 0;
    radio.startReceive();
    return;
  }
  txStart = millis();
  txState = 1;                                 // completion handled in loop()
}

// ----------------------------------------------------------- crypto
#if defined(USE_ENCRYPTION) && USE_ENCRYPTION

// PKCS#7 padding + AES-256 ECB in place; returns new (padded) length
static int encryptMsg(char *buf, int len) {
  int pad = 16 - (len % 16);                   // 1..16, so pad never equals 0
  for (int i = 0; i < pad; i++) buf[len + i] = (char)pad;

  mbedtls_aes_context ctx;
  mbedtls_aes_init(&ctx);
  mbedtls_aes_setkey_enc(&ctx, aesKey, 256);
  for (int b = 0; b < (len + pad) / 16; b++)
    mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT,
                          (unsigned char *)buf + 16 * b,
                          (unsigned char *)buf + 16 * b);
  mbedtls_aes_free(&ctx);
  return len + pad;
}

// decrypt in place, strips padding, returns plain length; -1 on failure
static int decryptMsg(char *buf, int len) {
  if (len == 0 || len % 16 != 0) return -1;

  mbedtls_aes_context ctx;
  mbedtls_aes_init(&ctx);
  mbedtls_aes_setkey_dec(&ctx, aesKey, 256);
  for (int b = 0; b < len / 16; b++)
    mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_DECRYPT,
                          (unsigned char *)buf + 16 * b,
                          (unsigned char *)buf + 16 * b);
  mbedtls_aes_free(&ctx);

  uint8_t pad = (uint8_t)buf[len - 1];
  if (pad < 1 || pad > 16) return -1;          // garbage -> wrong key / noise
  buf[len - pad] = '\0';
  return len - pad;
}

#endif
// deerflow_build_id=20261006T234831Z-7d93e6b997da-376a7ba28859
