
#ifndef SMOKEY_FAN_H
#define SMOKEY_FAN_H

#include <Arduino.h>
#include "Device.h"

class Fan : public Device
{
private:
    byte _pwmPin = 0;
    byte _switchPin = 2;
    byte _pwmChannel = 0;
    byte _pwmResolution = 8;
    int _pwmFreq = 25000;

public:
    Fan(char *name, byte pwmPin, byte switchPin, byte pwmChannel = 0, byte pwmResolution = 8, int pwmFreq = 25000);
    void init();
    void setValue(byte speed);
};
#endif
