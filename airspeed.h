#ifdef __cplusplus
extern "C" {
#endif

#ifndef _AIRSEEP_H_
#define _AIRSEEP_H_

#define AIR_ARRAY_SIZE  5
#define AIR_TICK        1000

#define AIR_DENSITY     1.225   // kg/m^3
#define CONV_MPS_KNOTS  1.94    // m/s to knots
#define CONV_MPS_KMH    3.6     // m/s to km/h

// Sensor map
#define AIR_SENSOR_IN_SHIFT    0    // 520
#define AIR_SENSOR_IN_MAX      1024 // 998
#define AIR_SENSOR_PA_MIN      0
// Max pressure for MPXV5010DP is 10Kpa at 5V (250 knots)
#define AIR_SENSOR_PA_MAX      6900 // TODO: a 3.3V 10000 a 5V

// Max pressure for MPXV7002 is 2Kpa (112 knots)
//#define AIR_SENSOR_PA_MAX    2000

#endif // _AIRSEEP_H_

#ifdef __cplusplus
} // extern "C"
#endif
