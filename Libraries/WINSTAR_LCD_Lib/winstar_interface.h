#ifndef WINSTAR_INTERFACE_H
#define WINSTAR_INTERFACE_H
#include "lcd_driver.h"
//------------------------------------------------------------------------------
#define clocks_delay(clocks) TIM3->CNT = 0;while(TIM3->CNT < (uint32_t)clocks);
#define INTDIS __disable_interrupt();BUS_PORT->CRH = 0x77777777;clocks_delay(8)
#define INTEN __enable_interrupt();

//------------------------------------------------------------------------------
typedef struct
{
  uint8_t x;
  uint8_t y;
}lcdPoint;
#ifdef __cplusplus
extern "C" {
#endif
//------------------------------------------------------------------------------
void init_clock_timers(void);
//------------------------------------------------------------------------------
void start_lcd_tx(void);
//------------------------------------------------------------------------------
void finish_lcd_tx(void);
//------------------------------------------------------------------------------
void set_lcd_on(void);
//------------------------------------------------------------------------------
void set_lcd_off(void);
//------------------------------------------------------------------------------
void lcd_select(uint8_t cs);
//------------------------------------------------------------------------------
void lcd_set_page(uint8_t x, uint8_t cs);
//------------------------------------------------------------------------------
void lcd_set_line(uint8_t x);
//------------------------------------------------------------------------------
void lcd_show_symbol(uint8_t symbol);
//------------------------------------------------------------------------------
uint8_t lcd_get_status(void);
//------------------------------------------------------------------------------
uint8_t lcd_get_symbol(void);
//------------------------------------------------------------------------------
void set_port_output_PP(GPIO_TypeDef* GPIOx, uint32_t portMask);
//------------------------------------------------------------------------------
void set_port_output_OD(GPIO_TypeDef* GPIOx, uint32_t portMask);
//------------------------------------------------------------------------------
void set_port_input(GPIO_TypeDef* GPIOx, uint32_t portMask);
//------------------------------------------------------------------------------
void init_indication(void);
//------------------------------------------------------------------------------
int clear_LCDBuffer(void);
//------------------------------------------------------------------------------
int redraw_LCD(void);
//------------------------------------------------------------------------------
int LCD_put_pict(const uint8_t *pict, uint8_t xPoint, uint8_t yPoint);
//------------------------------------------------------------------------------
int LCD_put_char(uint8_t x,uint8_t y,uint8_t ch, const uint8_t *font, uint8_t invert);
//------------------------------------------------------------------------------
int get_char_offset(uint8_t ch);
//------------------------------------------------------------------------------
int LCD_put_string(uint8_t *string, lcdPoint start, lcdPoint end, const uint8_t *font, uint8_t userFlags);
//------------------------------------------------------------------------------
int LCD_draw_rect(lcdPoint start, uint32_t width, uint32_t height, uint8_t borderWidth);
//------------------------------------------------------------------------------
int fill_area_solid(lcdPoint start, lcdPoint finish);
//------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif//INTERFACE_H