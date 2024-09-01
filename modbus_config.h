#ifndef MODBUS_CONFIG_H
#define MODBUS_CONFIG_H
//------------------------------------------------------------------------------------------------------------------------------
#include <stdint.h>
//------------------------------------------------------------------------------------------------------------------------------
//modbus registers configuration
enum Modbus_Register_e
{
       					MBHR_DISCRETE_INPUTS_LOW = 0,
		              MBHR_DISCRETE_OUTPUTS_LOW = 1,
		             REGISTER3 = 2,
		             REGISTER4 = 3,
		              REGISTER5 = 4,
	                  REGISTER6 = 5,
			       REGISTER7 = 6,
			        REGISTER8 = 7,
			          REGISTER9 = 8,
			           MBHR_ADS1115_RAW_DIFVAL1 = 9,
			          REGISTER11 = 10,
	          MBHR_SPACE_LAST_ADDR = REGISTER11
	
};
//------------------------------------------------------------------------------------------------------------------------------
#define MBHR_SETTINGS_SIZE                 (MBHR_SETTINGS_LAST_ADDR+1)
#define MBHR_SPACE_SIZE                    (MBHR_SPACE_LAST_ADDR+1)
//------------------------------------------------------------------------------------------------------------------------------
#define MAX_FIRMWARE_BLOCK_SIZE     (128*2)
#define TXRX_BUFFER_SIZE (256+6)
//------------------------------------------------------------------------------------------------------------------------------
#define BAUDRATE_INDEX_2400    0x00
#define BAUDRATE_INDEX_4800    0x01
#define BAUDRATE_INDEX_9600    0x02
#define BAUDRATE_INDEX_14400   0x03
#define BAUDRATE_INDEX_19200   0x04
#define BAUDRATE_INDEX_38400   0x05
#define BAUDRATE_INDEX_56000   0x06
#define BAUDRATE_INDEX_57600   0x07
#define BAUDRATE_INDEX_115200  0x08
//------------------------------------------------------------------------------------------------------------------------------
int check_register_readonly(uint16_t regnum);
//------------------------------------------------------------------------------------------------------------------------------
#endif/*MODBUS_CONFIG_H*/