/*
 * LoRa P2P Serial Chat - XIAO ESP32-S3 + Seeed Wio-SX1262
 * -----------------------------------------------------------------
 * All nodes boot directly into receive mode. Type any message in the 
 * Serial Monitor and press Enter to broadcast it to all nearby nodes.
 */

#include <SPI.h>
#include <RadioLib.h>

// Wio-SX1262 Pin Mapping for XIAO ESP32-S3 B2B Connector
#define LORA_SCK   7
#define LORA_MISO  8
#define LORA_MOSI  9
#define LORA_NSS   41
#define LORA_RST   42
#define LORA_BUSY  40
#define LORA_DIO1  39

SX1262 radio = new Module(LORA_NSS, LORA_DIO1, LORA_RST, LORA_BUSY);

// Flags and buffers
volatile bool operationDone = false;
bool transmitFlag = false;

#define MAX_MSG 200
char lineBuf[MAX_MSG + 1];
int lineLen = 0;

#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  operationDone = true;
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.println(F("=== LoRa P2P Serial Chat ==="));

  // Explicitly initialize custom SPI bus for the Wio-SX1262 module
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);

  // Initialize SX1262 radio
  Serial.print(F("[SX1262] Initializing ... "));
  int state = radio.begin();
  
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  // Configure module-specific settings required for Wio-SX1262
  radio.setTCXO(1.8);
  radio.setDio2AsRfSwitch(true);

  // Set standard radio parameters
  radio.setBandwidth(125.0);
  radio.setSpreadingFactor(9);
  radio.setCodingRate(7);
  radio.setOutputPower(22);
  radio.setSyncWord(0x3444);

  // Set interrupt action for DIO1
  radio.setDio1Action(setFlag);

  // Boot directly into receive mode
  Serial.print(F("[RX] Starting to listen ... "));
  state = radio.startReceive();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }
  
  transmitFlag = false;
  Serial.println(F("[I] Ready: type a message + Enter to broadcast."));
}

void loop() {
  // 1. Read characters from the Serial Monitor non-blockingly
  while (!transmitFlag && Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n') {
      if (lineLen > 0 && lineBuf[lineLen - 1] == '\r') lineLen--; // Handle CRLF
      if (lineLen > 0) {
        lineBuf[lineLen] = '\0';
        
        // Put radio into standby before transmitting from receive mode
        radio.standby();
        
        Serial.print(F("[TX] Broadcasting: "));
        Serial.println(lineBuf);
        
        int st = radio.startTransmit(lineBuf);
        if (st == RADIOLIB_ERR_NONE) {
          transmitFlag = true;
        } else {
          Serial.print(F("[E] Transmit start failed, code "));
          Serial.println(st);
          radio.startReceive(); // Resume listening if transmission fails to start
        }
      }
      lineLen = 0;
    } else if (lineLen < MAX_MSG) {
      lineBuf[lineLen++] = c;
    }
  }

  // 2. Handle radio completion interrupts (TX finished or RX packet received)
  if (operationDone) {
    operationDone = false;

    if (transmitFlag) {
      // Transmission completed
      Serial.println(F("[OK] Sent!"));
      transmitFlag = false;
      radio.startReceive(); // Resume listening
    } else {
      // Packet received
      String str;
      int st = radio.readData(str);
      
      if (st == RADIOLIB_ERR_NONE) {
        Serial.print(F("[RX "));
        Serial.print(radio.getRSSI());
        Serial.print(F(" dBm] "));
        Serial.println(str);
      } else if (st != RADIOLIB_ERR_RX_TIMEOUT) {
        Serial.print(F("[E] Read error, code "));
        Serial.println(st);
      }
      
      radio.startReceive(); // Resume listening
    }
  }
}
