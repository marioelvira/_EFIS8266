#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
#define I2C_CLK     5   // GPIO5 -> D1
#define I2C_DTA     4   // GPIO4 -> D2

#define DI_OUT      0   // GPIO0 -> D3
#define DI_LED      2   // GPIO2 -> D4
#define DI_IN       16  // GPIO16 -> D0

#define DI_ON       0
#define DI_OFF      1

#define IO_ON       1
#define IO_OFF      0

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
