#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#include "stm32f10x_conf.h"
//------------------------------------------------------------------------------
#define FRAMDEV   1
#define RTCDEV    2
#define ADCDEV    3
//------------------------------------------------------------------------------
#define RTCADDR 0xd0
#define FRAMADDR 0xa0
#define ADC1ADDR 0x90
#define ADC2ADDR 0x92
//------------------------------------------------------------------------------
//#define I2C_DELAY    180
#define I2C_DELAY    720
#define MAX_I2C_PACKET 300
//------------------------------------------------------------------------------
void recover_I2C1(void);
//------------------------------------------------------------------------------
void init_I2C1(void);
//------------------------------------------------------------------------------
#define I2C_IDLE                                0
#define I2C_INITIATING_CONVERSION               1
#define I2C_WRITING_POLLING_ADDR                2
#define I2C_POLLING                             3
#define I2C_WRITING_CONVERSION_ADDR             4
#define I2C_READING_DATA                        5
//------------------------------------------------------------------------------
#define I2C_START_INITIATED                     0
#define I2C_ADDR_GONE                           1
#define I2C_REGADDR_MSB_GONE                    2
#define I2C_REGADDR_LSB_GONE                    3
#define I2C_CONFIG1_GONE                        4
#define I2C_CONFIG2_GONE                        5
#define I2C_ALL_BYTES_TRANSFERRED               6
#define I2C_READING_LSB                         7
#define I2C_READING_MSB                         8
//------------------------------------------------------------------------------
#endif/*I2C_H*/