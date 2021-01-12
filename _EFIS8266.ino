
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <SPI.h>
#include <SD.h>

#include "main.h"

#include "airspeed.h"
#include "altimeter.h"
#include "e2prom.h"
#include "gyro.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "json.h"
#include "php.h"
#include "time.h"
#include "sdcard.h"
#include "units.h"
#include "vario.h"
#include "wdt.h"
#include "wifi.h"

//////////////
// Watchdog //
//////////////
#if (_USE_WDT_ == 1)
int wdtForced;
#endif

////////////
// E2PROM //
////////////
int resetConfig;

///////////////////
// IO definition //
///////////////////
int outAux;
int outLed;
int inAux;

int   InStatus = 0;
int   InStatus_ant = 0;
int   InCounter = 0;
int   InPulsacion = 0;

///////////
// Wi-Fi //
///////////
String        wifiInfo;

unsigned long wifiAPTick = 0;
unsigned long wifiLEDTick = 0;

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

unsigned long timeJSONMilisec = 0;

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
String                    gyroInfo;
int                       gyroNConnec;
unsigned long             gyroTickReconnect;
int                       gyroStatus;
GyroData                  gyroData;
adafruit_bno055_offsets_t gyroCalVal;
sensor_t                  gyroSensor;

sensors_event_t           gyroEvent;
uint8_t                   system_status, system_selftest, system_error;
uint8_t                   sys, gyro, accel, mag;

// I2C device address (by default address is 0x29 or 0x28)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

int gMag, gRoll, gPitch;
String sRoll;
String sPitch;
int iGforce;
int iBall;

///////////////
// Altimeter //
///////////////
float     Altimeter;
float     Altitude_m;

sensor_t      altSensor;
String        altInfo;
int           altStatus;
int           altNConnec;
unsigned long altTickReconnect;

AltData   altData;

Adafruit_BME280 bme;
Adafruit_Sensor *bme_temp     = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

sensors_event_t temp_event;       // Temp ºC
sensors_event_t pressure_event;   // Pressure hPa
sensors_event_t humidity_event;   // Humidity %

//////////////
// Airspeed //
//////////////
float AirSpeed;

float AirPressure;
float Air_mVolts;
int   AirInValue;
int   AirInValueCorrected;
int   AirInArray[AIR_ARRAY_SIZE];
int   AirInPointer;

String   airInfo;
AirsData airsData;
float AirSpeed_m;
float AirSpeed_b;

#if (_AIR_SERIAL_DEBUG_ == 1)
unsigned long AirCurrentTime = millis();
unsigned long AirPreviousTime = 0;
#endif

///////////
// Vario //
///////////
float Vario;
float Vario_mps;

//float VarioCurrentAtlitude;
float VarioPreviousAtlitude;

unsigned long VarioCurrentTime = millis();
unsigned long VarioPreviousTime = 0;

///////////
// Units //
///////////
Units  units;

/////////////
// SD Card //
/////////////
String        sdInfo;
int           sdStatus;
unsigned long sdTickReconnect;
File          sdFile;

//============//
// MAIN SETUP //
//============//
void setup(void)
{  
  // PIN setup
  _PINSetup();

  // IO setup
  _IOSetup();

  #if (_SERIAL_DEBUG_ == 1)
  delay(5000);  // 5 secs
  Serial.begin(115200);
  Serial.println("");
  #endif

  // Config setup
  _ConfigSetup();
  
  // Gyro setup
  _GyroSetup();

  // Airspeed setup
  _AirspeedSetup();

  // Altimeter setup
  _AltimeterSetup();

  // Vario setup
  _VarioSetup();
  
  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time Setup
  _TimeSetup();

  // SD card Setup
  _SDSetup();

  #if (_USE_WDT_ == 1)
  // Wdt Setup
  _WdtSetup();  
  #endif
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

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _IOLoop();
  _GyroLoop();
  _AirspeedLoop();
  _AltimeterLoop();
  _VarioLoop();
  _WifiLoop();
  _WifiLedLoop();
  _SDLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) ||
      (wifiStatus == WIFI_STATION_CONNECTED))
  {
    _HttpLoop();
  }
  
  _TimeLoop();
  _ConfigLoop();

  #if (_USE_WDT_ == 1)
  _WdtLoop();  
  #endif
}
