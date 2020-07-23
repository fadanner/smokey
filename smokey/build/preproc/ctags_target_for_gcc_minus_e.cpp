# 1 "e:\\code\\smokey\\smokey\\smokey.ino"
# 2 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 3 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 4 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 5 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 6 "e:\\code\\smokey\\smokey\\smokey.ino" 2


# 9 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 10 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 11 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 12 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 13 "e:\\code\\smokey\\smokey\\smokey.ino" 2
# 14 "e:\\code\\smokey\\smokey\\smokey.ino" 2

SSD1306 display (0x3c, 5, 4);
OLEDDisplayUi ui ( &display );


char* ssid = "FaMe_Guest";
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

const uint8_t SPI_CHIP_SELECT = 21; ///< Chip-Select PIN for SPI
const uint8_t SPI_MISO = MISO; ///< Master-In, Slave-Out PIN for SPI
const uint8_t SPI_SYSTEM_CLOCK = SCK; ///< System Clock PIN for SPI

ScreenController screenController = ScreenController(display, buttonLeftPin, buttonRightPin, buttonUpPin, buttonDownPin, buttonSelectPin);
ScreenFrame sfController = ScreenFrame(display);
ScreenFrame sfTemp = ScreenFrame(display);
ScreenFrame sfAir = ScreenFrame(display);



/////////////////////////////////////////////////////


void setup() {


  Serial.begin(115200);
  Serial.setDebugOutput(true);
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
    if(Serial.available() > 0){
      byte currentSpeed = (String(Serial.readStringUntil('\n'))).toInt();
      fan.setValue(currentSpeed);
      Serial.println(currentSpeed);
    }
  screenController.watchButtonPress();
  screenController.updateScreen();
  delay(10);

}
