#ifdef __cplusplus
extern "C" {
#endif

#ifndef _E2PROM_H_
#define _E2PROM_H_

#define _ERASE_EEPROM_        0
#define _READ_EEPROM_         0
#define _WRITE_SSID_EEPROM_   0

#define EEPROM_SIZE           512

// Address
#define EEPROM_ADD_OK             0x00

#define EEPROM_ADD_IP_MODE        0x01
#define EEPROM_ADD_IP1            0x02
#define EEPROM_ADD_IP2            0x03
#define EEPROM_ADD_IP3            0x04
#define EEPROM_ADD_IP4            0x05
#define EEPROM_ADD_MASK1          0x06
#define EEPROM_ADD_MASK2          0x07
#define EEPROM_ADD_MASK3          0x08
#define EEPROM_ADD_MASK4          0x09
#define EEPROM_ADD_GATE1          0x0A
#define EEPROM_ADD_GATE2          0x0B
#define EEPROM_ADD_GATE3          0x0C
#define EEPROM_ADD_GATE4          0x0D

#define EEPROM_ADD_WIFI_MODE      0x0E
#define EEPROM_ADD_WIFI_SSID      0x0F
#define WIFI_SSID_MAX             32    // SSID max 32 char -> Next 0x2F
#define EEPROM_ADD_WIFI_PSWD      0x2F
#define WIFI_PSWD_MAX             32    // Password max 32 char -> Next 0x4F

#define EEPROM_ADD_GYRO_CAL       0x4F  // 79
#define EERPOM_ADD_GYRO_VAL       0x50
#define EEPROM_GYRO_MAX           22    // Gyro Cal max 22 bytes -> Next 0x66

#define EERPOM_ADD_AIRS_VAL       0x66  // 102
#define EERPOM_AIRS_MAX           28    // Airspeed 28 bytes -> Next 0x82

#define EERPOM_ADD_ALT_VAL        0x82  // 130
#define EERPOM_ALT_MAX            2     // Altimeter 2 bytes -> Next 0x84

#define EERPOM_ADD_UNITS_VAL      0x84  // 134
#define EERPOM_UNITS_MAX          4     // Units 4 bytes -> Next 0x88

#define EERPOM_NEXT               0x88  // 136 Next value

// Values
#define EEPROM_VAL_OK             0xA5

#define EEPROM_VAL_IP_MODE        DHCP_MODE
#define EEPROM_VAL_IP1            192
#define EEPROM_VAL_IP2            168
#define EEPROM_VAL_IP3            43
#define EEPROM_VAL_IP4            10
#define EEPROM_VAL_MASK1          255
#define EEPROM_VAL_MASK2          255
#define EEPROM_VAL_MASK3          255
#define EEPROM_VAL_MASK4          0
#define EEPROM_VAL_GATE1          192
#define EEPROM_VAL_GATE2          168
#define EEPROM_VAL_GATE3          43
#define EEPROM_VAL_GATE4          1

#define ACCESSPOINT_MODE          0
#define STATION_MODE              1
#define EEPROM_VAL_WIFI_MODE      ACCESSPOINT_MODE // STATION_MODE

#define EEPROM_VAL_NOT_CAL        0x00   // Not calibrated

#define EEPROM_VAL_GYRO_CAL_OK    0xC0

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
