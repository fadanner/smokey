#ifndef SMOKEY_TEMPSENSOR_H
#define SMOKEY_TEMPSENSOR_H

#include <Arduino.h>
#include "MAX31855.h" // Include MAX31855 Sensor library
#include "Device.h"

class TempSensor : public Device{
  private:
    int _probeTemp = 0;
    int _ambientTemp = 0;
    byte _pin;
    byte _fault;
    MAX31855_Class MAX31855; ///< Create an instance of MAX31855
  public:
    TempSensor(char* name,byte pin) ;

    void init();

    int getProbeTemperature();

    int getAmbientTemperature();

    int getValue();

    byte getFault();
};
#endif