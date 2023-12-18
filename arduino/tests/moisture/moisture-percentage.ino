// ESP32 pin that connects to AOUT pin of moisture sensor
const byte MOISTURE_PIN = -1;

// Calibrated values
const int dry = -1;
const int wet = -1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    int value = analogRead(MOISTURE_PIN);

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
