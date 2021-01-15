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
 *                    A0 -|      |- GPIO16 -> D0 -> OUT
 *                    G  -|      |- GPIO5  -> D1 <> SCL*
 *                    VU -|      |- GPIO4  -> D2 <> SDA*
 *         AS3 <- GPIO10 -|      |- GPIO0  -> D3 <- IN
 *         AS2 <-  GPIO9 -|      |- GPIO2  -> D4 -> LED
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> D5 -> SPI CLK
 *          SK <-   SCLK -|      |- GPIO12 -> D6 -> SPI MISO
 *                     G -|      |- GPIO13 -> D7 -> SPI MOSI
 *                    3V -|      |- GPIO15 -> D8 -> SPI CS
 *                    EN -|      |- GPIO3  -> RX
 *                   RST -|      |- GPIO1  -> TX
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

#define PIN_AIR_IN      A0  // Entrada
 
#define PIN_I2C_CLK     5   // GPIO5 -> D1
#define PIN_I2C_DTA     4   // GPIO4 -> D2

#define PIN_OUT         16  // GPIO16 -> D0
#define PIN_LED         2   // GPIO2 -> D4
#define PIN_IN          0   // GPIO0 -> D3

#define PIN_OUT_ON      1
#define PIN_OUT_OFF     0

#define PIN_IN_OFF      1

// IO definition
#define IO_ON       1
#define IO_OFF      0

// Temporizaciones UpPulsaciones
#define NO_PULSACION          0     // x10ms
#define PULSACION_CORTA       50    // x10ms
#define PULSACION_LARGA       150   // x10ms
#define PULSACION_ERROR       10    // x10ms

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
