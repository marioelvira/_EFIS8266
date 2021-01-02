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
  float   senSensivity;   // 4 bytes
} AirsData;

#define AIR_ARRAY_SIZE  5
#define AIR_TICK        1000

#define AIR_DENSITY     1.225     // kg/m^3
#define CONV_MPS_KNOTS  1.94      // m/s to knots
#define CONV_MPS_KMH    3.6       // m/s to km/h
#define CONV_MMH2O_KPA  0.00981   // convesion multiplier from mmH2O to kPa

#define AIR_SENS_INFO_TYPE		    "MPX5010DP"
#define AIR_SENS_INFO_MAX		      "10kPa"
#define AIR_SENS_INFO_SENSIVITY	  "4.413 mV/mmH20"

#define AIR_DIG_OFFSET          55      	// Digital Offset
#define AIR_DIG_EOS             1023    	// Digital End Of Scale
#define AIR_MVOLTS_EOS          3300    	// mVolts Enf Of Scale
#define AIR_SENS_SENSIVITY      3.713   	// 4.413 in mV/mmH2O taken from datasheet. 4.413 * 3.3/5
/*
#define AIR_SENS_INFO_TYPE        "XGZP6897A"
#define AIR_SENS_INFO_MAX         "5kPa"
#define AIR_SENS_INFO_SENSIVITY   "4.413 mV/mmH20"
*/
#endif // _AIRSEEP_H_

#ifdef __cplusplus
} // extern "C"
#endif
