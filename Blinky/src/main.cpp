#include <Arduino.h>
#include "MyLed.h"
#include "Storage.h"


Storage storage;

int main(int argc, char **argv)
{
  init();

  Serial.begin(115200);

  // int intValue = 32767;
  // storage.writeIntValue(50, intValue);
  // long longValue = 2147483647L;
  // storage.writeLongValue(60, longValue);
  // unsigned long ulongValue = 4294967295;
  // storage.writeUnsignedLongValue(70, ulongValue);

  delay(500);

  int readValue = storage.readIntValue(50);
  Serial.print("Int value from storage = ");
  Serial.println(readValue);

  long readLongValue = storage.readLongValue(60);
  Serial.print("Long value from storage = ");
  Serial.println(readLongValue);

  unsigned long readULongValue = storage.readUnsignedLongValue(70);
  Serial.print("unsigned long value from storage = ");
  Serial.println(readULongValue);

  char greet[6] = { 'H', 'e', 'l', 'l', 'o', '\0' };
  char *ptr = greet;

  while (*ptr)
  {
    Serial.print(*ptr++);
  }
  

  // for (int i = 0; i < 5; i++) {
  //   Serial.print(*ptr++);
  // }

  Serial.println();

  MyLed led(LED_BUILTIN);

  for (;;)
  {
    led.on();
    Serial.println("Turn on LED");
    delay(1000);
    led.off();
    Serial.println("Turn off LED");
    delay(1000);
  }

  return 0;
}
