#ifndef STORAGE_H
#define STORAGE_H

class Storage
{
  public:
    int readIntValue(int address);
    long readLongValue(int address);
    unsigned long readUnsignedLongValue(int address);
    void writeIntValue(int address, int number);
    void writeLongValue(int address, long number);
    void writeUnsignedLongValue(int address, unsigned long number);
};

#endif