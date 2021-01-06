#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UNITS_H_
#define _UNITS_H_

typedef struct
{
  byte   alt;      // 1 byte
  byte   airspeed; // 1 byte
  byte   vario;    // 1 byte
  byte   temp;     // 1 byte
} Units;

#define ALT_FEET		  0
#define ALT_METERS		1

#define AIRS_KNOTS		0
#define AIRS_KMH		  1

#define VARIO_FEETpM  0
#define VARIO_MpM     1
//#define VARIO_FEETpS  2
//#define VARIO_MpS     3

#define TEMP_CELSIUS	  0
#define TEMP_KELVIN		  1
#define TEMP_FARENHEIT	2

#endif // _UNITS_H_

#ifdef __cplusplus
} // extern "C"
#endif
