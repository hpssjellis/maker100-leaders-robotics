#include <Arduino.h>
#include <esp_sleep.h>

// Can only use serial monitor for debugging when not usinging deep sleep.
// Could use Serial1 pins if we really need serial monitor. 

#define MY_LED_PIN LED_BUILTIN
#define MY_LED_ON LOW
#define MY_LED_OFF HIGH
#define MY_USE_SLEEP true   // true no serial monitor, false serial monitor debugging.


void mySleepSeconds(uint64_t mySeconds) {
  if (MY_USE_SLEEP) {
    esp_sleep_enable_timer_wakeup(mySeconds * 1000000ULL);
    esp_light_sleep_start();
  } else {
    delay(mySeconds * 1000UL);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(MY_LED_PIN, OUTPUT);
  digitalWrite(MY_LED_PIN, MY_LED_OFF);
  delay(2000);
  Serial.println("ESP32-S3 starting...");
}

void loop() {
  digitalWrite(MY_LED_PIN, MY_LED_ON);
  mySleepSeconds(1);
  int myAnalogReading = analogRead(A0);
  Serial.println("A0 reading: " + String(myAnalogReading));
  Serial.flush();
  digitalWrite(MY_LED_PIN, MY_LED_OFF);
  mySleepSeconds(3);
}
