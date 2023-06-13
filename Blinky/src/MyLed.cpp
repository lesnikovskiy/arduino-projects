#include "MyLed.h"

MyLed::MyLed(int pin)
{
  this->pin = pin;
}

void MyLed::on()
{
  digitalWrite(pin, HIGH);
}

void MyLed::off()
{
  digitalWrite(pin, LOW);
}
