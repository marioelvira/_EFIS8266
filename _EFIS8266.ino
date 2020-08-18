
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "e2prom.h"
#include "gyro.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "wifi.h"

///////////////////
// IO definition //
///////////////////
int ioOut;
int ioLed;
int ioIn;

///////////
// Wi-Fi //
///////////
unsigned long wifiAPTick = 0;
unsigned long wifiLEDTick = 0;

///////////
// Wi-Fi //
///////////

#if (_WRITE_SSID_EEPROM_ == 1)
const char* ssidSt = SSIDST;
const char* passwordSt = PSKST;
#endif

// Station Mode
char ssid[WIFI_SSID_MAX];
char password[WIFI_PSWD_MAX];

IPAddress wifiIP;

// Accesspoint Mode
const char* ssidAp = SSIDAP;
const char* passwordAp = PSKAP;

int wifiStatus;
int wifiMode;

////////////////
// IP Address //
////////////////
int       ipMode;

IPAddress ipAddress (192, 168, 43, 200);
IPAddress gateWay   (192, 168, 43, 1);
IPAddress netMask   (255, 255, 255, 0);

byte mac[6];

/////////////////
// Device Name //
/////////////////
#define DEVICENAME      "efis8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

String outState = "OFF";
String inState = "OFF";

int httpStatus;

//////////
// Gyro //
//////////
int                       gyroStatus;
GyroData                  gyroData;
adafruit_bno055_offsets_t gyroCalVal;
adafruit_bno055_offsets_t gyroCalValNew;
sensor_t                  gyroSensor;

// I2C device address (by default address is 0x29 or 0x28)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  // IO setup
  _IOSetup();

  // Gyro setup
  _GyroSetup();
  
  #if (_SERIAL_DEBUG_ == 1)
  delay(5000);  // 5 secs
  Serial.begin(115200);
  Serial.println("");
  #endif

  // Config setup
  _ConfigSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();
}

//////////////
// IO steup //
//////////////
void _IOSetup(void)
{ 
  pinMode(DI_LED, OUTPUT);
  digitalWrite(DI_LED, DI_OFF);
  ioLed = IO_OFF;

  pinMode(DI_OUT, OUTPUT);
  digitalWrite(DI_OUT, DI_OFF);
  ioOut = IO_OFF;

  pinMode(DI_IN, INPUT);
  ioIn = IO_OFF;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
  if (ioLed == IO_OFF)
    digitalWrite(DI_LED, DI_OFF);
  else
    digitalWrite(DI_LED, DI_ON);
 
  if (ioOut == IO_OFF)
    digitalWrite(DI_OUT, DI_OFF);
  else
    digitalWrite(DI_OUT, DI_ON);

  if (digitalRead(DI_IN))
    ioIn = IO_OFF;
  else
    ioIn = IO_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _IOLoop();
  _GyroLoop();
  
  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) ||
      (wifiStatus == WIFI_STATION_CONNECTED))
  {
    _HttpLoop();
  }
}
