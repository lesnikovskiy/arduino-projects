#include "Led.h"

Led::Led(byte pin) {
  this->pin = pin;
}

void Led::begin() {
  state = LOW;
  pinMode(pin, OUTPUT);
}

void Led::on() {
  state = HIGH;
  digitalWrite(pin, state);
}

void Led::off() {
  state = LOW;
  digitalWrite(pin, state);
}

void Led::toggle() {
  if (state == LOW) {
    on();
  } else {
    off();
  }
}