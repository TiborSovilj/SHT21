#ifndef SHT21_H
#define SHT21_H

#include "mbed.h"

#define ADDRESS 0x40
#define T_TRIGGER_HOLD_MASTER 0xE3
#define RH_TRIGGER_HOLD_MASTER 0xE5

class SHT21
{
public:
    SHT21(PinName, PinName);
    double getHumid();
    double getTemp();
    //void reset();

private:
    I2C sht;
    char _address;
    double temp;
    double rh;
    int catchTemp();
    int catchHumid();
    void arithmetics(char);

};

#endif