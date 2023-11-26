// Toggle built-in LED via MQTT for home asssitant

#include <PubSubClient.h>
#include <WiFi.h>

// Wifi Setup
const char *ssid = "ssid";
const char *password = "password";

// MQTT Setup
const char *mqtt_server = "mqtt_server_ip";
const char *mqtt_topic_set = "mqtt_topic_set";
const char *mqtt_topic_get = "mqtt_topic_get";
const char *mqtt_user = "mqtt_user";
const char *mqtt_password = "mqtt_password";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    connectWIFI();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    connectMQTT();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Not connected to WiFi");
        connectWIFI();
    }
    if (!client.connected()) {
        Serial.println("Not connected to MQTT");
        connectMQTT();
    }
    client.loop();
}

void connectWIFI() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi, IP address: ");
    Serial.println(WiFi.localIP());
}

void connectMQTT() {
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
            Serial.println("Connected to MQTT");
            client.subscribe(mqtt_topic_set);
            client.subscribe(mqtt_topic_get);
        } else {
            Serial.println("Failed, rc=");
            Serial.println(client.state());
            Serial.println("Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.println("Message arrived on topic: " + String(topic));

    if (String(topic) == mqtt_topic_set) {
        if (payload[0] == '1') {
            digitalWrite(LED_BUILTIN, LOW);
            Serial.println("LED turned ON");
            client.publish(mqtt_topic_get, String(!digitalRead(LED_BUILTIN)).c_str(), true);
            Serial.println("Send State: ON");
        } else if (payload[0] == '0') {
            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("LED turned OFF");
            client.publish(mqtt_topic_get, String(!digitalRead(LED_BUILTIN)).c_str(), true);
            Serial.println("Send State: OFF");
        }
    }
}
