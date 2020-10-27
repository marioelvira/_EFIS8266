
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
int outAux;
int outLed;
int inAux;

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
int httpStatus;

#if (_JSON_SERIAL_DEBUG_ == 1)
unsigned long timeJSONMilisec = 0;
#endif

//////////
// Time //
//////////
unsigned long timeMilisec = 0;
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;

//////////
// Gyro //
//////////
int                       gyroStatus;
GyroData                  gyroData;
adafruit_bno055_offsets_t gyroCalVal;
sensor_t                  gyroSensor;

sensors_event_t           event;
uint8_t                   system_status, self_test_results, system_error;
uint8_t                   sys, gyro, accel, mag;

// I2C device address (by default address is 0x29 or 0x28)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

int Mag, gRoll, gPitch;
String sRoll;
String sPitch;
int iGforce;

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  // IO setup
  _PINSetup();

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

  // Time Setup
  _TimeSetup();
}

///////////////
// PIN setup //
///////////////
void _PINSetup(void)
{ 
  //------//
  // OUTS //
  //------//
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  outLed = IO_OFF;

  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, PIN_OUT_OFF);
  outAux = IO_OFF;

  //-----//
  // INS //
  //-----//
  
  pinMode(PIN_IN, INPUT);
  inAux = IO_OFF;
}

///////////////////////
// PIN state machine //
///////////////////////
void _PINLoop()
{
  //------//
  // OUTS //
  //------//
  
  if (outLed == IO_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);
 
  if (outAux == IO_OFF)
    digitalWrite(PIN_OUT, PIN_OUT_OFF);
  else
    digitalWrite(PIN_OUT, PIN_OUT_ON);

  //-----//
  // INS //
  //-----//

  if (digitalRead(PIN_IN) == PIN_IN_OFF)
    inAux = IO_OFF;
  else
    inAux = IO_ON;
}

/////////////////////
// JSON simulation //
/////////////////////
#define JSON_TICK      100

unsigned long jsonCurrentTime = millis();
unsigned long jsonPreviousTime = 0;

int airSpeed = 34;
//int rollAngle = 30;
//int pitchAngle = 50;
int altitute = 1500;
int QNH = 1023;
//int turnAngle = 10;
//int heading = 90;
int vario = 2;

void _JsonLoop ()
{
  jsonCurrentTime = millis();
  if (jsonCurrentTime - jsonPreviousTime >= JSON_TICK)
  {
    airSpeed++;
    if (airSpeed > 100)
      airSpeed = 20;

    //rollAngle++;
    //if (rollAngle > 30)
    //  rollAngle = 0;
    
    //pitchAngle++;
    //if (pitchAngle > 30)
    //  pitchAngle = 0;
   
    altitute++;
    if (altitute > 10000)
      altitute = 1000;
    
    QNH++;
    if (QNH > 1030)
      QNH = 990;    
    
    //turnAngle++;
    //if (turnAngle > 30)
    //  turnAngle = -30;
    
    //heading++;
    //if (heading > 350)
    //  heading = 10;
    
    //vario++;
    //if (vario > 2);
    //  vario = 0;
        
    jsonPreviousTime = jsonCurrentTime;
  } 
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _GyroLoop();
  _WifiLoop();
  _WifiLedLoop();

  _JsonLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) ||
      (wifiStatus == WIFI_STATION_CONNECTED))
  {
    _HttpLoop();
  }
  
  _TimeLoop();
}
