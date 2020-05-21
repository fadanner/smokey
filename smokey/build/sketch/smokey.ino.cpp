#line 1 "e:\\code\\smokey\\smokey\\smokey.ino"
#include "Arduino.h"
#include "Wire.h"
#include "WiFi.h"
#include "src/esp8266-oled-ssd1306/src/SSD1306.h"
#include "src/esp8266-oled-ssd1306/src/OLEDDisplayUi.h"


#include "src/smokey/Device.h"
#include "src/smokey/TempSensor.h"
#include "src/smokey/Fan.h"
#include "src/smokey/ScreenController.h"
#include "src/smokey/ScreenFrame.h"
#include "src/smokey/ScreenLine.h"

SSD1306 display (0x3c, 5, 4);
OLEDDisplayUi ui     ( &display );


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
const byte buttonUpPin = 17;
const byte buttonDownPin = 17;
const byte buttonSelectPin = 17;

const uint8_t  SPI_CHIP_SELECT  =      21; ///< Chip-Select PIN for SPI
const uint8_t  SPI_MISO         =   MISO; ///< Master-In, Slave-Out PIN for SPI
const uint8_t  SPI_SYSTEM_CLOCK =    SCK; ///< System Clock PIN for SPI

ScreenController screenController;
ScreenFrame sfController;
ScreenFrame sfTemp;
ScreenFrame sfAir;



/////////////////////////////////////////////////////


#line 51 "e:\\code\\smokey\\smokey\\smokey.ino"
void setup();
#line 89 "e:\\code\\smokey\\smokey\\smokey.ino"
void loop();
#line 51 "e:\\code\\smokey\\smokey\\smokey.ino"
void setup() {

  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());


  Serial.println(MOSI); //23
  Serial.println(MISO); //19
  Serial.println(SCK); //18
  Serial.println(SS); //5

  screenController = ScreenController(display, buttonLeftPin, buttonRightPin, buttonUpPin, buttonDownPin, buttonSelectPin);
  sfTemp = ScreenFrame(display);
  sfTemp.setScreenLine(new ScreenLine(sensors[0])
  screenController.SetFrame(sfTemp;0)

  sfAir = ScreenFrame(display);
  sfAir.setScreenLine(new ScreenLine(fan)
  screenController.SetFrame(sfTemp;1)
 
  screenController.updateScreen();
  
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
  screenController.watchButtonPress();
  screenController.updateScreen();
  delay(10);

}

