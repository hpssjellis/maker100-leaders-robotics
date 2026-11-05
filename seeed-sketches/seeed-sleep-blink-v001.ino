#include <Arduino.h>
#include <esp_sleep.h>

// Serial monitor only works when not using light sleep (USB drops during sleep).
// A0 grounded = real sleep. A0 high (or pulled up to 3V3) = serial monitor debugging.

// Pre-declared functions
void mySleepSeconds(uint64_t mySeconds);


#define MY_LED_PIN LED_BUILTIN
#define MY_LED_ON LOW
#define MY_LED_OFF HIGH
#define MY_SLEEP_THRESHOLD 5

bool myUseSleep = false;

void mySleepSeconds(uint64_t mySeconds) {
  if (myUseSleep) {
    esp_sleep_enable_timer_wakeup(mySeconds * 1000000ULL);
    esp_light_sleep_start();
  } else {
    delay(mySeconds * 1000UL);
  }
}

void setup() {
  delay(3000);
  Serial.begin(115200);
  pinMode(MY_LED_PIN, OUTPUT);
  digitalWrite(MY_LED_PIN, MY_LED_ON);
  delay(2000);
  
  digitalWrite(MY_LED_PIN, MY_LED_OFF);
  Serial.println("ESP32-S3 starting...");
  Serial.println("Watch the double blink using a delay.");
  Serial.println("When you connect A0 to GND we continue a single blink just with light sleep between blinks");
  delay(2000);
}

void loop() {
  digitalWrite(MY_LED_PIN, MY_LED_ON);
  mySleepSeconds(1);

  int myAnalogReading = analogRead(A0);
  myUseSleep = (myAnalogReading < MY_SLEEP_THRESHOLD);
  if ( ! myUseSleep ) {  //extra blink
  digitalWrite(MY_LED_PIN, MY_LED_OFF);
  mySleepSeconds(1); 
  digitalWrite(MY_LED_PIN, MY_LED_ON);
  mySleepSeconds(1);

  }



 
  digitalWrite(MY_LED_PIN, MY_LED_OFF);
  mySleepSeconds(5);
}
