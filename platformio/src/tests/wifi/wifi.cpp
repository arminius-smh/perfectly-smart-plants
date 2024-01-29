// Connect ESP32 to WIFI
#include <Arduino.h>
#include <WiFi.h>
#include <config.h>

const char *ssid = config.wifi_ssid;
const char *password = config.wifi_password;

void connectWIFI()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi, IP address: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(115200);
    connectWIFI();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Not connected to WiFi");
        connectWIFI();
    }
}
