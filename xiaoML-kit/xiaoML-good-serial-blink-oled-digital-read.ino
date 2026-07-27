#include <U8g2lib.h>
#include <Wire.h>

// Initialize the OLED display
U8G2_SSD1306_72X40_ER_1_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE);  // efficient buffer   
// u8g2.firstPage(); do { } while (u8g2.nextPage());

// U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE); // full buffer
// u8g2.sendBuffer(); // Transfer the internal memory to the display

// Use a variable to track the last time the display was updated
unsigned long previousMillis = 0;
// Set the interval for updates (e.g., 1000ms for 1 second)
const long interval = 200;

int myA0;

void setup() {
  Serial.begin(115200);
  if (!Serial) {delay(5000);}  // to give 5 seconds to plugin serial but not demand it.
  pinMode(LED_BUILTIN, OUTPUT);

  //randomSeed(analogRead(A1));

  Serial.println("XIAOML Kit - Hello World");
  Serial.println("==========================");

  u8g2.begin();

  Serial.println("✓ Display initialized");
  Serial.println("Showing Hello World message...");
}

void loop() {
  myA0 = analogRead(A0);
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the display was updated
    previousMillis = currentMillis;

    // Start the drawing sequence
    u8g2.firstPage();
    do {
      // Set font
     // u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.setFont(u8g2_font_ncenB14_tr);
    

      // Display "number" centered
      u8g2.setCursor(8, 20);
      u8g2.print("A0:"); 
      u8g2.setCursor(8, 40);
      u8g2.print(String(myA0)); 

      // random pixel
      u8g2.drawPixel(random(72), random(40));

    } while (u8g2.nextPage());

    Serial.println("A0: " + String(myA0)); 
  }

  // Your LED blink logic can be handled separately with its own timer
  static unsigned long lastBlinkMillis = 0;
  static bool ledState = LOW;
  const long blinkInterval = 200; // Blink every 200ms

  if (currentMillis - lastBlinkMillis >= blinkInterval) {
    lastBlinkMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }

  // Other tasks can be performed here without being blocked
  // For example, reading sensor data, etc.
}
