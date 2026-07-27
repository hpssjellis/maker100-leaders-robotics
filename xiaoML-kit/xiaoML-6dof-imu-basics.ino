// You might have to delete the "Arduino_LSM6DS3" library and 
// Install the "Seeed Arduino LSM6DS3"

#include <LSM6DS3.h>
#include <Wire.h>

// Create IMU object using I2C interface
LSM6DS3 myIMU(I2C_MODE, 0x6A);

float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("XIAOML Kit IMU Test");
  Serial.println("LSM6DS3TR-C 6-Axis IMU");
  Serial.println("====================");

  // Initialize the IMU
  if (myIMU.begin() != 0) {
      Serial.println("ERROR: IMU initialization failed!");
      while(1) delay(1000);
  } else {
      Serial.println("✓ IMU initialized successfully");
      Serial.println("Data Format: AccelX,AccelY,AccelZ,"
                    "GyroX,GyroY,GyroZ");
      Serial.println("Units: g-force, degrees/second");
      Serial.println();
  }
}

void loop() {
  // Read accelerometer data (in g-force)
  accelX = myIMU.readFloatAccelX();
  accelY = myIMU.readFloatAccelY();
  accelZ = myIMU.readFloatAccelZ();

  // Read gyroscope data (in degrees per second)
  gyroX = myIMU.readFloatGyroX();
  gyroY = myIMU.readFloatGyroY();
  gyroZ = myIMU.readFloatGyroZ();

  // Print readable format
  Serial.print("Accel (g): X="); Serial.print(accelX, 3);
  Serial.print(" Y="); Serial.print(accelY, 3);
  Serial.print(" Z="); Serial.print(accelZ, 3);
  Serial.print(" | Gyro (°/s): X="); Serial.print(gyroX, 2);
  Serial.print(" Y="); Serial.print(gyroY, 2);
  Serial.print(" Z="); Serial.println(gyroZ, 2);

  delay(100); // 10 Hz update rate
}
