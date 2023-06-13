byte ledState = LOW;
unsigned long lastTimeLedBlink = millis(), blinkDelay = 1000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeLedBlink >= blinkDelay) {
    lastTimeLedBlink += blinkDelay;

    ledState = ledState == HIGH ? LOW : HIGH;
    digitalWrite(LED_BUILTIN, ledState);
  }
}