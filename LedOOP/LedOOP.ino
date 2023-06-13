#include "Led.h"
#include "LedBlinker.h"

#define RED_LED_PIN 11
#define YELLOW_LED_PIN 10
#define GREEN_LED_PIN 9

Led redLed(RED_LED_PIN);
Led yellowLed(YELLOW_LED_PIN);
Led greenLed(GREEN_LED_PIN);

LedBlinker redLedBlinker(redLed);
LedBlinker yellowLedBlinker(yellowLed);
LedBlinker greenLedBlinker(greenLed);

void setup() {
  redLedBlinker.begin(1000);
  yellowLedBlinker.begin(100);
  greenLedBlinker.begin(500);
}

void loop() {
  redLedBlinker.update();
  yellowLedBlinker.update();
  greenLedBlinker.update();
}