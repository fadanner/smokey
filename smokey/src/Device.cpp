#include "smokey\Device.h"

Device::Device(String name){
    _name = name;
};

void Device::setValue(byte value){
    _value = value;
};
int Device::getValue(){
    return _value;
};
String Device::getName(){
    return _name;
};
boolean Device::isControllable(){
    return _isControllable;
};