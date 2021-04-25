/*Здесь функции для работы с кнопками и индикаторами на плате индикации*/
#include "winstar_interface.h"
#include "stm32f10x_it.h"
//------------------------------------------------------------------------------
//Глобальные переменные---------------------------------------------------------
GPIO_InitTypeDef        GPIO_InitStructure;
//------------------------------------------------------------------------------
uint8_t * lcdRamMirror;
//------------------------------------------------------------------------------
uint16_t lcd_574_keys = 0x00; 
uint8_t highByte = 0x00;
uint32_t restorePort = 0x00;
//------------------------------------------------------------------------------
void init_clock_timers()
{
  TIM_TimeBaseInitTypeDef timerInitStructure;
#ifndef GAZVES
  timerInitStructure.TIM_Prescaler = 7;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 0xffff;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM4, &timerInitStructure);
  TIM_Cmd(TIM4, ENABLE);
#endif
#ifdef DOZATOR2
  timerInitStructure.TIM_Prescaler = 7;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 0xffff;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3, &timerInitStructure);
  TIM_Cmd(TIM3, ENABLE);
#else
  timerInitStructure.TIM_Prescaler = 7;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 0xffff;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3, &timerInitStructure);
  TIM_Cmd(TIM3, ENABLE);
#endif
  timerInitStructure.TIM_Prescaler = 1;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 36000;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM2, &timerInitStructure);
  TIM_Cmd(TIM2, ENABLE);
}
//------------------------------------------------------------------------------
void set_lcd_on(void)
{ 
#ifdef DOZATOR2
  INTDIS;
#endif
  lcd_574_keys &= ~(1 << DI_SIG);
  lcd_574_keys &= ~(1 << CS1_SIG);
  lcd_574_keys |= (1 << CS2_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  clocks_delay(TWHE_CLOCKS - TDSW_CLOCKS);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort | (0x3f << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TDSW_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(TAH_CLOCKS);
#ifdef DOZATOR2
  INTEN;
  INTDIS;
#endif
  lcd_574_keys &= ~(1 << DI_SIG);
  lcd_574_keys |= (1 << CS1_SIG);
  lcd_574_keys &= ~(1 << CS2_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  clocks_delay(TWHE_CLOCKS - TDSW_CLOCKS);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort | (0x3f << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TDSW_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(TAH_CLOCKS);
#ifdef DOZATOR2
  INTEN;
#endif
}
//------------------------------------------------------------------------------
void set_lcd_off(void)
{ 
#ifdef DOZATOR2
  INTDIS;
#endif
  lcd_574_keys &= ~(1 << DI_SIG);
  lcd_574_keys &= ~(1 << CS1_SIG);
  lcd_574_keys |= (1 << CS2_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  clocks_delay(TWHE_CLOCKS - TDSW_CLOCKS);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort | (0x3e << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TDSW_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(TAH_CLOCKS);
#ifdef DOZATOR2
  INTEN;
  INTDIS;
#endif
  lcd_574_keys &= ~(1 << DI_SIG);
  lcd_574_keys |= (1 << CS1_SIG);
  lcd_574_keys &= ~(1 << CS2_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  clocks_delay(TWHE_CLOCKS - TDSW_CLOCKS);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort | (0x3e << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TDSW_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(TAH_CLOCKS);
#ifdef DOZATOR2
  INTDIS;
#endif
}
//------------------------------------------------------------------------------
void lcd_select(uint8_t cs)
{
  if(cs == 1)
  {
    lcd_574_keys &= ~(1 << CS1_SIG);
    lcd_574_keys |= (1 << CS2_SIG);
    restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
    LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
    CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
    CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  }
  else if(cs == 2)
  {
    lcd_574_keys |= (1 << CS1_SIG);
    lcd_574_keys &= ~(1 << CS2_SIG);
    restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
    LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
    CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
    CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  }
}
//------------------------------------------------------------------------------
void lcd_set_page(uint8_t x, uint8_t cs)
{
#ifdef DOZATOR2
  INTDIS;
#endif
  lcd_574_keys &= ~(1 << DI_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  lcd_select(cs);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort | ((0xB8 | x) << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TWIE_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(8);
#ifdef DOZATOR2
  INTEN;
#endif
}
//------------------------------------------------------------------------------
void lcd_set_line(uint8_t x)
{
#ifdef DOZATOR2
  INTDIS;
#endif
  lcd_574_keys &= ~(1 << DI_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort | ((0x40 | x) << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TWIE_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(8);
#ifdef DOZATOR2
  INTEN;
#endif
}
//------------------------------------------------------------------------------
void lcd_show_symbol(uint8_t symbol)
{
#ifdef DOZATOR2
  INTDIS;
#endif
  lcd_574_keys |= (1 << DI_SIG);
  restorePort = LCD_CONTROL_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_CONTROL_PORT->ODR = restorePort | lcd_574_keys;
  CL1_LCD_PORT->ODR &= ~(1 << CL1_LCD);
  CL1_LCD_PORT->ODR |= (1 << CL1_LCD);
  clocks_delay(TAS_CLOCKS);
  LCD_EN_PORT->BSRR  |= (1 << EN_SIG);
  restorePort = LCD_SEGMENTS_PORT->ODR & ~(0xff << LCD_SEGMENTS_PORT_OFFSET);
  LCD_SEGMENTS_PORT->ODR = restorePort |(symbol << LCD_SEGMENTS_PORT_OFFSET);
  clocks_delay(TWIE_CLOCKS);
  LCD_EN_PORT->BRR  |= (1 << EN_SIG);
  clocks_delay(8);
#ifdef DOZATOR2
  INTEN;
#endif
}
//------------------------------------------------------------------------------
void set_port_output_PP(GPIO_TypeDef* GPIOx, uint32_t portMask)
{
  GPIO_InitStructure.GPIO_Pin = portMask;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
//------------------------------------------------------------------------------
void set_port_output_OD(GPIO_TypeDef* GPIOx, uint32_t portMask)
{
  GPIO_InitStructure.GPIO_Pin = portMask;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
//------------------------------------------------------------------------------
void set_port_input(GPIO_TypeDef* GPIOx, uint32_t portMask)
{
  GPIO_InitStructure.GPIO_Pin = portMask;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
//------------------------------------------------------------------------------
void init_indication(void)
{
  set_port_output_PP(LCD_EN_PORT, (1 << EN_SIG));
  set_port_output_PP(LCD_BL_PORT, (1 << LCD_BL));
  set_port_output_PP(LCD_HIGHZ_PORT, (1 << HIGHZ_5V));
  set_port_output_PP(LCD_SEGMENTS_PORT, 0x00ff);
  set_port_output_PP(LCD_CONTROL_PORT, (1 << CL1_LCD));
  //set_port_output(LCD_CONTROL_PORT, (1 << CL1_KEYS));
}
//------------------------------------------------------------------------------
int clear_LCDBuffer()
{
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED;
  for(int i = 0; i < LCD_BUFFER_LENGTH; i++)
  {
    lcdRamMirror[i] = 0x00;
  }
  return OK;
}
//------------------------------------------------------------------------------
int redraw_LCD()
{
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED; 
    for(int i = 0; i < 8; i++)
    {
      lcd_set_page(i, CS1);
      lcd_set_line(0);
      for(int j = 0; j < LCD_WIDTH/2; j++)
      {
        lcd_show_symbol(lcdRamMirror[i * (LCD_WIDTH/2 + LCD2_OFFSET) + j + LCD1_OFFSET]);
      }
    }
    for(int i = 0; i < 8; i++)
    {
      lcd_set_page(i, CS2);
      lcd_set_line(0);
      for(int j = 0; j < LCD_WIDTH/2; j++)
      {
        lcd_show_symbol(lcdRamMirror[i * (LCD_WIDTH/2 + LCD2_OFFSET) + j + LCD2_OFFSET]);
      }
    }
    return OK;
}
//------------------------------------------------------------------------------
int LCD_put_pict(const uint8_t *pict, uint8_t xPoint, uint8_t yPoint)
{
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED;
  LCD_PIC_DATA_TYPE width = pict[LCD_PIC_WIDTH_ADDRESS];
  LCD_PIC_DATA_TYPE height = pict[LCD_PIC_HEIGHT_ADDRESS];
  if(xPoint >= LCD_WIDTH - width)
    return WIDTH_OUT_OF_BOUNDS;
  if(yPoint >= LCD_HEIGHT - height)
    return HEIGHT_OUT_OF_BOUNDS;
  uint8_t startPage = yPoint / LCD_PAGE_HEIGHT;
  uint8_t finishPage = (yPoint + height) / LCD_PAGE_HEIGHT;
  if((yPoint + height) % LCD_PAGE_HEIGHT == 0)
    finishPage--;
  uint8_t startLine = xPoint;
  uint8_t yStartOffset = yPoint - startPage * LCD_PAGE_HEIGHT;
  uint8_t yFinishOffset = 8 - (yPoint + height - finishPage * LCD_PAGE_HEIGHT);
  uint8_t lbMask;
  uint8_t hbMask;
  int index = LCD_PICT_DATA_ADDRESS * 8;
  uint8_t picBitOffset;
  for(int j = startLine; j < (startLine + width); j++)
  {
    for(int i = startPage; i <= finishPage; i++)
    {
      lbMask = (i == startPage)?yStartOffset:0;
      hbMask = (i == finishPage)?yFinishOffset:0;
      uint8_t pixelsNeeded = 8 - lbMask - hbMask;
      uint8_t mask = (0xff << lbMask) & (0xff >> hbMask);
      uint8_t byte = lcdRamMirror[i * LCD_WIDTH + j];
      byte &= ~mask;
      uint8_t pixelsWritten = 0;
      while(pixelsNeeded)
      {
        picBitOffset = index % 8;
        if(picBitOffset > lbMask)
        {
          byte |= (pict[index / 8] >> (picBitOffset - lbMask)) & mask;
          if(pixelsNeeded > (8 - picBitOffset))
          {
            pixelsWritten = 8 - picBitOffset;
            index += pixelsWritten;
            pixelsNeeded -= pixelsWritten;
          }
          else
          {
            pixelsWritten = pixelsNeeded;
            index += pixelsWritten;
            pixelsNeeded = 0;
          }  
        }
        else if(picBitOffset <= lbMask)
        {
          byte |= (pict[index / 8] << (lbMask + pixelsWritten - picBitOffset)) & mask;
          index += pixelsNeeded;
          pixelsNeeded = 0;
        }
      }
      lcdRamMirror[i * LCD_WIDTH + j] = byte;
    }
  }
  return OK;
}
//------------------------------------------------------------------------------
int LCD_put_char(uint8_t xPoint, uint8_t yPoint, uint8_t ch, const uint8_t *font, uint8_t invert)
{
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED;
  uint8_t maxwidth = font[FONT_MAX_WIDTH_ADDRESS];
  uint8_t height = font[FONT_HEIGHT_ADDRESS];
  int charBitAddress = (ch - get_char_offset(ch)) * ((height * maxwidth)+WIDTH_BITMASK_LENGTH) + FONT_DATA_START_ADDRESS * 8;
  uint8_t actualWidth = 0;
  for(int i = 0; i < WIDTH_BITMASK_LENGTH; i++)
  {
    actualWidth |= (((font[charBitAddress / 8] & (0x00|(1 << (charBitAddress % 8))))?1:0) << i);
    charBitAddress++;
  }
  if(xPoint >= LCD_WIDTH - actualWidth)
    return WIDTH_OUT_OF_BOUNDS;
  if(yPoint >= LCD_HEIGHT - height)
    return HEIGHT_OUT_OF_BOUNDS;
  uint8_t startPage = yPoint / LCD_PAGE_HEIGHT;
  uint8_t finishPage = (yPoint + height) / LCD_PAGE_HEIGHT;
  if((yPoint + height) % LCD_PAGE_HEIGHT == 0)
    finishPage--;
  uint8_t startLine = xPoint;
  uint8_t yStartOffset = yPoint - startPage * LCD_PAGE_HEIGHT;
  uint8_t yFinishOffset = 8 - (yPoint + height - finishPage * LCD_PAGE_HEIGHT);
  uint8_t lbMask;
  uint8_t hbMask;
  int index = charBitAddress;
  uint8_t fontBitOffset;
  for(int j = startLine; j < (startLine + actualWidth); j++)
  {
    for(int i = startPage; i <= finishPage; i++)
    {
      lbMask = (i == startPage)?yStartOffset:0;
      hbMask = (i == finishPage)?yFinishOffset:0;
      uint8_t pixelsNeeded = 8 - lbMask - hbMask;
      uint8_t mask = (0xff << lbMask) & (0xff >> hbMask);
      uint8_t byte = lcdRamMirror[i * LCD_WIDTH + j];
      byte &= ~mask;
      uint8_t pixelsWritten = 0;
      while(pixelsNeeded)
      {
        fontBitOffset = index % 8;
        if(fontBitOffset > lbMask)
        {
          byte |= (font[index / 8] >> (fontBitOffset - lbMask)) & mask;
          if(pixelsNeeded > (8 - fontBitOffset))
          {
            pixelsWritten = 8 - fontBitOffset;
            index += pixelsWritten;
            pixelsNeeded -= pixelsWritten;
          }
          else
          {
            pixelsWritten = pixelsNeeded;
            index += pixelsWritten;
            pixelsNeeded = 0;
          }
          
        }
        else if(fontBitOffset <= lbMask)
        {
          byte |= (font[index / 8] << (lbMask + pixelsWritten - fontBitOffset)) & mask;
          index += pixelsNeeded;
          pixelsNeeded = 0;
        }
      }
      lcdRamMirror[i * LCD_WIDTH + j] = invert?(~byte & mask):byte;
    }
  }
  return OK;										
}
//------------------------------------------------------------------------------
int get_char_offset(uint8_t ch)
{
  if(ch >= 0x20 && ch <= 0x7E)
    return 0x20;
  else if(ch == 0xa8)
    return 0x44;
  else if(ch == 0xb8)
    return 0x52;
  else if(ch >= 0xc0)
    return 0x5f;
  else
    return 0x00;
}
//------------------------------------------------------------------------------
int LCD_put_string(uint8_t *string, lcdPoint start, lcdPoint end, const uint8_t *font, uint8_t userFlags)
{
  /*va_list ap;
  va_start(ap, count);
  uint8_t userFlags = va_arg(ap, uint8_t);
  va_end(ap);*/
  uint8_t flags = LCD_DEFAULT_FLAGS;
  if((userFlags != 0x00) && (userFlags != 0xff))
    flags = userFlags;
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED;
  int index = 0;
  int symbols = 0;
  int xP = start.x;
  int yP = start.y;
  uint8_t maxwidth = font[FONT_MAX_WIDTH_ADDRESS];
  uint8_t height = font[FONT_HEIGHT_ADDRESS];
  uint8_t maxLines = (end.y - start.y) / height;
  uint8_t lineChars[LCD_HEIGHT / MIN_SYMBOL_HEIGHT];
  uint8_t linePixels[LCD_HEIGHT / MIN_SYMBOL_HEIGHT];
  for(int i = 0; i < LCD_HEIGHT / MIN_SYMBOL_HEIGHT; i++)
  {
    lineChars[i] = 0;
    linePixels[i] = 0;
  }
  int spaceBitAddress = (' ' - get_char_offset(string[index])) * ((height * maxwidth)+WIDTH_BITMASK_LENGTH) + FONT_DATA_START_ADDRESS * 8;
  uint8_t spaceWidth = 0;
  for(int j = 0; j < WIDTH_BITMASK_LENGTH; j++)
  {
    spaceWidth |= (((font[spaceBitAddress / 8] & (0x00|(1 << (spaceBitAddress % 8))))?1:0) << j);
    spaceBitAddress++;
  }
  if((flags & NO_SPLIT) != NO_SPLIT)
  {
    int theLine = 0;
    while(string[index]!= 0x00)
    {     
      int charBitAddress = (string[index] - get_char_offset(string[index])) * ((height * maxwidth)+WIDTH_BITMASK_LENGTH) + FONT_DATA_START_ADDRESS * 8;
      uint8_t actualWidth = 0;
      for(int j = 0; j < WIDTH_BITMASK_LENGTH; j++)
      {
        actualWidth |= (((font[charBitAddress / 8] & (0x00|(1 << (charBitAddress % 8))))?1:0) << j);
        charBitAddress++;
      }
      if(xP + actualWidth <= end.x)
      {
        lineChars[theLine]++;
        symbols++;
        if(xP == start.x && string[index] == ' ')
        {
          index++;
          continue;
        }
        xP +=actualWidth;
        linePixels[theLine] += actualWidth;
        index++;
      }
      else 
      {
        if(yP + height <= end.y)
        {
          if(string[index - 1] == ' ')
          {
            linePixels[theLine] -= spaceWidth;
          }
          xP = start.x;
          yP += height;
          theLine++;  
        }
        else
        {
          if((flags & TRUNCATE_IF_TOO_LONG) != TRUNCATE_IF_TOO_LONG)
            return STRING_TOO_LONG;
          else
            break;
        }
      }
    }
  }
  index = 0;
  yP = start.y;
  uint8_t actualLines = 0;
  for(int i = 0; i < maxLines; i++)
  {
    if(lineChars[i] == 0)
      break;
    else
      actualLines++;
  }
  if((flags & VALIGN_MIDDLE) == VALIGN_MIDDLE)
  {
    yP += (end.y - start.y - actualLines * height) / 2;
  }
  else if((flags & VALIGN_BOTTOM) == VALIGN_BOTTOM)
  {
    yP += end.y - start.y - actualLines * height;
  }
  for(int i = 0; i < actualLines; i++)
  {
    if(index >= symbols)
      break;
    xP = start.x;
    if((flags & HALIGN_RIGHT) == HALIGN_RIGHT)
    {
      xP += end.x - start.x - linePixels[i];
    }
    if((flags & HALIGN_CENTER) == HALIGN_CENTER)
    {
      xP += (end.x - start.x - linePixels[i]) / 2;
    }
    for(int j = 0; j < lineChars[i]; j++)
    {
      if(string[index] == ' ')
      {
        if(j == 0)
          index++;
        else if(j == lineChars[i] - 1)
        {
          index++;
          continue;
        }
      } 
      int charBitAddress = (string[index] - get_char_offset(string[index])) * ((height * maxwidth)+WIDTH_BITMASK_LENGTH) + FONT_DATA_START_ADDRESS * 8;
      uint8_t actualWidth = 0;
      for(int k = 0; k < WIDTH_BITMASK_LENGTH; k++)
      {
        actualWidth |= (((font[charBitAddress / 8] & (0x00|(1 << (charBitAddress % 8))))?1:0) << k);
        charBitAddress++;
      }
      uint8_t invert = (flags & INVERTION)?1:0;
      LCD_put_char(xP, yP, string[index], font, invert);
      xP +=actualWidth;
      index++; 
    }
    yP += height;
  }
  return OK;
}
//------------------------------------------------------------------------------
int LCD_draw_rect(lcdPoint start, uint32_t width, uint32_t height, uint8_t borderWidth)
{
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED;
  if((start.x + width) > LCD_WIDTH)
    return WIDTH_OUT_OF_BOUNDS;
  if(start.y + height > LCD_HEIGHT)
    return HEIGHT_OUT_OF_BOUNDS;
  uint8_t startPage = start.y / LCD_PAGE_HEIGHT;
  uint8_t finishPage = (start.y + height) / LCD_PAGE_HEIGHT;
  if((start.y + height) % LCD_PAGE_HEIGHT == 0)
    finishPage--;
  uint8_t startLine = start.x;
  uint8_t yStartOffset = start.y - startPage * LCD_PAGE_HEIGHT;
  uint8_t yFinishOffset = LCD_PAGE_HEIGHT - (start.y + height - finishPage * LCD_PAGE_HEIGHT);
  uint8_t lbMask;
  uint8_t hbMask;
  for(int j = startLine; j < (startLine + width); j++)
  {
    int32_t topBorder = borderWidth;
    int32_t bottomBorder = borderWidth - height;
    for(int i = startPage; i <= finishPage; i++)
    {
      lbMask = (i == startPage)?yStartOffset:0;
      hbMask = (i == finishPage)?yFinishOffset:0;
      uint8_t mask = (0xff << lbMask) & (0xff >> hbMask);
      uint8_t pixelsNeeded = LCD_PAGE_HEIGHT - lbMask - hbMask;
      uint8_t byte = 0;
      uint8_t rbyte = lcdRamMirror[i * LCD_WIDTH + j];
      if(j < (startLine + borderWidth))
      {
        rbyte |= (0xff & mask);
      }
      else if(j > (startLine + width - borderWidth - 1))
      {
        rbyte |= (0xff & mask);
      }
      else
      {
        while(pixelsNeeded)
        {
          if(topBorder-- > 0)
          {
            rbyte |= (1 << (LCD_PAGE_HEIGHT - pixelsNeeded));
          }
          else
          {
            rbyte &=~(1 << (LCD_PAGE_HEIGHT - pixelsNeeded));
          }
          if(++bottomBorder > 0)
          {
            rbyte |= (0x80 >> (hbMask - pixelsNeeded + 1));
          }
          /*else
          {
            byte &=~(0x80 >> (pixelsNeeded - 1));
          }*/
          pixelsNeeded--;
        }
      }
      byte &= ~mask;
      byte |= rbyte;
      lcdRamMirror[i * LCD_WIDTH + j] = byte;
    }
  }
  return OK;
}
//------------------------------------------------------------------------------
int fill_area_solid(lcdPoint start, lcdPoint finish)
{
  uint32_t width = finish.x - start.x + 1;
  uint32_t height = finish.y - start.y + 1;
  if(lcdRamMirror == NULL)
    return BUFFER_NOT_INITIALISED;
  if((start.x + width) > LCD_WIDTH)
    return WIDTH_OUT_OF_BOUNDS;
  if(start.y + height > LCD_HEIGHT)
    return HEIGHT_OUT_OF_BOUNDS;
  uint8_t startPage = start.y / LCD_PAGE_HEIGHT;
  uint8_t finishPage = (start.y + height) / LCD_PAGE_HEIGHT;
  if((start.y + height) % LCD_PAGE_HEIGHT == 0)
    finishPage--;
  uint8_t startLine = start.x;
  uint8_t yStartOffset = start.y - startPage * LCD_PAGE_HEIGHT;
  uint8_t yFinishOffset = LCD_PAGE_HEIGHT - (start.y + height - finishPage * LCD_PAGE_HEIGHT);
  uint8_t lbMask;
  uint8_t hbMask;
  for(int j = startLine; j < (startLine + width); j++)
  {
    for(int i = startPage; i <= finishPage; i++)
    {
      lbMask = (i == startPage)?yStartOffset:0;
      hbMask = (i == finishPage)?yFinishOffset:0;
      uint8_t mask = (0xff << lbMask) & (0xff >> hbMask);
      uint8_t rbyte = lcdRamMirror[i * LCD_WIDTH + j];
      rbyte = (rbyte & ~mask) | (0xff & mask);
      lcdRamMirror[i * LCD_WIDTH + j] = rbyte;
    }
  }
  return OK;
}
//------------------------------------------------------------------------------
