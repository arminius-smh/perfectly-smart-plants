// Test humidity, temperature and pressure sensor
#include <Adafruit_BME280.h>
#include <Arduino.h>

Adafruit_BME280 bme;
float temp = 0.00;
float hum = 0.00;
float pressure = 0.00;

void setup() {
    Serial.begin(115200);
    if (!bme.begin(0x76, &Wire)) {
        Serial.println("can NOT initialize BME280.\n");
        while (true)
            ;
    }
}

void loop() {
    temp = bme.readTemperature();
    hum = bme.readHumidity();
    pressure = bme.readPressure() / 100;  // Pa to hPa
    Serial.print("Humidity: ");
    Serial.print(String(hum));
    Serial.print("\t Temperature: ");
    Serial.print(String(temp));
    Serial.print("\tPressure: ");
    Serial.println(String(pressure));
    delay(2000);
}
