// Toggle built-in LED via MQTT for home asssitant
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <config.h>

// Setup LED pin
const int LED_PIN = config.LED_PIN;

// Wifi Setup
const char *ssid = config.wifi_ssid;
const char *password = config.wifi_password;

// MQTT Setup
const char *mqtt_server = config.mqtt_server;
const char *mqtt_topic_set = config.test_mqtt_topic_set;
const char *mqtt_topic_get = config.test_mqtt_topic_get;
const char *mqtt_user = config.mqtt_user;
const char *mqtt_password = config.mqtt_password;
const int mqtt_port = config.mqtt_port;

WiFiClient espClient;
PubSubClient client(espClient);

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

void connectMQTT()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP32Client", mqtt_user, mqtt_password))
        {
            Serial.println("Connected to MQTT");
            client.subscribe(mqtt_topic_set);
            client.subscribe(mqtt_topic_get);
        }
        else
        {
            Serial.println("Failed, rc=");
            Serial.println(client.state());
            Serial.println("Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("Message arrived on topic: " + String(topic));

    if (String(topic) == mqtt_topic_set)
    {
        if (payload[0] == '1')
        {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("LED turned ON");
            client.publish(mqtt_topic_get, String(digitalRead(LED_PIN)).c_str(), true);
            Serial.println("Send State: ON");
        }
        else if (payload[0] == '0')
        {
            digitalWrite(LED_PIN, LOW);
            Serial.println("LED turned OFF");
            client.publish(mqtt_topic_get, String(digitalRead(LED_PIN)).c_str(), true);
            Serial.println("Send State: OFF");
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    connectWIFI();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    connectMQTT();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Not connected to WiFi");
        connectWIFI();
    }
    if (!client.connected())
    {
        Serial.println("Not connected to MQTT");
        connectMQTT();
    }
    client.loop();
}
