#include "TempSensor.h"

TempSensor::TempSensor(char *name, byte pin) : Device(name)
{
    _pin = pin;
    init();
}

void TempSensor::init()
{
    while (!MAX31855.begin(_pin))
        ;
}

int TempSensor::getProbeTemperature()
{
    _probeTemp = MAX31855.readProbe(); // retrieve thermocouple probe temp
    uint8_t faultCode = MAX31855.fault();
    return _probeTemp;
}

int TempSensor::getAmbientTemperature()
{
    _ambientTemp = MAX31855.readAmbient(); // retrieve MAX31855 die ambient temperature
    return _ambientTemp;
}

byte TempSensor::getFault()
{
    _fault = MAX31855.fault(); // retrieve MAX31855 die ambient temperature
    return _fault;
}

int TempSensor::getValue(){
    Device::setValue(this->getProbeTemperature());
    return Device::getValue();
}