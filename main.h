#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

////////////////////////////////////////////////////////
// Note: Selec on Arduino:                            //
//       SP8266 Boards-> NodeMCU 1.0 (ESP-12E Module) //
////////////////////////////////////////////////////////

///////////
// Debug //
///////////
#define _SERIAL_DEBUG_          1

#define _ADCI2C_SERIAL_DEBUG_   0
#define _AIR_SERIAL_DEBUG_      0
#define _ALT_SERIAL_DEBUG_      0
#define _DLOGGER_SERIAL_DEBUG_  1
#define _EEPROM_SERIAL_DEBUG_   1
#define _GYRO_SERIAL_DEBUG_     0
#define _HTTP_SERIAL_DEBUG_     1
#define _IN_SERIAL_DEBUG_       0
#define _MAIN_SERIAL_DEBUG_     0
#define _PHP_SERIAL_DEBUG_      0
#define _RTC_SERIAL_DEBUG_      1
#define _SDCARD_SERIAL_DEBUG_   0
#define _TICK_SERIAL_DEBUG_     0
#define _WIFI_SERIAL_DEBUG_     1
#define _VARIO_SERIAL_DEBUG_    0

#define _USE_WDT_               0
#define _USE_RTC_               1

////////////
// HW I2C //
////////////
#define BNO_I2C_ADDRESS   0x29
#define ADS_I2C_ADDRESS   0x48
#define RTC_I2C_ADDRESS   0x68
#define BNE_I2C_ADDRESS   0x77

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
