#define EXTERNS_H/*to prevent linker ambiguity*/
//------------------------------------------------------------------------------
#include "includes.h"
//------------------------------------------------------------------------------
SemaphoreHandle_t Com1RxSemaphore;
//SemaphoreHandle_t ComTxSemaphore;
//------------------------------------------------------------------------------
uint8_t com1TxBuffer[TXRX_BUFFER_SIZE];
uint8_t com1RxBuffer[TXRX_BUFFER_SIZE];
uint8_t transmitActive;
//------------------------------------------------------------------------------
ComMessage Com1RxQueue[MAX_COM_QUEUE_LENGTH];
ComMessage Com1TxQueue[MAX_COM_QUEUE_LENGTH];
uint8_t Com1RxReadInd;
uint8_t Com1RxWriteInd;
uint8_t Com1TxReadInd;
uint8_t Com1TxWriteInd;
//------------------------------------------------------------------------------
//i2c issues
uint8_t I2C1State;
uint8_t I2C1TransferStatus;
uint8_t i2cAddr;
uint8_t conversions;
uint8_t ADS1115_DIFSIG_Config_Buf[] = {0x8f,0xa3};//comparator off, datarate 250, single-shot mode, differential AIN0 -> AIN1, start conversion
uint8_t ADS1115_REF_Config_Buf[] = {0xf5,0xa3};//comparator off, datarate 250, single-shot mode, AIN2 -> GND, start conversion
uint8_t ADS_READ_Buf[2];
//------------------------------------------------------------------------------
uint16_t flashParams[FLASH_BACKUP_PARAMS_LEN];
const uint16_t defaultParams[FLASH_BACKUP_PARAMS_LEN] = 
{
  3,
  416,
  0xaabb
};
uint8_t flashBuf[FLASH_PAGE_LEN];
//------------------------------------------------------------------------------
