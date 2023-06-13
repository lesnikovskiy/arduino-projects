const byte relay_pin{ 9 };

const byte state_1{ 1 };
const byte state_2{ 2 };

byte state{ state_1 };

void setup() {
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  switch (state) {
    case state_1:
      {
        digitalWrite(relay_pin, HIGH);
        delay(3000);
        digitalWrite(relay_pin, LOW);
        delay(1500);
        state = state_2;
        break;
      }
    case state_2:
      {
        digitalWrite(relay_pin, HIGH);
        delay(5000);
        digitalWrite(relay_pin, LOW);
        delay(1500);
        state = state_1;
        break;
      }
    default:
      {
        state = state_1;
      }
  }
}