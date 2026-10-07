/*
 * RadioLib SX126x Ping-Pong Example (Enhanced for XIAO ESP32-S3 + Wio-SX1262)
 * --------------------------------------------------------------------------
 * Node A (#define INITIATING_NODE active) sends the first ping.
 * Node B (INITIATING_NODE commented out) starts listening for packets.
 */

#include <SPI.h>
#include <RadioLib.h>

// Uncomment the following ONLY on one of the two nodes to initiate ping-pong
//#define INITIATING_NODE

// Wio-SX1262 Pin Mapping for XIAO ESP32-S3 B2B Connector
#define LORA_SCK   7
#define LORA_MISO  8
#define LORA_MOSI  9
#define LORA_NSS   41
#define LORA_RST   42
#define LORA_BUSY  40
#define LORA_DIO1  39

SX1262 radio = new Module(LORA_NSS, LORA_DIO1, LORA_RST, LORA_BUSY);

// Save transmission states between loops
int transmissionState = RADIOLIB_ERR_NONE;

// Flag to indicate transmission (true) or reception (false) state
bool transmitFlag = false;

// Flag triggered by hardware interrupt when packet is sent or received
volatile bool operationDone = false;

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
  Serial.println(F("=== SX1262 Ping-Pong Test ==="));

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

#if defined(INITIATING_NODE)
  // Send the first packet on this node
  Serial.println(F("[SX1262] Mode: INITIATING NODE (Sending first ping)"));
  Serial.print(F("[TX] Transmitting: \"Hello World!\" ... "));
  transmissionState = radio.startTransmit("Hello World!");
  if (transmissionState == RADIOLIB_ERR_NONE) {
    Serial.println(F("started."));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(transmissionState);
  }
  transmitFlag = true;
#else
  // Start listening for LoRa packets on this node
  Serial.println(F("[SX1262] Mode: RESPONDER NODE (Listening)"));
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
#endif
}

void loop() {
  // Check if the previous radio operation finished via ISR interrupt
  if (operationDone) {
    operationDone = false;

    if (transmitFlag) {
      // Previous operation was a transmission
      if (transmissionState == RADIOLIB_ERR_NONE) {
        Serial.println(F("[OK] Transmission finished successfully!"));
      } else {
        Serial.print(F("[E] Transmission failed, code "));
        Serial.println(transmissionState);
      }

      // Switch back to listening mode to await response
      Serial.println(F("[RX] Switching to receive mode..."));
      radio.startReceive();
      transmitFlag = false;

    } else {
      // Previous operation was a reception
      String str;
      int state = radio.readData(str);

      if (state == RADIOLIB_ERR_NONE) {
        Serial.println(F("[RX] Packet received successfully!"));
        Serial.print(F("     Data: "));
        Serial.println(str);
        Serial.print(F("     RSSI: "));
        Serial.print(radio.getRSSI());
        Serial.println(F(" dBm"));
        Serial.print(F("     SNR:  "));
        Serial.print(radio.getSNR());
        Serial.println(F(" dB"));
      } else {
        Serial.print(F("[E] Read data failed, code "));
        Serial.println(state);
      }

      // Brief delay before responding
      delay(1000);

      // Send response back
      Serial.print(F("[TX] Transmitting response: \"Hello World!\" ... "));
      transmissionState = radio.startTransmit("Hello World!");
      if (transmissionState == RADIOLIB_ERR_NONE) {
        Serial.println(F("started."));
      } else {
        Serial.print(F("failed, code "));
        Serial.println(transmissionState);
      }
      transmitFlag = true;
    }
  }
}
