const byte led_pin{ 9 };

byte ledState{ LOW };

void setup() {
  pinMode(led_pin, OUTPUT);
}

void loop() {
  ledState = ledState == LOW ? HIGH : LOW;
  digitalWrite(led_pin, ledState);
  delay(1000);
}