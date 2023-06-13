#include <EEPROM.h>
#include "Storage.h"

int Storage::readIntValue(int address)
{
  return (EEPROM.read(address) << 8) + (EEPROM.read(address + 1));
}

long Storage::readLongValue(int address)
{
  return ((long)EEPROM.read(address) << 24) + ((long)EEPROM.read(address + 1) << 16) + ((long)EEPROM.read(address + 2) << 8) + (long)EEPROM.read(address + 3);
}

unsigned long Storage::readUnsignedLongValue(int address)
{
  return ((long)EEPROM.read(address) << 24) + ((long)EEPROM.read(address + 1) << 16) + ((long)EEPROM.read(address + 2) << 8) + (long)EEPROM.read(address + 3);
}

void Storage::writeIntValue(int address, int number)
{
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

void Storage::writeLongValue(int address, long number)
{
  EEPROM.write(address, number >> 24);
  EEPROM.write(address + 1, number >> 16);
  EEPROM.write(address + 2, number >> 8);
  EEPROM.write(address + 3, number & 0xFF);
}

void Storage::writeUnsignedLongValue(int address, unsigned long number)
{
  EEPROM.write(address, number >> 24);
  EEPROM.write(address + 1, number >> 16);
  EEPROM.write(address + 2, number >> 8);
  EEPROM.write(address + 3, number & 0xFF);
}
