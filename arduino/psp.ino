#include <PubSubClient.h>
#include <WiFi.h>

// Pins
const byte LED_PIN = -1;
const byte MOISTURE_PIN = -1;

// Wifi
const char *ssid = "ssid";
const char *password = "password";

// MQTT Broker
const char *mqtt_server = "mqtt_server";
const char *mqtt_topic = "mqtt_topic";
const char *mqtt_user = "mqtt_user";
const char *mqtt_password = "mqtt_password";
const int mqtt_port = 1883;

// Calibrated values
const int dry = -1;
const int wet = -1;

// miscellaneous setup
const int THRESHOLD = 15;
int LEDSTATE = 0;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    connectWIFI();

    client.setServer(mqtt_server, mqtt_port);
    connectMQTT();
}

void loop() {
    // Reconnect if failed
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Not connected to WiFi");
        connectWIFI();
    }
    if (!client.connected()) {
        Serial.println("Not connected to MQTT");
        connectMQTT();
    }

    // Sensor Data
    int value = analogRead(MOISTURE_PIN);
    if (value < wet) {
        value = wet;
    } else if (value > dry) {
        value = dry;
    }
    int percentageHumidity = map(value, wet, dry, 100, 0);
    Serial.print(percentageHumidity);
    Serial.println("%");

    if (percentageHumidity < THRESHOLD && LEDSTATE == 0) {
        digitalWrite(LED_PIN, HIGH);
        LEDSTATE = 1;
    } else if (percentageHumidity >= THRESHOLD && LEDSTATE == 1) {
        digitalWrite(LED_PIN, LOW);
        LEDSTATE = 0;
    }
    client.publish(mqtt_topic, String(percentageHumidity).c_str(), true);

    delay(10000);
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
            client.subscribe(mqtt_topic);
        } else {
            Serial.println("Failed, rc=");
            Serial.println(client.state());
            Serial.println("Retrying in 5 seconds...");
            delay(5000);
        }
    }
}
