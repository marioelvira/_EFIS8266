#ifdef __cplusplus
extern "C" {
#endif

#ifndef _AIRSEEP_H_
#define _AIRSEEP_H_

#define AIR_ARRAY_SIZE  20
#define AIR_TICK        1000

#define AIR_DENSITY     1.2     // kg/m^3
#define CONV_MPS_KNOTS  1.94    // m/s to knots

// Sensor map
#define AIR_SENSOR_IN_SHIFT    520
#define AIR_SENSOR_IN_MAX      998
#define AIR_SENSOR_PA_MIN      0
// Max pressure for MPXV5010DP is 10Kpa (250 knots)
#define AIR_SENSOR_PA_MAX      10000

// Max pressure for MPXV7002 is 2Kpa (112 knots)
//#define AIR_SENSOR_PA_MAX    2000

#endif // _AIRSEEP_H_

#ifdef __cplusplus
} // extern "C"
#endif
