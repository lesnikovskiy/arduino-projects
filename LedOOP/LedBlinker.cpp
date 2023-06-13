#include "LedBlinker.h"

LedBlinker::LedBlinker(Led &led) {
  this->led = led;
}

void LedBlinker::begin(long blinkInterval) {
  this->blinkInterval = blinkInterval;
  lastTimeBlinked = millis();

  led.begin();
}

void LedBlinker::update() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeBlinked >= blinkInterval) {
    lastTimeBlinked += blinkInterval;

    led.toggle();
  }
}