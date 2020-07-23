#ifndef SMOKEY_SCREENLINE_H
#define SMOKEY_SCREENLINE_H

#include <Arduino.h>
#include "Device.h"

class ScreenLine
{
private:
  Device _device;

public:
    ScreenLine();
    String getColumn1String();
    String getColumn2String();
    void setValue(byte value);
    void increaseValue(byte value);
    void decreaseValue(byte value);
};
#endif