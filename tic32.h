//25-Aug-2020


#ifndef TIC32_H
#define	TIC32_H


#include <xc.h>
#include <stdlib.h>
#include <stdint.h>

#include "i2c.h"


#define TIC32_BUFF_SIZE  512  //columns*strings(pages)=128*4

uint8_t scrbuff[TIC32_BUFF_SIZE];


////////////////////////////////////////////////////////////////

#define TIC32_RST_TRIS  TRISBbits.RB2
#define TIC32_RST_LAT   LATBbits.LATB2

////////////////////////////////////////////////////////////////


#define TIC32_RESET  TIC32_RST_LAT=1; TIC32_RST_TRIS=0


//VLCD register  0..127
#define TIC32_CONTRAST 58

//I2C chip address
#define TIC32_ADDRESS  0x78


#define TIC32_RW_H  0b00000001
#define TIC32_RW_L  0b00000000

#define TIC32_CO_H  0b10000000
#define TIC32_CO_L  0b00000000

#define TIC32_RS_H  0b01000000
#define TIC32_RS_L  0b00000000

#define TIC32_READ   TIC32_RW_H
#define TIC32_WRITE  TIC32_RW_L

#define TIC32_DATA     TIC32_RS_H
#define TIC32_COMMAND  TIC32_RS_L

#define TIC32_ONE     TIC32_CO_H
#define TIC32_SERIAL  TIC32_CO_L


#define TIC32_SET_DEFAULT_COMMAND_PAGE  0b00000001


#define TIC32_SELECT_COMMAND_PAGE            0b00001000

#define TIC32_FUNCTION_AND_RAM_COMMAND_PAGE  0b00000000
#define TIC32_DISPLAY_SETTING_COMMAND_PAGE   0b00000001
#define TIC32_HV_GEN_COMMAND_PAGE            0b00000010


/* function and RAM command page */

#define TIC32_FUNCTION_SET           0b00100000

#define TIC32_CHIP_ACTIVE            0b00000000
#define TIC32_CHIP_POWER_DOWN        0b00000100

#define TIC32_HORIZONTAL_ADDRESSING  0b00000000
#define TIC32_VERTICAL_ADDRESSING    0b00000010

#define TIC32_Y_ADDRESS_RAM  0b01000000
#define TIC32_X_ADDRESS_RAM  0b10000000


/* display setting command page */

#define TIC32_MULTIPLEX_RATE       0b00000100

#define TIC32_MULTIPLEX_RATE_1_17  0b00000000
#define TIC32_MULTIPLEX_RATE_1_26  0b00000010
#define TIC32_MULTIPLEX_RATE_1_34  0b00000001


#define TIC32_DISPLAY_CONTROL       0b00001000

#define TIC32_NORMAL_MODE           0b00000000
#define TIC32_ICON_MODE             0b00000010

#define TIC32_DISPLAY_BLANK         0b00000000
#define TIC32_DISPLAY_NORMAL_MODE   0b00000100
#define TIC32_ALL_DISPLAY_SEGMENTS  0b00000001
#define TIC32_INVERSE_VIDEO_MODE    0b00000101


#define TIC32_BIAS_SYSTEM    0b00010000

#define TIC32_BIAS_SYSTEM_7  0b00000000
#define TIC32_BIAS_SYSTEM_6  0b00000001
#define TIC32_BIAS_SYSTEM_5  0b00000010
#define TIC32_BIAS_SYSTEM_4  0b00000011
#define TIC32_BIAS_SYSTEM_3  0b00000100
#define TIC32_BIAS_SYSTEM_2  0b00000101
#define TIC32_BIAS_SYSTEM_1  0b00000110
#define TIC32_BIAS_SYSTEM_0  0b00000111


/* HV-gen command page */

#define TIC32_HV_GEN_CONTROL              0b00000100

#define TIC32_VLCD_PROGRAMMING_RANGE_LOW  0b00000000
#define TIC32_VLCD_PROGRAMMING_RANGE_HIGH 0b00000010

#define TIC32_VOLTAGE_MULTIPLIER_DISABLED  0b00000000
#define TIC32_VOLTAGE_MULTIPLIER_ENABLED   0b00000001


#define TIC32_HV_GEN_CONFIGURATION   0b00001000

#define TIC32_VOLTAGE_MULTIPLIER_X2  0B00000000
#define TIC32_VOLTAGE_MULTIPLIER_X3  0B00000001
#define TIC32_VOLTAGE_MULTIPLIER_X4  0B00000010
#define TIC32_VOLTAGE_MULTIPLIER_X5  0B00000011


#define TIC32_TEMPERATURE_CONTROL        0b00100000

#define TIC32_TEMPERATURE_COEFFICIENT_0  0b00000000
#define TIC32_TEMPERATURE_COEFFICIENT_1  0b00000001
#define TIC32_TEMPERATURE_COEFFICIENT_2  0b00000010
#define TIC32_TEMPERATURE_COEFFICIENT_3  0b00000011
#define TIC32_TEMPERATURE_COEFFICIENT_4  0b00000100
#define TIC32_TEMPERATURE_COEFFICIENT_5  0b00000101
#define TIC32_TEMPERATURE_COEFFICIENT_6  0b00000110
#define TIC32_TEMPERATURE_COEFFICIENT_7  0b00000111


#define TIC32_VLCD_CONTROL  0b10000000


void tic32_init(void);

void tic32_update(void);
void tic32_pixel(uint8_t x, uint8_t y);
void tic32_print(uint8_t x, uint8_t y, char *str);
void tic32_line(int8_t x1, int8_t y1, int8_t x2, int8_t y2);

void tic32_print16x30(uint8_t x, uint8_t y, char *str);


#endif	/* TIC32_H */

