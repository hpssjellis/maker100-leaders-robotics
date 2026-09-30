/*
  Maker100 Robotics - WebSerial Game Controller
  serial-v001

  XIAO ESP32-S3 / Seeed-style wiring:
    D6 = push button to 3V3
    D5 = external LED through resistor to GND
    Built-in LED is also used

  Browser protocol:
    ESP32 -> webpage: LEFT
    webpage -> ESP32: HIT
    webpage -> ESP32: RESET

  The ESP32 is the physical input/output device.
  The webpage is responsible for the game logic.
*/

#include <Arduino.h>

const int myButtonPin = D6;
const int myLedPin = D5;

bool myLastButtonState = false;
bool myLedState = false;

void mySetLed(bool myState) {
  myLedState = myState;

  // XIAO built-in LED is commonly active LOW.
  digitalWrite(LED_BUILTIN, myState ? LOW : HIGH);

  // External LED on D5 is active HIGH.
  digitalWrite(myLedPin, myState ? HIGH : LOW);
}

void mySendButtonCommand() {
  Serial.println("LEFT");
}

void myHandleSerialCommand(String myCommand) {
  myCommand.trim();
  myCommand.toUpperCase();

  if (myCommand == "HIT") {
    mySetLed(true);
    Serial.println("LED_ON");
  }

  if (myCommand == "RESET") {
    mySetLed(false);
    Serial.println("LED_OFF");
  }

  if (myCommand == "PING") {
    Serial.println("PONG");
  }
}

void myReadSerial() {
  if (Serial.available()) {
    String myCommand = Serial.readStringUntil('\n');
    myHandleSerialCommand(myCommand);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(myLedPin, OUTPUT);
  pinMode(myButtonPin, INPUT_PULLDOWN);

  mySetLed(false);

  Serial.begin(115200);
  delay(500);

  Serial.println("SERIAL_V001_READY");
}

void loop() {
  myReadSerial();

  bool myButtonState = digitalRead(myButtonPin);

  // Send only once when the button changes from released to pressed.
  if (myButtonState && !myLastButtonState) {
    mySendButtonCommand();
  }

  myLastButtonState = myButtonState;

  delay(10);
}
