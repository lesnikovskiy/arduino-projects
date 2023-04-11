#include <LiquidCrystal.h>

float voltageThreshold = 3.5;
// Warning: Use DMM to calibrate the correct ratio for your battery source
float voltageDividerRatio = 6.0;

const int analogInputPin = A0;

const int lcdRsPin = A5;
const int lcdEPin = A4;
const int lcd4Pin = 6;
const int lcd5Pin = 7;
const int lcd6Pin = 8;
const int lcd7Pin = 9;

LiquidCrystal lcd (lcdRsPin, lcdEPin, lcd4Pin, lcd5Pin, lcd6Pin, lcd7Pin);

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2);
}

void loop() {
  int sensorValue = analogRead(analogInputPin);
  float voltage = sensorValue * (5.0 / 1023.0) * voltageDividerRatio;

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.setCursor(9, 0);
  lcd.print(voltage, 3);
  lcd.setCursor(14, 0);
  lcd.print("V");

  Serial.print("Voltage: ");
  Serial.print(voltage, 3);
  Serial.println("V");

  if (voltage < voltageThreshold) {
    Serial.println("Low battery voltage detected!");
    lcd.setCursor(2, 1);
    lcd.print("Low battery");
  }

  delay(1000);
}
