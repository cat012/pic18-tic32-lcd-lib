//25-Aug-2020


#include "tic32.h"


extern const uint8_t font5x7[];
extern const uint8_t num16x30[];



//-----------------------------------------------------------------------------
static void tic32_goto(uint8_t line, uint8_t row)
    {
    i2c_start();
    i2c_send_byte(TIC32_ADDRESS | TIC32_WRITE);
    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);

    i2c_send_byte(TIC32_SET_DEFAULT_COMMAND_PAGE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_Y_ADDRESS_RAM | line);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_X_ADDRESS_RAM | row);
    i2c_stop();
    }


//-----------------------------------------------------------------------------
static void tic32_clear(void)  //clear buffer
    {
    for(uint16_t x=0; x<TIC32_BUFF_SIZE; x++) scrbuff[x]=0;
    }


//-----------------------------------------------------------------------------
void tic32_update(void)  //write buffer to screen
    {
    tic32_goto(0,0);

    i2c_start();
    i2c_send_byte(TIC32_ADDRESS | TIC32_WRITE);
    i2c_send_byte(TIC32_DATA | TIC32_SERIAL);

    for(uint16_t k=0; k<TIC32_BUFF_SIZE; k++) i2c_send_byte(scrbuff[k]);

    i2c_stop();

    tic32_clear();
    }


//-----------------------------------------------------------------------------
void tic32_init(void)
    {
    i2c_init();

    TIC32_RESET;

    i2c_start();
    i2c_send_byte(TIC32_ADDRESS | TIC32_WRITE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_SET_DEFAULT_COMMAND_PAGE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_FUNCTION_SET | TIC32_CHIP_ACTIVE | TIC32_HORIZONTAL_ADDRESSING);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_SELECT_COMMAND_PAGE | TIC32_DISPLAY_SETTING_COMMAND_PAGE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_DISPLAY_CONTROL | TIC32_NORMAL_MODE |TIC32_DISPLAY_NORMAL_MODE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_MULTIPLEX_RATE | TIC32_MULTIPLEX_RATE_1_34);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_BIAS_SYSTEM | TIC32_BIAS_SYSTEM_3);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_SET_DEFAULT_COMMAND_PAGE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_SELECT_COMMAND_PAGE | TIC32_HV_GEN_COMMAND_PAGE);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_HV_GEN_CONFIGURATION | TIC32_VOLTAGE_MULTIPLIER_X2);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_TEMPERATURE_CONTROL | TIC32_TEMPERATURE_COEFFICIENT_0);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_HV_GEN_CONTROL | TIC32_VLCD_PROGRAMMING_RANGE_LOW | TIC32_VOLTAGE_MULTIPLIER_ENABLED);

    i2c_send_byte(TIC32_COMMAND | TIC32_ONE);
    i2c_send_byte(TIC32_VLCD_CONTROL | TIC32_CONTRAST);

    i2c_stop();

    tic32_clear();
    tic32_update();
    }


//-----------------------------------------------------------------------------
void tic32_pixel(uint8_t x, uint8_t y)  //x: 0..127  //y: 0..31
    {
    if(x<=127 && y<=31) scrbuff[x+128*(y/8)] |= 1<<(y%8);
    }


//-----------------------------------------------------------------------------
static void tic32_char(uint8_t x, uint8_t y, uint8_t sign)
    {
    if(sign<32 || sign>127) sign=128;

    for(uint8_t i=0; i<5; i++)
        {
        for(uint8_t k=0; k<8; k++)
            {
            if(((font5x7[5*(sign-32)+i])>>(7-k))&1) tic32_pixel(x+i, y-k);
            }
        }
    }


//-----------------------------------------------------------------------------
void tic32_print(uint8_t x, uint8_t y, char *str)
    {
    for(; (*str && x<=127 && y<=31); x+=6) tic32_char(x, y, *str++);
    }


//-------------------------------------------------------------------------------------------------
static void tic32_num16x30(uint8_t x, uint8_t y, uint8_t sign)
    {
    for(uint8_t i=0; (i<60) && (sign>=48) && (sign<=57); i+=2)
        {
        for(uint8_t k=0; k<8; k++)
            {
            if(((num16x30[i+(sign-48)*60])>>(7-k))&1) tic32_pixel(x+k, y-30+i/2);
            if(((num16x30[i+1+(sign-48)*60])>>(7-k))&1) tic32_pixel(x+8+k, y-30+i/2);
            }
        }
    }


//-------------------------------------------------------------------------------------------------
void tic32_print16x30(uint8_t x, uint8_t y, char *str)
    {
    for(; (*str && x<=127); x+=16) tic32_num16x30(x, y, *str++);
    }


//-------------------------------------------------------------------------------------------------
void tic32_line(int8_t x1, int8_t y1, int8_t x2, int8_t y2)  //x: 0..127  //y: 0..31
    {
    int16_t P;

    int8_t x = x1;
    int8_t y = y1;

    int8_t dx = abs((int8_t)(x2-x1));
    int8_t dy = abs((int8_t)(y2-y1));

    int8_t addx, addy;

    if(x1>x2) addx=-1;
    else addx=1;

    if(y1>y2) addy=-1;
    else addy=1;

    if(dx>=dy)
        {
        P=2*dy-dx;

        for(uint8_t k=0; k<=dx; k++)
            {
            tic32_pixel(x, y);

            if(P<0)
                {
                P+=2*dy;
                x+=addx;
                }
            else
                {
                P+=2*dy-2*dx;
                x+=addx;
                y+=addy;
                }
            }
        }
    else
        {
        P=2*dx-dy;

        for(uint8_t k=0; k<=dy; k++)
            {
            tic32_pixel(x, y);

            if(P<0)
                {
                P+=2*dx;
                y+=addy;
                }
            else
                {
                P+=2*dx-2*dy;
                x+=addx;
                y+=addy;
                }
            }
        }
    }

