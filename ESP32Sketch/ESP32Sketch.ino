byte ledState{ LOW };

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("It's alive");
  delay(1000);
}