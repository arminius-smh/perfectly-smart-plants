// Test moisture sensor
#include <Arduino.h>

// ESP32 pin that connects to AOUT pin of moisture sensor
const byte MOISTURE_PIN = -1;

// Calibrated values
const int dry = -1;
const int wet = -1;

void setup() {
    Serial.begin(115200);
}

void loop() {
    int value = analogRead(MOISTURE_PIN);

    if (wet == -1 && dry == -1) {
        Serial.print("Moisture value: ");
        Serial.println(value);

        delay(500);
    } else {
        if (value < wet) {
            value = wet;
        } else if (value > dry) {
            value = dry;
        }

        int percentageHumidity = map(value, wet, dry, 100, 0);
        Serial.print(percentageHumidity);
        Serial.println("%");

        delay(500);
    }
}
