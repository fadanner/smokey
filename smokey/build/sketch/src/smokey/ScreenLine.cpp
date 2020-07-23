#include "ScreenLine.h"

ScreenLine::ScreenLine(Device& device){
    _device = device;
}

    String ScreenLine::getColumn1String(){
        return _device.getName()
    };
    String ScreenLine::getColumn2String(){
        return String(_device.getValue());
    };

    void ScreenLine::setValue(byte value){
        _device.setValue(value);
    };
    void ScreenLine::increaseValue(byte value){
        _device.setValue(_device.getValue() + value);
    };

    void ScreenLine::decreaseValue(byte value){
        _device.setValue(_device.getValue() - value);
    };