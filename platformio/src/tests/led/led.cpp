// Initializes and blinks the built-in LED
#include <Arduino.h>
#include <config.h>

// Setup LED pin
const int LED_PIN = config.LED_PIN;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
}
