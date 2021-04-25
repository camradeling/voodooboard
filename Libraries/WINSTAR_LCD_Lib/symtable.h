#ifndef SYMTABLE_H
#define SYMTABLE_H
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//------------------------------------------------------------------------------
#define TOTAL_FONTS 1
//------------------------------------------------------------------------------
#define FONT_HEIGHT_ADDRESS 0
#define FONT_MAX_WIDTH_ADDRESS 1
#define FONT_TYPE_ADDRESS 2
#define FONT_DATA_START_ADDRESS 3
#define ASKII_OFFSET 0x20
#define WIDTH_BITMASK_LENGTH 5
//------------------------------------------------------------------------------
extern const uint8_t table_5X8Ymonospace;
//------------------------------------------------------------------------------
extern const uint8_t table_test;
//------------------------------------------------------------------------------
extern const uint8_t font10x8ok;
//------------------------------------------------------------------------------
#endif/*SYMTABLE_H*/
