#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ALTIMETER_H_
#define _ALTIMETER_H_

#define ALT_DETECTION      0
#define ALT_DETECTED       1
#define ALT_WORKING        2
#define ALT_NOT_DETECTED   3

#define ALT_SAMPLERATE_DELAY_MS    100


/*

altitude = (T0/L) * [(P0/P)^(LR/Mg) - 1]

where
T0 = base temperature (defined as 288.15°K at sea level in the standard atmosphere)
L = lapse rate (defined as -0.0065 °K/m in the std atmosphere)
P0 = base pressure
P = pressure at altitude
R = gas constant = 8.314 J/K-mol
M = molecular wt of dry air = 28.95 g/mol = 0.02895 kg/mol
g = standard gravity = 9.807 m/s2

*/
#define Mg_DIV_LR             5.255
#define LR_DIV_Mg             0.190295
#define T0_DIV_L              44330.0

#define CONV_METERS_TO_FEET   3.281

#endif // _ALTIMETER_H_

#ifdef __cplusplus
} // extern "C"
#endif
