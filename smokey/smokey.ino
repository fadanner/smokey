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
//OLEDDisplayUi ui     ( &display );


char* ssid     = "FaMe_Guest";
const char* password = "fame_gast";

const int sensorCount = 6;
TempSensor sensors[sensorCount] = {
  TempSensor("Fleisch1",22),
  TempSensor("Fleisch2",16),
  TempSensor("Grill1",17),
  TempSensor("Grill2",0),
  TempSensor("Grill3",5),
  TempSensor("Grill4",4)
};

Fan fan = Fan("Fan",0,2);

const byte buttonLeftPin = 16 ;
const byte buttonRightPin = 17;
const byte buttonUpPin = 17;
const byte buttonDownPin = 17;
const byte buttonSelectPin = 17;

const uint8_t  SPI_CHIP_SELECT  =      21; ///< Chip-Select PIN for SPI
const uint8_t  SPI_MISO         =   MISO; ///< Master-In, Slave-Out PIN for SPI
const uint8_t  SPI_SYSTEM_CLOCK =    SCK; ///< System Clock PIN for SPI

ScreenController screenController = ScreenController(display, buttonLeftPin, buttonRightPin, buttonUpPin, buttonDownPin, buttonSelectPin);
ScreenFrame sfController = ScreenFrame();
ScreenFrame sfTemp  = ScreenFrame();
ScreenFrame sfAir  = ScreenFrame();



void setup() {

  
  Serial.begin(115200);
  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());


  Serial.println(MOSI); //23
  Serial.println(MISO); //19
  Serial.println(SCK); //18
  Serial.println(SS); //5


  ScreenLine slSensor0 = ScreenLine(sensors[0]);
  sfTemp.setScreenLine(slSensor0,0);
  screenController.SetFrame(sfTemp,0);
  
  ScreenLine slFan = ScreenLine(fan);
  sfAir.setScreenLine(slFan,0);
  screenController.SetFrame(sfTemp,1);
 
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
   // byte currentSpeed = (String(Serial.readStringUntil('\n'))).toInt();
    //fan.setValue(currentSpeed);
    //Serial.println(currentSpeed);
    Serial.println("##########");
    for (size_t i = 0; i < sensorCount; i++)
    {
      String data;
      data = sensors[i].getString();
      Serial.println(data);
    }

  //screenController.watchButtonPress();
  //screenController.updateScreen();
  delay(500);

}
