// ESP32 pin that connects to AOUT pin of moisture sensor
const byte MOISTURE_PIN = -1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    int value = analogRead(MOISTURE_PIN);

    Serial.print("Moisture value: ");
    Serial.println(value);

    delay(500);
}
