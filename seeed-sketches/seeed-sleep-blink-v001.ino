#include <Arduino.h>
#include <esp_sleep.h> // Native ESP32 sleep library

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);    
}

void loop() {
  int myAnalogReading = analogRead(A0);
  Serial.println("Serial print works on the XIAO ESP32-S3. The A0 reading is: " + String(myAnalogReading));
  
  // Ensure outgoing serial data is fully sent before sleeping
  Serial.flush();

  digitalWrite(LED_BUILTIN, LOW);    // LED ON
  
  // ESP32 sleep timers take microseconds (1 second = 1,000,000 microseconds)
  esp_sleep_enable_timer_wakeup(1000ULL * 1000ULL); 
  esp_light_sleep_start();           // Enter ultra-low power light sleep for 1 second
  
  digitalWrite(LED_BUILTIN, HIGH);   // LED OFF
  
  esp_sleep_enable_timer_wakeup(3000ULL * 1000ULL); 
  esp_light_sleep_start();           // Enter ultra-low power light sleep for 3 seconds
}
