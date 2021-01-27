#ifdef __cplusplus
extern "C" {
#endif

#ifndef _AIRSEEP_H_
#define _AIRSEEP_H_

typedef struct
{
  int16_t digOffset;      // 2 bytes
  int16_t digEOS;         // 2 bytes
  float   mVoltsEOS;      // 4 bytes
  float   airSensR;       // 4 bytes
  float   airSensPA1;     // 4 bytes
  float   airSensPA2;     // 4 bytes
  float   airSensV1;      // 4 bytes
  float   airSensV2;      // 4 bytes
} AirsData;

#define AIR_ARRAY_SIZE  5
#define AIR_TICK        1000

#define AIR_DENSITY     1.225     // kg/m^3
#define CONV_MPS_KNOTS  1.94      // m/s to knots
#define CONV_MPS_KMH    3.6       // m/s to km/h

#define AIR_DIG_OFFSET          0     // Digital Offset
#define AIR_DIG_EOS             1024  // Digital End Of Scale
#define AIR_MVOLTS_EOS          3300  // mVolts Enf Of Scale

#define AIR_SENS_R              0.66  // (3.3 <-> 5)

//#define AIR_SENS_INFO_TYPE      "MPX5010DP"
#define AIR_SENS_INFO_TYPE        "XGZP6897A"

#define AIR_SENS_PA1              0     // 0  Pa
#define AIR_SENS_PA2              10000 // 10 kPa
#define AIR_SENS_V1               200   // 200 mV
#define AIR_SENS_V2               4700  // 4700 mV

#define AIR_SPEED_MPS_ONFLY       17    // 17 m/s aprox 60 km/h

#endif // _AIRSEEP_H_

#ifdef __cplusplus
} // extern "C"
#endif
