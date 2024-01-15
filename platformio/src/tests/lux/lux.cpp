// Test lux sensor
#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>
#include <config.h>

// define the wiring settings for I2C interface connection.
const int SCL_PIN = config.SCL_PIN;
const int SDA_PIN = config.SDA_PIN;

BH1750 lightMeter;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
}

void loop() {
    float lux = lightMeter.readLightLevel();
    Serial.print("Amount of Light: ");
    Serial.print(lux);
    Serial.println(" lux");
    delay(1000);
}
