#include "Fan.h"

Fan::Fan(char *name, byte pwmPin, byte switchPin, byte pwmChannel, byte pwmResolution, int pwmFreq) : Device(name)
{
  _pwmPin = pwmPin;
  _switchPin = switchPin;
  _pwmChannel = pwmChannel;
  _pwmResolution = pwmResolution;
  _pwmFreq = pwmFreq;
}

void Fan::init()
{
  pinMode(_pwmPin, OUTPUT);
  pinMode(_switchPin, OUTPUT);
  ledcSetup(_pwmChannel, _pwmFreq, _pwmResolution);
  ledcAttachPin(_pwmPin, _pwmChannel);
}


void Fan::setValue(byte value)
{
  Device::setValue(value);
  float setSpeed = 170 - (Device::getValue() / 100.0 * 170);
  ledcWrite(_pwmChannel, setSpeed);
  if (Device::getValue() > 0)
  {
    digitalWrite(_switchPin, HIGH);
  }
  else
  {
    digitalWrite(_switchPin, LOW);
  }
}