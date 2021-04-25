#ifndef BUTTONS_H
#define BUTTONS_H
//------------------------------------------------------------------------------
typedef struct
{
  uint8_t event;
  uint8_t keyCode;
}buttonEvent;
//------------------------------------------------------------------------------
#include "display.h"
//------------------------------------------------------------------------------
#define BUTTON_PRESSED_CODE        1
#define BUTTON_RELEASED_CODE       2
#define BUTTON_MULTIPRESS_CODE     3
#define CALIBRATION_FINISHED       4
//------------------------------------------------------------------------------
#ifdef DOZATOR2
//------------------------------------------------------------------------------
#define NUMBER_OF_BUTTON_BLOCKS 3
#define BUTTONS_IN_BLOCK 8
#define BUTTON_NUMBER_OFFSET 8
#define BUTTON_EVENT_QUEUE_LENGTH 5
//------------------------------------------------------------------------------
#define NONE                0
#define COUNTER             1
#define SUM                 2
#define NETTO               3
#define BRUTTO              4
#define DOSE4               5
#define DOSE3               6
#define DOSE2               7
#define DOSE1               8
#define SEVEN               9
#define FOUR                10
#define ONE                 11
#define ZERO                12
#define EIGHT               13
#define FIVE                14
#define TWO                 15
#define COMMAR              16
#define NINE                17
#define SIX                 18
#define THREE               19
#define ENTER               20
#define F1                  21
#define OKTOTORP            22
#define BACKSPACE           23
#define HANDMODE_SYM        24
//------------------------------------------------------------------------------
#else
//------------------------------------------------------------------------------
#define NUMBER_OF_BUTTON_BLOCKS 6
#define BUTTONS_IN_BLOCK 4
#define BUTTON_NUMBER_OFFSET 4
#define BUTTON_EVENT_QUEUE_LENGTH 5
//------------------------------------------------------------------------------
#define NONE                0
#define CALIBRATION         1
#define F1                  2
#define INDICATION          3
#define F2                  4
#define UP_ARROW            5
#define LEFT_ARROW          6
#define DOWN_ARROW          7
#define RIGHT_ARROW         8
#define SEVEN               9
#define EIGHT               10
#define NINE                11
#define PARAMETERS          12
#define FOUR                13
#define FIVE                14
#define SIX                 15
#define OKTOTORP            16
#define ONE                 17
#define TWO                 18
#define THREE               19
#define BACKSPACE           20
#define ZERO                21
#define COMMAR              22
#define ENTER               23
#define CROSS               24
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
void read_buttons(void);
//------------------------------------------------------------------------------
void get_key_code(void);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif/*BUTTONS_H*/