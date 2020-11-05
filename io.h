#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
/*
 *                        --------
 *                    A0 -|      |- GPIO16 -> D0 <- IN
 *                    G  -|      |- GPIO5  -> D1 <> SCL*
 *                    VU -|      |- GPIO4  -> D2 <> SDA*
 *         AS3 <- GPIO10 -|      |- GPIO0  -> D3 -> OUT
 *         AS2 <-  GPIO9 -|      |- GPIO2  -> D4 -> LED
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> D5
 *          SK <-   SCLK -|      |- GPIO12 -> D6
 *                     G -|      |- GPIO13 -> D7
 *                    3V -|      |- GPIO15 -> D8
 *                    EN -|      |- GPIO3  -> RX
 *                   RST -|      |- GPIO1  -> TX
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

#define PIN_AIR_IN      A0  // Entrada
 
#define PIN_I2C_CLK     5   // GPIO5 -> D1
#define PIN_I2C_DTA     4   // GPIO4 -> D2

#define PIN_OUT         0   // GPIO0 -> D3
#define PIN_LED         2   // GPIO2 -> D4
#define PIN_IN          16  // GPIO16 -> D0

#define PIN_OUT_ON      1
#define PIN_OUT_OFF     0

#define PIN_IN_OFF      1

// IO definition
#define IO_ON       1
#define IO_OFF      0

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
