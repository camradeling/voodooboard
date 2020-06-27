#ifndef ADC_H
#define ADC_H
//------------------------------------------------------------------------------
#include "includes.h"
//------------------------------------------------------------------------------
#define ADS_CONVERSION_REG  0
#define ADS_CONFIG_REG      1
#define ADS_LOW_THRESH_REG  2
#define ADS_HIGH_THRESH_REG 3
//------------------------------------------------------------------------------
#define ADS_COMP_QUE0       (1 << 0)
#define ADS_COMP_QUE1       (1 << 1)
#define ADS_COMP_LAT        (1 << 2)
#define ADS_COMP_POL        (1 << 3)
#define ADS_COMP_MODE       (1 << 4)
#define ADS_DR0             (1 << 5)
#define ADS_DR1             (1 << 6)
#define ADS_DR2             (1 << 7)
#define ADS_MODE            (1 << 8)
#define ADS_PGA0            (1 << 9)
#define ADS_PGA1            (1 << 10)
#define ADS_PGA2            (1 << 11)
#define ADS_MUX0            (1 << 12)
#define ADS_MUX1            (1 << 13)
#define ADS_MUX2            (1 << 14)
#define ADS_OS              (1 << 15)
//------------------------------------------------------------------------------
#define ADS_CONFIG_SIG_MASK      0x05a3
#define ADS_CONFIG_REF_MASK      0x75a3
//------------------------------------------------------------------------------
#endif