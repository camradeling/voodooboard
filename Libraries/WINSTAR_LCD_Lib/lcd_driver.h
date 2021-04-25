#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdarg.h>
//#include "stm32f10x_lib.h"
#include "stm32f10x_it.h"
#include "hardware_config.h"
#include "primitive_lib.h"
#include "symtable.h"
//#include "buttons.h"
//------------------------------------------------------------------------------
/*additional includes*/
#include "FreeRTOS.h"
//------------------------------------------------------------------------------
#ifndef INC_FREERTOS_H
#define configCPU_CLOCK_HZ ( ( unsigned long ) 72000000 )
#endif
//------------------------------------------------------------------------------
#define LCD1_OFFSET 0
#define LCD2_OFFSET 64
#define LCD_BUFFER_LENGTH 1024
/*ширина кодировани€ высоты и ширины картинки*/
#define LCD_PIC_DATA_TYPE uint8_t
//#define LCD_PIC_HEIGHT_LENGTH 1
//#define LCD_PIC_WIDTH_LENGTH 1
#define LCD_PIC_WIDTH_ADDRESS 0
#define LCD_PIC_HEIGHT_ADDRESS 1
#define LCD_PICT_DATA_ADDRESS 2
#define USING_TEXT
//------------------------------------------------------------------------------
#define US_CALC (configCPU_CLOCK_HZ / 1000000)
#define TDSW_CLOCKS (200 * US_CALC / 1000)
#define TWIE_CLOCKS (500 * US_CALC / 1000)
#define TWHE_CLOCKS TWIE_CLOCKS
#define TAS_CLOCKS (140 * US_CALC /1000)
#define TDHR_CLOCKS (20 * US_CALC /1000)
#define TDDR_CLOCKS (300 * US_CALC /1000)
#define TAH_CLOCKS (10 * US_CALC / 1000)
//------------------------------------------------------------------------------
#define LCD_HEIGHT 64
#define LCD_PAGE_HEIGHT 8
#define LCD_WIDTH 128
#define MIN_SYMBOL_HEIGHT 5
#define WIDTH_OUT_OF_BOUNDS 1
#define HEIGHT_OUT_OF_BOUNDS 2
#define BUFFER_NOT_INITIALISED 3
#define STRING_TOO_LONG 4
#define OK 0
//------------------------------------------------------------------------------
#define HALIGN_BIT 0
#define HALIGN_LEFT (0 << HALIGN_BIT)
#define HALIGN_CENTER (0x01 << HALIGN_BIT)
#define HALIGN_RIGHT (0x02 << HALIGN_BIT)
#define VALIGN_BIT 2
#define VALIGN_TOP (0 << VALIGN_BIT)
#define VALIGN_MIDDLE (0x01 << VALIGN_BIT)
#define VALIGN_BOTTOM (0x02 << VALIGN_BIT)
#define NO_SPLIT_BIT 4
#define NO_SPLIT (1 << NO_SPLIT_BIT)
#define SPLIT (0 << NO_SPLIT_BIT)
#define TRUNCATE_BIT 5
#define TRUNCATE_IF_TOO_LONG (1 << TRUNCATE_BIT)
#define ERR_IF_TOO_LONG (0 << TRUNCATE_BIT)
#define INVERTION_BIT 6
#define INVERTION (1 << INVERTION_BIT)
#define LCD_DEFAULT_FLAGS 0x00|HALIGN_CENTER|VALIGN_MIDDLE|SPLIT|ERR_IF_TOO_LONG
//------------------------------------------------------------------------------
/*Ѕуфер видеопам€ти. Ќужно об€зательно инициализировать, чтобы было изображение)))*/
extern const uint8_t lcdRamInitial[];
extern uint16_t lcd_574_keys;
extern uint8_t highByte;
extern uint32_t restorePort;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif /*LCD_DRIVER_H*/