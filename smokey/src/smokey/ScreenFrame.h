#ifndef SMOKEY_SCREENFRAME_H
#define SMOKEY_SCREENFRAME_H

#include <Arduino.h>
#include "../esp8266-oled-ssd1306/src/SSD1306.h"
#include "ScreenLine.h"

class ScreenFrame
{
protected:
  SSD1306 &display;
  byte _lineCount = 6;
  ScreenLine _screenLines[6];
  byte _hoveredLine = 0;
  boolean _selected = false;

public:
  ScreenFrame();

  void setDisplay(SSD1306 &display);
  void drawFrame();
  void hoverNextLine();
  void hoverPreviousLine();
  void selectLine();
  void selectLine(byte selectedLine);
  void setScreenLine(ScreenLine screenline, byte position);
  void deselectLine();
  void toggleSelection();

  void setSelectedValue(byte value);
  void increaseSelectedValue(byte value = 1);
  void decreaseSelectedValue(byte value = 1);

  byte getSelectedValue();
};

#endif