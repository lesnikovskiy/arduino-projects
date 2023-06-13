#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include <Arduino.h>
#include "Led.h"

class LedBlinker {
  private:
    Led led;
    unsigned long lastTimeBlinked;
    unsigned long blinkInterval;
  public:
    LedBlinker() {}
    LedBlinker(Led &led);
    void begin(long blinkInterval);
    void update();
};

#endif