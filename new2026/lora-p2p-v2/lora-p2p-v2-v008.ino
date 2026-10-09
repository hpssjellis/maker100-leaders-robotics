/*    DRAFT FOR BETTER PIN POSITIONS
 * LoRa P2P Chat + Camera + SD Card
 * This is a test if these things can work together.
 * Needs the <RadioLib.h> library
 * Tools --> USB CDC Enable On Boot needs to be enabled.
 * Tools --> PSRAM --> OPI PSRAM
 * Needs all the pins from the lora module connected properly to the xiao esp32s3 board. Needs 8 wires
 * ------------------------------------------------------------
 * XIAO ESP32-S3 Sense + Wio-SX1262
 *
 * Shared SPI bus:
 *   SCK  = GPIO 7        // D8 (Shared with SD card SPI)
 *   MISO = GPIO 8        // D9 (Shared with SD card SPI)
 *   MOSI = GPIO 9        // D10 (Shared with SD card SPI)
 *
 * Separate chip-select pins:
 *   LoRa NSS = GPIO 2    D3  was  // D1 - Chip Select
 *   SD CS    = GPIO 21    // using the B2B connector internal pin
 *
 * Commands:
 *   @photo        : Take a photo and save /test.jpg
 *   @<num>        : Switch channel live
 *   @name <name>  : Set call sign
 *   @encrypt on   : Enable encryption
 *   @encrypt off  : Disable encryption
 *   @seed <pass>  : Set encryption seed
 *   @stats        : View statistics
 *   @help         : Show commands
 *   <text>        : Broadcast message
 */

// ============================================================
// LIBRARIES
// ============================================================

#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>

#include "esp_camera.h"
#include "FS.h"
#include "SD.h"


// ============================================================
// LORA EXTERNAL PIN MAPPING (Avoids Camera GPIO 39/40 conflict)
// ============================================================
#define LORA_SCK    D8     //    7           // D8 (Shared with SD card SPI)
#define LORA_MISO   D9     //    8           // D9 (Shared with SD card SPI)
#define LORA_MOSI   D10    //    9           // D10 (Shared with SD card SPI)
#define LORA_NSS    D3     //   was  D1      //    2           // D1 - Chip Select
#define LORA_RST    D2     //   was  RADIOLIB_NC               // was Not wired
#define LORA_BUSY   D1     //   was  D3      //     4           // D3 - Busy status line
#define LORA_DIO1   D0     //   was  D6      //     43          // D6 - Interrupt / DIO1 line  main reason Tools --> USB CDC Enable On Boot needs to be enabled.


// ============================================================
// LORA RADIO
// ============================================================

SX1262 radio = new Module(
  LORA_NSS,
  LORA_DIO1,
  LORA_RST,
  LORA_BUSY
);


// ============================================================
// CAMERA PINS
// XIAO ESP32-S3 Sense
// ============================================================

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


// ============================================================
// CAMERA SETTINGS
// ============================================================

#define CAM_HMIRROR       1
#define CAM_VFLIP         1
#define CAM_BRIGHTNESS    1
#define CAM_AE_LEVEL      1
#define CAM_WARMUP_FRAMES 3


// ============================================================
// SD CARD
// ============================================================

#define SD_CS 21


// ============================================================
// FLAGS
// ============================================================

volatile bool operationDone = false;

bool transmitFlag = false;

bool mySDavailable = false;


// ============================================================
// SERIAL BUFFER
// ============================================================

#define MAX_MSG 200

char lineBuf[MAX_MSG + 1];

int lineLen = 0;


// ============================================================
// RADIO SETTINGS
// ============================================================

float myBaseFreq = 915.0;

int myChannel = 0;

char myCallsign[20] = "Node";


// ============================================================
// ENCRYPTION
// ============================================================

bool myEncryptEnabled = false;

char myEncryptionSeed[32] = "maker100";


// ============================================================
// STATISTICS
// ============================================================

unsigned long myTxCount = 0;

unsigned long myRxCount = 0;

unsigned long myErrCount = 0;


// ============================================================
// LORA INTERRUPT
// ============================================================

#if defined(ESP8266) || defined(ESP32)

  ICACHE_RAM_ATTR

#endif

void setFlag(void) {

  operationDone = true;
}


// ============================================================
// SIMPLE ASCII ENCRYPTION
// ============================================================

void applyEncryption(
  char *myBuf,
  bool myIsEncrypt
) {

  int mySeedLen =
    strlen(myEncryptionSeed);

  if (mySeedLen == 0) {
    return;
  }


  for (
    int i = 0;
    myBuf[i] != '\0';
    i++
  ) {

    char c = myBuf[i];


    if (
      c >= 32 &&
      c <= 126
    ) {

      int myShift =
        myEncryptionSeed[
          i % mySeedLen
        ] % 95;


      if (!myIsEncrypt) {

        myShift = -myShift;

      }


      c =
        32 +
        (
          c -
          32 +
          myShift +
          95
        ) % 95;


      myBuf[i] = c;
    }
  }
}


// ============================================================
// CAMERA INIT
// ============================================================

bool myCameraInit() {

  Serial.println(
    F("[CAM] Starting camera...")
  );


  camera_config_t myConfig = {};


  myConfig.ledc_channel =
    LEDC_CHANNEL_0;

  myConfig.ledc_timer =
    LEDC_TIMER_0;


  myConfig.pin_d0 =
    Y2_GPIO_NUM;

  myConfig.pin_d1 =
    Y3_GPIO_NUM;

  myConfig.pin_d2 =
    Y4_GPIO_NUM;

  myConfig.pin_d3 =
    Y5_GPIO_NUM;

  myConfig.pin_d4 =
    Y6_GPIO_NUM;

  myConfig.pin_d5 =
    Y7_GPIO_NUM;

  myConfig.pin_d6 =
    Y8_GPIO_NUM;

  myConfig.pin_d7 =
    Y9_GPIO_NUM;


  myConfig.pin_xclk =
    XCLK_GPIO_NUM;

  myConfig.pin_pclk =
    PCLK_GPIO_NUM;

  myConfig.pin_vsync =
    VSYNC_GPIO_NUM;

  myConfig.pin_href =
    HREF_GPIO_NUM;


  myConfig.pin_sccb_sda =
    SIOD_GPIO_NUM;

  myConfig.pin_sccb_scl =
    SIOC_GPIO_NUM;


  myConfig.pin_pwdn =
    PWDN_GPIO_NUM;

  myConfig.pin_reset =
    RESET_GPIO_NUM;


  myConfig.xclk_freq_hz =
    20000000;


  myConfig.pixel_format =
    PIXFORMAT_JPEG;


  myConfig.frame_size =
    FRAMESIZE_240X240;


  myConfig.jpeg_quality =
    12;


  myConfig.fb_count = 1;


  esp_err_t myCamErr =
    esp_camera_init(
      &myConfig
    );


  if (
    myCamErr != ESP_OK
  ) {

    Serial.printf(
      "[CAM] Camera init FAILED: 0x%x\n",
      myCamErr
    );

    return false;
  }


  sensor_t *mySensor =
    esp_camera_sensor_get();


  if (mySensor != NULL) {

    mySensor->set_hmirror(
      mySensor,
      CAM_HMIRROR
    );

    mySensor->set_vflip(
      mySensor,
      CAM_VFLIP
    );

    mySensor->set_brightness(
      mySensor,
      CAM_BRIGHTNESS
    );

    mySensor->set_ae_level(
      mySensor,
      CAM_AE_LEVEL
    );
  }


  // Camera warmup

  for (
    int myCount = 0;
    myCount < CAM_WARMUP_FRAMES;
    myCount++
  ) {

    camera_fb_t *myWarmupFrame =
      esp_camera_fb_get();


    if (myWarmupFrame) {

      esp_camera_fb_return(
        myWarmupFrame
      );
    }


    delay(30);
  }


  Serial.println(
    F("[CAM] Camera initialized")
  );


  return true;
}


// ============================================================
// SD INIT
// ============================================================

bool mySDInit() {

  Serial.println(
    F("[SD] Starting SD card...")
  );


  // SD chip select

  pinMode(
    SD_CS,
    OUTPUT
  );

  digitalWrite(
    SD_CS,
    HIGH
  );


  // IMPORTANT:
  // Explicitly deselect LoRa while
  // initializing the SD card.

  pinMode(
    LORA_NSS,
    OUTPUT
  );

  digitalWrite(
    LORA_NSS,
    HIGH
  );


  delay(100);


  /*
   * Shared SPI bus:
   *
   * GPIO7  = SCK
   * GPIO8  = MISO
   * GPIO9  = MOSI
   *
   * SD CS = GPIO21
   * LoRa NSS = GPIO2
   */


  mySDavailable =
    SD.begin(
      SD_CS,
      SPI,
      400000,
      "/sd",
      5,
      false
    );


  if (!mySDavailable) {

    SD.end();


    Serial.println(
      F("[SD] No SD card - continuing without it")
    );


    return false;
  }


  Serial.println(
    F("[SD] SD card mounted successfully")
  );


  uint64_t myCardSize =
    SD.cardSize() /
    (1024 * 1024);


  Serial.printf(
    "[SD] Card size: %llu MB\n",
    (unsigned long long)myCardSize
  );


  return true;
}


// ============================================================
// TAKE PHOTO
// ============================================================

void myTakePhoto() {

  Serial.println(
    F("[PHOTO] Taking photo...")
  );


  if (!mySDavailable) {

    Serial.println(
      F("[PHOTO] ERROR: SD card is not available")
    );

    return;
  }


  camera_fb_t *myFb =
    esp_camera_fb_get();


  if (!myFb) {

    Serial.println(
      F("[PHOTO] ERROR: Camera capture failed")
    );

    return;
  }


  Serial.printf(
    "[PHOTO] JPEG size: %u bytes\n",
    (unsigned)myFb->len
  );


  if (
    SD.exists("/test.jpg")
  ) {

    SD.remove(
      "/test.jpg"
    );
  }


  File myFile =
    SD.open(
      "/test.jpg",
      FILE_WRITE
    );


  if (!myFile) {

    Serial.println(
      F("[PHOTO] ERROR: Could not create /test.jpg")
    );


    esp_camera_fb_return(
      myFb
    );


    return;
  }


  size_t myJpegSize =
    myFb->len;


  size_t myWritten =
    myFile.write(
      myFb->buf,
      myJpegSize
    );


  myFile.close();


  esp_camera_fb_return(
    myFb
  );


  Serial.printf(
    "[PHOTO] Written: %u bytes\n",
    (unsigned)myWritten
  );


  if (
    myWritten ==
    myJpegSize
  ) {

    Serial.println(
      F("[SUCCESS] /test.jpg saved to SD card")
    );

  } else {

    Serial.println(
      F("[ERROR] JPEG was not completely written")
    );
  }
}


// ============================================================
// SERIAL MENU
// ============================================================

void printMenu() {

  Serial.println(
    F("\n--- Serial Menu ---")
  );


  Serial.println(
    F("  @photo        : Take a photo and save /test.jpg")
  );


  Serial.println(
    F("  <text>        : Broadcast message")
  );


  Serial.println(
    F("  @<num>        : Switch channel")
  );


  Serial.println(
    F("  @name <name>  : Set call sign")
  );


  Serial.println(
    F("  @encrypt on   : Enable encryption")
  );


  Serial.println(
    F("  @encrypt off  : Disable encryption")
  );


  Serial.println(
    F("  @seed <pass>  : Set encryption password")
  );


  Serial.println(
    F("  @stats        : View statistics")
  );


  Serial.println(
    F("  @help         : Show this menu")
  );


  Serial.println(
    F("-------------------")
  );
}


// ============================================================
// RADIO STATISTICS
// ============================================================

void printStats() {

  Serial.println(
    F("\n--- Radio Statistics ---")
  );


  Serial.print(
    F("  Call Sign   : ")
  );

  Serial.println(
    myCallsign
  );


  Serial.print(
    F("  Channel     : ")
  );

  Serial.print(
    myChannel
  );


  Serial.print(
    F(" (")
  );


  Serial.print(
    myBaseFreq +
    (myChannel * 0.1),
    1
  );


  Serial.println(
    F(" MHz)")
  );


  Serial.print(
    F("  Encryption  : ")
  );


  Serial.println(
    myEncryptEnabled ?
    F("ON") :
    F("OFF")
  );


  Serial.print(
    F("  Seed        : ")
  );


  Serial.println(
    myEncryptionSeed
  );


  Serial.print(
    F("  Sent Packets: ")
  );


  Serial.println(
    myTxCount
  );


  Serial.print(
    F("  Recv Packets: ")
  );


  Serial.println(
    myRxCount
  );


  Serial.print(
    F("  Error Count : ")
  );


  Serial.println(
    myErrCount
  );


  Serial.println(
    F("------------------------")
  );
}


// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(
    115200
  );


  delay(500);


  Serial.println();
  Serial.println();


  Serial.println(
    F("========================================")
  );


  Serial.println(
    F("XIAO ESP32-S3")
  );


  Serial.println(
    F("LoRa + Camera + SD Card")
  );


  Serial.println(
    F("Shared SPI Bus")
  );


  Serial.println(
    F("========================================")
  );


  // ==========================================================
  // INITIALIZE SHARED SPI BUS
  // ==========================================================

  SPI.begin(
    LORA_SCK,
    LORA_MISO,
    LORA_MOSI,
    -1
  );


  // Make sure both SPI devices start deselected.

  pinMode(
    SD_CS,
    OUTPUT
  );

  digitalWrite(
    SD_CS,
    HIGH
  );


  pinMode(
    LORA_NSS,
    OUTPUT
  );

  digitalWrite(
    LORA_NSS,
    HIGH
  );


  // ==========================================================
  // 1. SD CARD
  // ==========================================================

  mySDInit();


  // ==========================================================
  // 2. CAMERA
  // ==========================================================

  myCameraInit();


  // ==========================================================
  // 3. RE-ESTABLISH SHARED SPI BUS
  // ==========================================================

  /*
   * SD and camera initialization may alter peripheral state.
   *
   * Re-establish the SPI pins before starting LoRa.
   */

  SPI.begin(
    LORA_SCK,
    LORA_MISO,
    LORA_MOSI,
    -1
  );


  // Make sure SD is deselected before LoRa starts.

  digitalWrite(
    SD_CS,
    HIGH
  );


  // ==========================================================
  // 4. LORA
  // ==========================================================

  Serial.print(
    F("[SX1262] Initializing ... ")
  );


  int state =
    radio.begin(
      myBaseFreq +
      (myChannel * 0.1)
    );


  if (
    state ==
    RADIOLIB_ERR_NONE
  ) {

    Serial.println(
      F("success!")
    );

  } else {

    Serial.print(
      F("failed, code ")
    );

    Serial.println(
      state
    );


    myErrCount++;


    while (true) {

      delay(10);
    }
  }


  // Radio settings

  radio.setTCXO(
    1.8
  );


  radio.setDio2AsRfSwitch(
    true
  );


  radio.setBandwidth(
    125.0
  );


  radio.setSpreadingFactor(
    9
  );


  radio.setCodingRate(
    7
  );


  radio.setOutputPower(
    22
  );


  radio.setSyncWord(
    0x3444
  );


  radio.setDio1Action(
    setFlag
  );


  // ==========================================================
  // START RECEIVE
  // ==========================================================

  state =
    radio.startReceive();


  if (
    state ==
    RADIOLIB_ERR_NONE
  ) {

    Serial.println(
      F("[RX] Starting to listen ... success!")
    );

  } else {

    Serial.print(
      F("[E] RX start failed, code ")
    );


    Serial.println(
      state
    );


    myErrCount++;
  }


  transmitFlag = false;


  Serial.println();


  Serial.println(
    F("========================================")
  );


  Serial.println(
    F("SYSTEM READY")
  );


  Serial.println(
    F("========================================")
  );


  Serial.println(
    F("Type @photo to take a picture")
  );


  Serial.println(
    F("Type @help for commands")
  );


  Serial.println(
    F("Type text to send by LoRa")
  );


  Serial.println(
    F("========================================")
  );
}


// ============================================================
// LOOP
// ============================================================

void loop() {

  // ==========================================================
  // 1. SERIAL INPUT
  // ==========================================================

  while (
    !transmitFlag &&
    Serial.available()
  ) {

    char myChar =
      (char)Serial.read();


    // --------------------------------------------------------
    // END OF LINE
    // --------------------------------------------------------

    if (
      myChar == '\n'
    ) {

      if (
        lineLen > 0 &&
        lineBuf[lineLen - 1] == '\r'
      ) {

        lineLen--;
      }


      if (
        lineLen > 0
      ) {

        lineBuf[lineLen] =
          '\0';


        // ====================================================
        // LOCAL COMMANDS
        // ====================================================

        if (
          lineBuf[0] == '@'
        ) {


          // --------------------------------------------------
          // HELP
          // --------------------------------------------------

          if (
            strcasecmp(
              lineBuf,
              "@help"
            ) == 0 ||

            strcasecmp(
              lineBuf,
              "@?"
            ) == 0
          ) {

            printMenu();
          }


          // --------------------------------------------------
          // STATS
          // --------------------------------------------------

          else if (
            strcasecmp(
              lineBuf,
              "@stats"
            ) == 0
          ) {

            printStats();
          }


          // --------------------------------------------------
          // PHOTO
          // --------------------------------------------------

          else if (
            strcasecmp(
              lineBuf,
              "@photo"
            ) == 0
          ) {

            myTakePhoto();
          }


          // --------------------------------------------------
          // NAME
          // --------------------------------------------------

          else if (
            strncasecmp(
              lineBuf,
              "@name ",
              6
            ) == 0
          ) {

            strncpy(
              myCallsign,
              lineBuf + 6,
              sizeof(myCallsign) - 1
            );


            myCallsign[
              sizeof(myCallsign) - 1
            ] = '\0';


            Serial.print(
              F("[OK] Call sign updated to: ")
            );


            Serial.println(
              myCallsign
            );
          }


          // --------------------------------------------------
          // ENCRYPTION SEED
          // --------------------------------------------------

          else if (
            strncasecmp(
              lineBuf,
              "@seed ",
              6
            ) == 0
          ) {

            strncpy(
              myEncryptionSeed,
              lineBuf + 6,
              sizeof(myEncryptionSeed) - 1
            );


            myEncryptionSeed[
              sizeof(myEncryptionSeed) - 1
            ] = '\0';


            Serial.print(
              F("[OK] Encryption seed updated to: ")
            );


            Serial.println(
              myEncryptionSeed
            );
          }


          // --------------------------------------------------
          // ENCRYPT ON
          // --------------------------------------------------

          else if (
            strcasecmp(
              lineBuf,
              "@encrypt on"
            ) == 0
          ) {

            myEncryptEnabled = true;


            Serial.println(
              F("[OK] Encryption ENABLED")
            );
          }


          // --------------------------------------------------
          // ENCRYPT OFF
          // --------------------------------------------------

          else if (
            strcasecmp(
              lineBuf,
              "@encrypt off"
            ) == 0
          ) {

            myEncryptEnabled = false;


            Serial.println(
              F("[OK] Encryption DISABLED")
            );
          }


          // --------------------------------------------------
          // CHANNEL
          // --------------------------------------------------

          else {

            char *myEndPtr;


            int myNewChannel =
              (int)strtol(
                lineBuf + 1,
                &myEndPtr,
                10
              );


            if (
              *myEndPtr == '\0' &&
              myNewChannel >= 0
            ) {

              myChannel =
                myNewChannel;


              float myNewFreq =
                myBaseFreq +
                (myChannel * 0.1);


              radio.standby();


              int myState =
                radio.setFrequency(
                  myNewFreq
                );


              if (
                myState ==
                RADIOLIB_ERR_NONE
              ) {

                Serial.print(
                  F("[OK] Switched live to Channel ")
                );


                Serial.print(
                  myChannel
                );


                Serial.print(
                  F(" (")
                );


                Serial.print(
                  myNewFreq,
                  1
                );


                Serial.println(
                  F(" MHz)")
                );

              } else {

                Serial.print(
                  F("[E] Frequency change failed, code ")
                );


                Serial.println(
                  myState
                );


                myErrCount++;
              }


              radio.startReceive();

            } else {

              Serial.println(
                F("[E] Unknown command. Type '@help' for available commands.")
              );
            }
          }
        }


        // ====================================================
        // REGULAR LORA MESSAGE
        // ====================================================

        else {

          char myOutboundBuf[
            MAX_MSG + 32
          ];


          snprintf(
            myOutboundBuf,
            sizeof(myOutboundBuf),
            "%s: %s",
            myCallsign,
            lineBuf
          );


          if (
            myEncryptEnabled
          ) {

            applyEncryption(
              myOutboundBuf,
              true
            );
          }


          // Deselect SD before LoRa SPI activity.

          digitalWrite(
            SD_CS,
            HIGH
          );


          radio.standby();


          Serial.print(
            F("[TX] Broadcasting: ")
          );


          Serial.println(
            myOutboundBuf
          );


          int myState =
            radio.startTransmit(
              myOutboundBuf
            );


          if (
            myState ==
            RADIOLIB_ERR_NONE
          ) {

            transmitFlag = true;

            myTxCount++;

          } else {

            Serial.print(
              F("[E] Transmit start failed, code ")
            );


            Serial.println(
              myState
            );


            myErrCount++;


            radio.startReceive();
          }
        }
      }


      lineLen = 0;
    }


    // ========================================================
    // STORE CHARACTER
    // ========================================================

    else if (
      lineLen < MAX_MSG
    ) {

      lineBuf[
        lineLen++
      ] = myChar;
    }
  }


  // ==========================================================
  // 2. RADIO COMPLETION
  // ==========================================================

  if (
    operationDone
  ) {

    operationDone = false;


    // ========================================================
    // TRANSMIT COMPLETE
    // ========================================================

    if (
      transmitFlag
    ) {

      Serial.println(
        F("[OK] Sent!")
      );


      transmitFlag = false;


      radio.startReceive();
    }


    // ========================================================
    // RECEIVE COMPLETE
    // ========================================================

    else {

      String myReceivedString;


      int myState =
        radio.readData(
          myReceivedString
        );


      if (
        myState ==
        RADIOLIB_ERR_NONE
      ) {

        myRxCount++;


        char myRxBuf[
          MAX_MSG + 32
        ];


        myReceivedString.toCharArray(
          myRxBuf,
          sizeof(myRxBuf)
        );


        if (
          myEncryptEnabled
        ) {

          applyEncryption(
            myRxBuf,
            false
          );
        }


        Serial.print(
          F("[RX ")
        );


        Serial.print(
          radio.getRSSI()
        );


        Serial.print(
          F(" dBm] ")
        );


        Serial.println(
          myRxBuf
        );

      }


      else if (
        myState !=
        RADIOLIB_ERR_RX_TIMEOUT
      ) {

        Serial.print(
          F("[E] Read error, code ")
        );


        Serial.println(
          myState
        );


        myErrCount++;
      }


      radio.startReceive();
    }
  }


  delay(5);
}
