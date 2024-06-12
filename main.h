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
#define _ALT_SERIAL_DEBUG_      1
#define _DLOGGER_SERIAL_DEBUG_  0
#define _EEPROM_SERIAL_DEBUG_   1
#define _GYRO_SERIAL_DEBUG_     1
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
#define BNE_I2C_ADDRESS   0x76

/*
08:26:31.345 -> Scanning...
08:26:31.345 -> I2C device found at address 0x29  // BNO_I2C_ADDRESS
08:26:31.345 -> I2C device found at address 0x48  // ADS_I2C_ADDRESS
08:26:31.379 -> I2C device found at address 0x57  // AT24C32_I2C_ADDRESS E2PORM
08:26:31.379 -> I2C device found at address 0x68  // DS3231_I2C_ADDRESS  RTC
08:26:31.379 -> I2C device found at address 0x76  // BNE_I2C_ADDRESS
08:26:31.379 -> done
*/

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
