#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
private:
  byte pin;
  byte state;
public:
  Led() {}
  Led(byte pin);
  void begin();
  void on();
  void off();
  void toggle();
};

#endif