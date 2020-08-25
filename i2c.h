// Software I2C
//
// i2c.h
// Microchip XC8 Compiler v1.33
//
// 25-Aug-2020
// i2c.h
//
// 25-Aug-2020


#ifndef I2C_H
#define	I2C_H


#include <xc.h>

#include <stdint.h>

#define _XTAL_FREQ 8000000


#define I2C_FAST 0


#if I2C_FAST
#define I2C_DELAY  asm("NOP")
#else
#define I2C_DELAY  __delay_us(5)
#endif


///////////////////////////////////////////////////////////////////////////////

#define I2C_SDA_PIN   PORTBbits.RB1
#define I2C_SDA_TRIS  TRISBbits.RB1
#define I2C_SDA_LAT   LATBbits.LATB1

#define I2C_SCK_PIN   PORTBbits.RB0
#define I2C_SCK_TRIS  TRISBbits.RB0
#define I2C_SCK_LAT   LATBbits.LATB0

///////////////////////////////////////////////////////////////////////////////


#define I2C_SDA_CLR  I2C_SDA_LAT=0
#define I2C_SDA_SET  I2C_SDA_LAT=1
#define I2C_SDA_OUT  I2C_SDA_TRIS=0
#define I2C_SDA_INP  I2C_SDA_TRIS=1

#define I2C_SCK_CLR  I2C_SCK_LAT=0
#define I2C_SCK_SET  I2C_SCK_LAT=1
#define I2C_SCK_OUT  I2C_SCK_TRIS=0
#define I2C_SCK_INP  I2C_SCK_TRIS=1


#define I2C_SDA_PULL  I2C_SDA_INP
#define I2C_SDA_NULL  I2C_SDA_CLR; I2C_SDA_OUT

#define I2C_SDA_IS_PULL  I2C_SDA_PIN==1

#define I2C_SCK_PULL  I2C_SCK_INP
#define I2C_SCK_NULL  I2C_SCK_CLR; I2C_SCK_OUT


#define I2C_ACK   0
#define I2C_NACK  1



void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_send_byte(uint8_t data);
uint8_t i2c_read_byte(uint8_t ack);


#endif	/* I2C_H */

