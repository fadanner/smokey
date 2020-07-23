#include "ScreenController.h"

ScreenController::ScreenController(SSD1306& display, byte pinButtonLeft, byte pinButtonRight, byte pinButtonUp, byte pinButtonDown, byte pinButtonSelect):
_display(display)
{
    _display = display;
    _buttonLeft = Button(pinButtonLeft);
    _buttonRight = Button(pinButtonRight);
    _buttonUp = Button(pinButtonUp);
    _buttonDown = Button(pinButtonDown);
    _buttonSelect = Button(pinButtonSelect);
    init();
};

void ScreenController::init(){
    _display.clear();

};

void ScreenController::SetFrame(ScreenFrame frame, byte position)
{
    _screenFrames[position] = frame;
};

void ScreenController::watchButtonPress()
{
    //Left
    if (_buttonLeft.isPressed() && !_lineSelected)
    {
        showPreviousFrame();
    }
    else if (_buttonLeft.isPressed() && _lineSelected)
    {
         _screenFrames[_currentFrame].decreaseSelectedValue();
    }
    //Right
    if (_buttonRight.isPressed() && !_lineSelected)
    {
        showNextFrame();
    }
    else if (_buttonRight.isPressed() && _lineSelected)
    {
         _screenFrames[_currentFrame].increaseSelectedValue();
    }
    //Up 
    if (_buttonUp.isPressed())
    {
         _screenFrames[_currentFrame].hoverPreviousLine();
         _screenFrames[_currentFrame].deselectLine();
    }
    //Down 
    if (_buttonDown.isPressed())
    {
         _screenFrames[_currentFrame].hoverNextLine();
         _screenFrames[_currentFrame].deselectLine();
    }
    //Select 
    if (_buttonSelect.isPressed())
    {
         _screenFrames[_currentFrame].toggleSelection();
    }
};

void ScreenController::updateScreen()
{
    _screenFrames[_currentFrame].drawFrame();
};

void ScreenController::showNextFrame()
{
    _currentFrame++;
    updateScreen();
};

void ScreenController::showPreviousFrame()
{
    _currentFrame--;
    updateScreen();
};
