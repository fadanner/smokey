#ifndef SMOKEY_Device_H
#define SMOKEY_Device_H

#include <Arduino.h>

class Device
{
private:
    String _name;
    int _value;
    boolean _isControllable;

public:
    Device(String name);
    void setValue(byte value);
    int getValue();
    String getName();
    boolean isControllable();
};
#endif