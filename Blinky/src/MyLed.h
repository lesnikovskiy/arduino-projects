#ifndef LED_H
#define LED_H

#include <Arduino.h>

class MyLed
{
  private:
    int pin;

  public:
    MyLed(int pin);
    void on();
    void off();
};

#endif