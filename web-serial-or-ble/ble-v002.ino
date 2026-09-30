/*
  Maker100 Robotics - WebBLE Game Controller
  ble-v002

  WHAT CHANGED FROM v001 (why the ESP32S3 was not showing up):
  1. ADVERTISING PAYLOAD OVERFLOW FIXED. v001 advertised both the
     128-bit service UUID (18 bytes) and the name "ESP32-Fusion-01"
     (17 bytes) plus flags (3 bytes) = 38 bytes. A legacy BLE
     advertising packet holds only 31 bytes, so advertising start
     failed silently and the board never went on air. This is the same
     bug fixed in esp32-v15 (its "v08" note). Now only the NAME is
     advertised. The webpage filters by namePrefix, and the GATT
     service is found after connecting, so the UUID is not needed.
  2. advertising->start() return value is now checked and printed.
  3. Advertising restarts after the browser disconnects, so you can
     reconnect without rebooting the board.
  4. Notifies are sent from loop(), not inside the BLE write callback
     (keeps the NimBLE host task happy).
  5. Simple button debounce.

  XIAO ESP32-S3 wiring:
    D6 = push button to 3V3 (internal pulldown used)
    D5 = external LED through resistor to GND
    Built-in LED is also used (active LOW)

  Browser protocol (same as v001):
    ESP32 -> webpage: LEFT      (button pressed)
    webpage -> ESP32: HIT       (turn LED on, replies LED_ON)
    webpage -> ESP32: RESET     (turn LED off, replies LED_OFF)
    webpage -> ESP32: PING      (replies PONG)

  Requires: NimBLE-Arduino by h2zero, version 2.x
*/

#include <Arduino.h>
#include <NimBLEDevice.h>

const int myButtonPin = D6;
const int myLedPin    = D5;

#define MY_BLE_SERVICE_UUID       "7e400001-b2c3-5d4e-af60-9b3c7d8eaf20"
#define MY_BLE_CONTROL_CHAR_UUID  "7e400002-b2c3-5d4e-af60-9b3c7d8eaf20"
#define MY_BLE_RESULT_CHAR_UUID   "7e400006-b2c3-5d4e-af60-9b3c7d8eaf20"

const char* myDeviceName = "ESP32-Fusion-01";

NimBLECharacteristic* myControlChar = nullptr;
NimBLECharacteristic* myResultChar  = nullptr;

// Messages waiting to be sent to the browser (sent from loop)
volatile bool myPendingSend = false;
char myPendingMessage[24] = "";

bool myLastButtonState = false;
unsigned long myLastButtonChangeMs = 0;

void mySetLed(bool myState) {
  // XIAO built-in LED is active LOW
  digitalWrite(LED_BUILTIN, myState ? LOW : HIGH);
  // External LED on D5 is active HIGH
  digitalWrite(myLedPin, myState ? HIGH : LOW);
}

// Safe to call from anywhere: just queues the message
void myQueueResult(const char* myMessage) {
  strncpy(myPendingMessage, myMessage, sizeof(myPendingMessage) - 1);
  myPendingMessage[sizeof(myPendingMessage) - 1] = '\0';
  myPendingSend = true;
}

// Only called from loop()
void myFlushResult() {
  if (!myPendingSend || !myResultChar) return;

  myPendingSend = false;
  myResultChar->setValue((const uint8_t*)myPendingMessage, strlen(myPendingMessage));
  myResultChar->notify();

  Serial.print("BLE -> WEB: ");
  Serial.println(myPendingMessage);
}

class MyServerCallbacks : public NimBLEServerCallbacks {

  void onConnect(NimBLEServer* myServer, NimBLEConnInfo& myConnInfo) override {
    Serial.println("Browser connected");
    if (myResultChar) myResultChar->setValue("BLE_V002_READY");
  }

  void onDisconnect(NimBLEServer* myServer, NimBLEConnInfo& myConnInfo, int myReason) override {
    Serial.println("Browser disconnected - advertising again");
    NimBLEDevice::getAdvertising()->start();
  }
};

class MyControlCallbacks : public NimBLECharacteristicCallbacks {

  void onWrite(NimBLECharacteristic* myCharacteristic, NimBLEConnInfo& myConnInfo) override {

    std::string myValue = myCharacteristic->getValue();
    if (myValue.length() == 0) return;

    String myCommand = String(myValue.c_str());
    myCommand.trim();
    myCommand.toUpperCase();

    Serial.print("WEB -> BLE: ");
    Serial.println(myCommand);

    if (myCommand == "HIT") {
      mySetLed(true);
      myQueueResult("LED_ON");
    }
    else if (myCommand == "RESET") {
      mySetLed(false);
      myQueueResult("LED_OFF");
    }
    else if (myCommand == "PING") {
      myQueueResult("PONG");
    }
  }
};

void myStartBLE() {

  NimBLEDevice::init(myDeviceName);

  NimBLEServer* myServer = NimBLEDevice::createServer();
  myServer->setCallbacks(new MyServerCallbacks());

  NimBLEService* myService = myServer->createService(MY_BLE_SERVICE_UUID);

  myControlChar = myService->createCharacteristic(
    MY_BLE_CONTROL_CHAR_UUID,
    NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
  );

  myResultChar = myService->createCharacteristic(
    MY_BLE_RESULT_CHAR_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
  );

  myControlChar->setCallbacks(new MyControlCallbacks());
  myResultChar->setValue("BLE_V002_READY");

  myService->start();

  // NAME ONLY in the advertising packet (see header: UUID + name > 31 bytes)
  NimBLEAdvertising* myAdvertising = NimBLEDevice::getAdvertising();
  myAdvertising->setName(myDeviceName);

  bool myOk = myAdvertising->start();

  Serial.println("BLE_V002_READY");
  Serial.print("Advertising as: ");
  Serial.println(myDeviceName);
  Serial.print("Advertising start: ");
  Serial.println(myOk ? "OK" : "FAILED");
  Serial.print("Board BLE address: ");
  Serial.println(NimBLEDevice::getAddress().toString().c_str());
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(myLedPin, OUTPUT);
  pinMode(myButtonPin, INPUT_PULLDOWN);

  mySetLed(false);

  Serial.begin(115200);
  delay(500);

  myStartBLE();
}

void loop() {

  bool myButtonState = digitalRead(myButtonPin);

  // Send once per press, with a 30 ms debounce
  if (myButtonState != myLastButtonState && millis() - myLastButtonChangeMs > 30) {
    myLastButtonChangeMs = millis();
    myLastButtonState = myButtonState;

    if (myButtonState) {
      myQueueResult("LEFT");
    }
  }

  myFlushResult();

  delay(10);
}
