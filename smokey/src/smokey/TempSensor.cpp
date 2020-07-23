#include "TempSensor.h"
#include <MAX31855.h>

TempSensor::TempSensor(char *name, byte pin) : Device(name)
{
    _pin = pin;
    init();
}

void TempSensor::init()
{
    while (!Sensor.begin(_pin))
        ;
}

int TempSensor::getProbeTemperature()
{
    _probeTemp = Sensor.readProbe() / 1000; // retrieve thermocouple probe temp
    return _probeTemp;
}

int TempSensor::getAmbientTemperature()
{
    _ambientTemp = Sensor.readAmbient() / 1000; // retrieve MAX31855 die ambient temperature
    return _ambientTemp;
}

byte TempSensor::getFault()
{
    _fault = Sensor.fault(); // retrieve MAX31855 die ambient temperature
    return _fault;
}

String TempSensor::getString()
{
    char data[100];
    sprintf(data,"%s : int: %i, ext: %i, fault:%i",this->getName(),this->getAmbientTemperature(),this->getProbeTemperature(),this->getFault());
    return data;
}

int TempSensor::getValue(){
    Device::setValue(this->getProbeTemperature());
    return Device::getValue();
}