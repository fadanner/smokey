#ifndef SMOKEY_SCREENCONTROLLER_H
#define SMOKEY_SCREENCONTROLLER_H

#include <Arduino.h>
#include "../esp8266-oled-ssd1306/src/SSD1306.h"
#include "ScreenFrame.h"
#include "Button.h"

class ScreenController
{
private:
  SSD1306  _display;
  static const int _frameCount = 3;
  byte _currentFrame = 0;
  ScreenFrame _screenFrames [_frameCount];
  Button _buttonLeft;
  Button _buttonRight;
  Button _buttonUp;
  Button _buttonDown;
  Button _buttonSelect;
  boolean _lineSelected = false;

public:
  ScreenController(SSD1306 display, byte pinButtonLeft, byte pinButtonRight, byte pinButtonUp, byte pinButtonDown, byte pinButtonSelect);

  void init();

  void SetFrame(ScreenFrame frame, byte position);

  void watchButtonPress();

  void updateScreen();

  void showNextFrame();

  void showPreviousFrame();
};

#endif