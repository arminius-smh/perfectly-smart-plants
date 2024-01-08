#include <Arduino.h>
#include <PubSubClient.h>
#include <Update.h>
#include <WebServer.h>
#include <WiFi.h>

// Pins
const byte LED_PIN = -1;
const int MOISTURE_PIN = -1;

// Wifi
const char *ssid = "ssid";
const char *password = "password";

// MQTT Broker
const char *mqtt_client_id = "mqtt_client_id";
const char *mqtt_server = "mqtt_server";
const char *mqtt_topic = "mqtt_topic";
const char *mqtt_user = "mqtt_user";
const char *mqtt_password = "1123";
const int mqtt_port = 1883;

// Calibrated values
const int dry = -1;
const int wet = -1;

// miscellaneous setup
const int THRESHOLD = 35;
int LEDSTATE = 0;
WiFiClient espClient;
PubSubClient client(espClient);
WebServer server(80);
unsigned long previousMillisServer = 0;
unsigned long previousMillisMQTT = 0;
const long serverInterval = 1;    // Interval for handling server clients in milliseconds
const long mqttInterval = 10000;  // Interval for publishing MQTT messages in milliseconds

const char *serverIndex = "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'/><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js'></script><script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js'></script><style> body { background-color: #f8f9fa; padding: 20px; } .container { max-width: 500px; margin: 0 auto; } #prg { margin-top: 10px; }</style><div class='container'> <h2 class='mt-4 mb-4'>ESP32 Firmware Update</h2> <form method='POST' action='#' enctype='multipart/form-data' id='upload_form'> <div class='custom-file mb-3'> <input type='file' class='custom-file-input' id='update' name='update' required /> <label class='custom-file-label' for='update'>Choose firmware file</label> </div> <button type='submit' class='btn btn-primary'>Update</button> </form> <div id='prg' class='mt-3'>Progress: 0%</div></div><script> $(document).ready(function () { $('form').submit(function (e) { e.preventDefault(); var form = $('#upload_form')[0]; var data = new FormData(form); $.ajax({ url: '/update', type: 'POST', data: data, contentType: false, processData: false, xhr: function () { var xhr = new window.XMLHttpRequest(); xhr.upload.addEventListener( 'progress', function (evt) { if (evt.lengthComputable) { var per = (evt.loaded / evt.total) * 100; $('#prg').html('Progress: ' + Math.round(per) + '%'); } }, false, ); return xhr; }, success: function (d, s) { console.log('Success!'); }, error: function (a, b, c) {}, }); }); });</script>";

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
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("Not connected to WiFi");
            connectWIFI();
        }

        Serial.println("Connecting to MQTT...");

        if (client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
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

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    connectWIFI();

    client.setServer(mqtt_server, mqtt_port);
    connectMQTT();

    /*return index page which is stored in serverIndex */
    server.on("/", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", serverIndex);
    });
    /*handling uploading firmware file */
    server.on(
        "/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart(); }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %lu\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    } });
    server.begin();
}

void loop() {
    // Get the current time
    unsigned long currentMillis = millis();
    // Reconnect if failed
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Not connected to WiFi");
        connectWIFI();
    }
    if (!client.connected()) {
        Serial.println("Not connected to MQTT");
        connectMQTT();
    }

    if (currentMillis - previousMillisServer >= serverInterval) {
        server.handleClient();
        previousMillisServer = currentMillis;
    }
    if (currentMillis - previousMillisMQTT >= mqttInterval) {
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
        previousMillisMQTT = currentMillis;
    }
}
