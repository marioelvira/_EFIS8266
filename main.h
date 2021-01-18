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

#define _AIR_SERIAL_DEBUG_      0
#define _ALT_SERIAL_DEBUG_      0
#define _VARIO_SERIAL_DEBUG_    0
#define _MAIN_SERIAL_DEBUG_     0
#define _IN_SERIAL_DEBUG_       0
#define _GYRO_SERIAL_DEBUG_     0
#define _EEPROM_SERIAL_DEBUG_   1
#define _HTTP_SERIAL_DEBUG_     1
#define _WIFI_SERIAL_DEBUG_     1
#define _TICK_SERIAL_DEBUG_     0
#define _PHP_SERIAL_DEBUG_      0
#define _SDCARD_SERIAL_DEBUG_   1

#define _USE_WDT_               0

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
