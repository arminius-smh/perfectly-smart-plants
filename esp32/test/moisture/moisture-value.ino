// ESP32 pin that connects to AOUT pin of moisture sensor
#define AOUT_PIN -1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(AOUT_PIN);
  
  Serial.print("Moisture value: ");
  Serial.println(value);
  
  delay(500);
}
