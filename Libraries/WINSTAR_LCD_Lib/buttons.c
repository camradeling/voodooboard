#include <stdint.h>
#include "winstar_interface.h"
#include "buttons.h"
#include "hardware_config.h"
#include "app_config.h"
//------------------------------------------------------------------------------
uint8_t allButtons[NUMBER_OF_BUTTON_BLOCKS];
uint32_t restoreButtonsPort = 0;
uint32_t keyCode = NONE;
//------------------------------------------------------------------------------
#ifdef DOZATOR2
//------------------------------------------------------------------------------
char* buttonsDecode[] =
{
  "None",
  "Ч",
  "С",//
  "Н",//
  "Б",//
  "Д4",//
  "Д3",//
  "Д2",//
  "Д1",//
  "7",//
  "4",//
  "1",//
  "0",//
  "8",//
  "5",//
  "2",//
  ".",//
  "9",//
  "6",//
  "3",//
  "Ввод",//
  "Ф1",//
  "#",//
  "<",//
  "Р"//
};
//------------------------------------------------------------------------------
void read_buttons(void)
{
  for(int i = 0; i < NUMBER_OF_BUTTON_BLOCKS; i++)
  {
    restoreButtonsPort = BUS_PORT->ODR & ~(0xff << BUS_PORT_OFFSET);
    set_port_output_OD(BUTTONS_PORT, 0xff00);
    BUTTONS_PORT->ODR = restoreButtonsPort | (1 << (i + BUS_PORT_OFFSET));
    SYN_SCAN_PORT->BRR = (1 << SYN_SCAN);
    SYN_SCAN_PORT->BSRR = (1 << SYN_SCAN);
    set_port_input(BUTTONS_PORT, 0xff00);
    LCD_CONTROL_PORT->ODR &= ~(1 << IN_KEY);
    uint8_t temp = ~((BUS_PORT->IDR & 0xFF00) >> 8);
    for(int j = 0; j < BUTTONS_IN_BLOCK; j++)
    {
      if(temp & (1 << j))
      {
        allButtons[i] |= (1 << j);
      }
      else
      {
        allButtons[i] &= ~(1 << j);
      }
    }
    LCD_CONTROL_PORT->ODR |= (1 << IN_KEY);
    //set_port_output_OD(BUTTONS_PORT, 0xff00);
  }
  //BUTTONS_PORT->ODR = restoreButtonsPort | (0xff << BUS_PORT_OFFSET);
}
//------------------------------------------------------------------------------
#else
//------------------------------------------------------------------------------
char* buttonsDecode[] =
{
  "None",
  "К",
  "Ф1",
  "И",
  "Ф2",
  "Вверх",
  "Влево",
  "Вниз",
  "Вправо",
  "7",
  "8",
  "9",
  "П",
  "4",
  "5",
  "6",
  "#",
  "1",
  "2",
  "3",
  "<",
  "0",
  ".",
  "Ввод",
  "X"
};
//------------------------------------------------------------------------------
void read_buttons(void)
{
  for(int i = 0; i < BUTTONS_IN_BLOCK; i++)
  {
    restoreButtonsPort = BUTTONS_PORT->ODR & ~(0x000000ff << LCD_SEGMENTS_PORT_OFFSET);
    lcd_574_keys &= 0xff0f;
    BUTTONS_PORT->ODR = restoreButtonsPort | (lcd_574_keys << LCD_SEGMENTS_PORT_OFFSET)|(1 << (i + BUTTON_NUMBER_OFFSET));
    LCD_CONTROL_PORT->ODR &= ~(1 << CL1_LCD);
    LCD_CONTROL_PORT->ODR |= (1 << CL1_LCD);
    set_port_input(BUTTONS_PORT, 0x00ff);
    LCD_CONTROL_PORT->ODR &= ~(1 << CL1_KEYS);
    uint8_t temp = BUTTONS_PORT->IDR;
    for(int j = 0; j < NUMBER_OF_BUTTON_BLOCKS; j++)
    {
      if(temp & (1 << j))
      {
        allButtons[j] |= (1 << i);
      }
      else
      {
        allButtons[j] &= ~(1 << i);
      }
    }
    LCD_CONTROL_PORT->ODR |= (1 << CL1_KEYS);
    set_port_output_PP(BUTTONS_PORT, 0x00ff);
  }
  lcd_574_keys &= 0xff0f;
  restoreButtonsPort = BUTTONS_PORT->ODR & ~(0x000000ff << LCD_SEGMENTS_PORT_OFFSET);
  BUTTONS_PORT->ODR = restoreButtonsPort | (lcd_574_keys << LCD_SEGMENTS_PORT_OFFSET);
}
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
void get_key_code(void)
{
  uint8_t flag = 0;
  for(uint8_t i = 0; i < NUMBER_OF_BUTTON_BLOCKS; i++)
  {
    for(uint8_t j = 0; j < BUTTONS_IN_BLOCK; j++)
    {
      if(allButtons[i] & (1 << j))
      {
        keyCode = i * BUTTONS_IN_BLOCK + j + 1;
        flag = 1;
        break;
      }
    }
    if(flag)
      break;
  }
  if(!flag)
    keyCode = NONE;
}
//------------------------------------------------------------------------------
