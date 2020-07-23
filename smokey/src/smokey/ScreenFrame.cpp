#include "ScreenFrame.h"


ScreenFrame::ScreenFrame():display(display){}

void ScreenFrame::setDisplay(SSD1306 &display){
        this->display = display;
}

void ScreenFrame::drawFrame()
{
    this->display.setTextAlignment(TEXT_ALIGN_LEFT);
    this->display.setFont(ArialMT_Plain_10);
    for (int i = 0; i < _lineCount; i++)
    {
        if (i == _hoveredLine)
        {
            this->display.drawString(0, 10 * i, "*");
        }
        this->display.drawString(1, 10 * i, _screenLines[i].getColumn1String());
        if (_selected)
        {
            this->display.drawString(59, 10 * i, "<");
        }
        this->display.drawString(60, 10 * i, _screenLines[i].getColumn2String());
        if (_selected)
        {
            this->display.drawString(66, 10 * i, ">");
        }
    }
};

void ScreenFrame::hoverNextLine()
{
    _hoveredLine++;
    this->drawFrame();
};

void ScreenFrame::hoverPreviousLine()
{
    _hoveredLine++;
    this->drawFrame();
}

void ScreenFrame::selectLine(){
    _selected = true;
    this->drawFrame();
}

void ScreenFrame::toggleSelection(){
    if(_selected == true){
        _selected == false;
    }else{
        _selected == true;
    }
    this->drawFrame();
}


void ScreenFrame::setScreenLine(ScreenLine screenline, byte position){
    _screenLines[position] = screenline;
}

void ScreenFrame::deselectLine(){
    	_selected = false;
        this->drawFrame();
}

void ScreenFrame::setSelectedValue(byte value){
    if(_selected){
        (_screenLines[_hoveredLine]).setValue();
    }
}

void ScreenFrame::increaseSelectedValue(byte value = 1){
    if(_selected){
        (_screenLines[_hoveredLine]).increaseValue(value);
    }  
}
void ScreenFrame::decreaseSelectedValue(byte value = 1){
    if(_selected){
        (_screenLines[_hoveredLine]).decreaseValue(value);
    }  
}
