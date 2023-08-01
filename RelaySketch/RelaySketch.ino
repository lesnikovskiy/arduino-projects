const byte RELAY_PIN{ 9 };
const byte MOVEMENT_PIN{ 10 };
const unsigned long THREE_MINUTES{ 1000 * 60 * 3 };

unsigned long lastTimeRead = millis();
unsigned long readDelay = 100;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MOVEMENT_PIN, INPUT);

  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeRead >= readDelay) {
    lastTimeRead = timeNow;

    byte isMoving = digitalRead(MOVEMENT_PIN);
    readDelay = isMoving ? THREE_MINUTES : 100;

    Serial.print("Moving state at ");
    Serial.print(timeNow);
    Serial.print(" is ");
    Serial.println(isMoving);

    if (isMoving) {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}