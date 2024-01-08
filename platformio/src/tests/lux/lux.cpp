// Test lux sensor
#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>

// define the wiring settings for I2C interface connection.
#define BH1750_I2C_SCL 22
#define BH1750_I2C_SDA 21

BH1750 lightMeter;

void setup() {
    Serial.begin(115200);
    Wire.begin(BH1750_I2C_SDA, BH1750_I2C_SCL);
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
}

void loop() {
    float lux = lightMeter.readLightLevel();
    Serial.print("Amount of Light: ");
    Serial.print(lux);
    Serial.println(" lux");
    delay(1000);
}
