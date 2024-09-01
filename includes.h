#ifndef INCLUDES_H
#define INCLUDES_H
//------------------------------------------------------------------------------
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//------------------------------------------------------------------------------
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//------------------------------------------------------------------------------
/* Library includes. */
#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "stm32f10x.h"
//------------------------------------------------------------------------------
/* app includes. */
#include "app_config.h"
#include "adc.h"
#include "i2c.h"
#include "serial.h"
#include "modbus.h"
#include "externs.h"
#include "spi_flash.h"
//------------------------------------------------------------------------------
#define FLASH_BACKUP_PARAMS_LEN 4
#define FLASH_BACKUP_FIRST_ADDR 0
//------------------------------------------------------------------------------
#endif/*INCLUDES_H*/