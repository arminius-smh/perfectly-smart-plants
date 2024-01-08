// Connect ESP32 to WIFI
#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "ssid";
const char *password = "password";

void connectWIFI() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi, IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    connectWIFI();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Not connected to WiFi");
        connectWIFI();
    }
}
