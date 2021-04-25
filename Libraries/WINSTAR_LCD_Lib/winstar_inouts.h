#ifndef INOUTS_H
#define INOUTS_H
//------------------------------------------------------------------------------
/*EN_PORT*/
#define LCD_EN_PORT GPIOB
#define EN_SIG 1
#define LCD_BL 7
#define HIGHZ_5V 12
//------------------------------------------------------------------------------
/*Заголовочный файл для назначения портов и пинов*/
/*на каком порту управление сегментами индикаторов*/
#define LCD_SEGMENTS_PORT GPIOC
/*отступ в порту (необязательно нумерация начинается с нулевого пина)*/
#define LCD_SEGMENTS_PORT_OFFSET 0
#define LCD_CONTROL_PORT GPIOC
#define CS1 1
#define CS2 2
//------------------------------------------------------------------------------
#define DI_SIG 3 
#define CS1_SIG 1 
#define CS2_SIG 2 
#define LCD_RESET 0 
//------------------------------------------------------------------------------
#define CL1_LCD 8 
#define CL1_KEYS 9 
//------------------------------------------------------------------------------
#define BUTTONS_PORT GPIOC
#define BUTTON0_SIG 4 
#define BUTTON1_SIG 5
#define BUTTON2_SIG 6
#define BUTTON3_SIG 7
#define BUTTON_BLOCK_PIN0 0
#define BUTTON_BLOCK_PIN1 1
#define BUTTON_BLOCK_PIN2 2
#define BUTTON_BLOCK_PIN3 3
#define BUTTON_BLOCK_PIN4 4
#define BUTTON_BLOCK_PIN5 5
//------------------------------------------------------------------------------
#endif//INOUTS_H
