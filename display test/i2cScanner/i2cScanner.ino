#include <Wire.h>

// XIAO ESP32C3 I2C pins
#define SDA_PIN 6  // D4
#define SCL_PIN 7  // D5

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nXIAO ESP32C3 I2C Scanner");

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  Serial.println("Scanning I2C bus...");
}

void loop() {
  byte error;
  int devices = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);

      devices++;
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found!");
  } else {
    Serial.print("Scan complete. Found ");
    Serial.print(devices);
    Serial.println(" device(s).");
  }

  Serial.println("-------------------------");
  delay(3000);
}