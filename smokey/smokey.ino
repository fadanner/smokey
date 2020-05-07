#include "WiFi.h"
#include <Wire.h>
#include "src/esp8266-oled-ssd1306/src/SSD1306.h"
#include "src/esp8266-oled-ssd1306/src/OLEDDisplayUi.h"
#include <MAX31855.h> // Include MAX31855 Sensor library


SSD1306 display (0x3c, 5, 4);
OLEDDisplayUi ui     ( &display );



class Fan{
  private:
    String _name;
    byte _speed = 0;
    byte _pwmPin = 0;
    byte _switchPin = 2;
    byte _pwmChannel = 0;
    byte _pwmResolution = 8;
    int _pwmFreq = 25000;
   public:
    Fan(char* name, byte pwmPin, byte switchPin, byte pwmChannel = 0, byte pwmResolution = 8, int pwmFreq = 25000){
      _name = name;
      _pwmPin = pwmPin;
      _switchPin = switchPin;
      _pwmChannel = pwmChannel;
      _pwmResolution = pwmResolution;
      _pwmFreq = pwmFreq; 
    }

    void init(){
      pinMode(_pwmPin,OUTPUT);
      pinMode(_switchPin,OUTPUT);
      ledcSetup(_pwmChannel,_pwmFreq,_pwmResolution);
      ledcAttachPin(_pwmPin,_pwmChannel);
    }

    byte getSpeed(){
      return _speed;
    }
    String getName(){
      return _name;
    }
    void setSpeed(byte speed){
      _speed = speed;
      float setSpeed = 170-(_speed / 100.0 * 170);
      ledcWrite(_pwmChannel,setSpeed);
      if(speed > 0){
        digitalWrite(_switchPin, HIGH);
      }else{
        digitalWrite(_switchPin, LOW); 
      }
    }

};


class TempSensor{
  private:
    long _probeTemp = 0;
    long _ambientTemp = 0;
    String _name;
    byte _pin;
    byte _fault;
    MAX31855_Class MAX31855; ///< Create an instance of MAX31855
  public:
    TempSensor(char* name,byte pin){
      _name = name;
      _pin = pin;
      init();
    }

    void init(){
      while (!MAX31855.begin(_pin));
    }

    long getProbeTemperature(){
        _probeTemp = MAX31855.readProbe();   // retrieve thermocouple probe temp
        uint8_t faultCode          = MAX31855.fault(); 
      return _probeTemp; 
    }

    long getAmbientTemperature(){
      _ambientTemp = MAX31855.readAmbient(); // retrieve MAX31855 die ambient temperature
      return _ambientTemp; 
    }

    byte getFault(){
      _fault = MAX31855.fault(); // retrieve MAX31855 die ambient temperature
      return _fault;   
    }

    String getName(){
      return _name;
    }
};






const char* ssid     = "FaMe_Guest";
const char* password = "fame_gast";

const int sensorCount = 1;
TempSensor sensors[sensorCount] = {
  TempSensor("Sensor0",21)
};

const byte fanPwmPin = 0;
const byte fanSwitchPin = 2;
Fan fan = Fan("Fan",0,2);

const byte buttonLeftPin = 16 ;
const byte buttonRightPin = 17;

const uint8_t  SPI_CHIP_SELECT  =      21; ///< Chip-Select PIN for SPI
const uint8_t  SPI_MISO         =   MISO; ///< Master-In, Slave-Out PIN for SPI
const uint8_t  SPI_SYSTEM_CLOCK =    SCK; ///< System Clock PIN for SPI





void controllerInfos(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0+x,0+y, "Wifi:");
  display->drawString(40+x, 0 +y, WiFi.SSID());
  display->drawString(0+x,10+y, "Rssi:");
  display->drawString(40+x,10+y, String(WiFi.RSSI()));
  display->drawString(0+x,20+y, "IP:");
  display->drawString(40+x,20+y, WiFi.localIP().toString());
}

void sensorInfos(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  for(int i = 0; i < sensorCount; i++){
    display->drawString(0+x,10*i+y, sensors[i].getName());
    display->drawString(60+x, 10*i +y, String(sensors[i].getAmbientTemperature())); 
  }
}

void airInfos(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0, 0, fan.getName());
  display->drawString(60, 0, String(fan.getSpeed())); 
}


void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(millis()));
}

FrameCallback frames[] = {controllerInfos,sensorInfos,airInfos};
int frameCount = 3;
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;
/////////////////////////////////////////////////////

void IRAM_ATTR buttonLeftPressed() {
  ui.previousFrame();
}

void IRAM_ATTR buttonRightPressed() {
  ui.nextFrame();
}






void setup() {
  pinMode(buttonLeftPin, INPUT_PULLUP);
  pinMode(buttonRightPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonLeftPin), buttonLeftPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonRightPin), buttonRightPressed, FALLING);
  

  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());


  Serial.println(MOSI); //23
  Serial.println(MISO); //19
  Serial.println(SCK); //18
  Serial.println(SS); //5
  ui.setTargetFPS(30);
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, frameCount);
  //ui.setTimePerFrame(5*1000);
  ui.disableAutoTransition();
  ui.init();
  fan.init();
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
   }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  

}

void loop() {
    if(Serial.available() > 0){
      byte currentSpeed = (String(Serial.readStringUntil('\n'))).toInt();
      fan.setSpeed(currentSpeed);
      Serial.println(currentSpeed);
    }
  ui.update();
  delay(10);

}
