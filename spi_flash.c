//------------------------------------------------------------------------------
#include "includes.h"
//------------------------------------------------------------------------------
void vSpiFlashTask (void *pvParameters)
{
  uint16_t num = 0;
  //erase_flash(0x0001FC00);
  //write_flash(0x0001FC00, 0xaabb);
  for(;;)
  {
    num = *(uint16_t*)0x0001FC00;
    vTaskDelay(1000 / portTICK_RATE_MS);
  }
}
//------------------------------------------------------------------------------
void w25_write_enable(void)
{
  uint8_t sr = 0x00;
  uint8_t dummy = 0x00;
  SET_PIN_LOW(GPIOA,4);
  SPI1->DR = W25_WRITE_ENABLE;
  while(!(SPI1->SR & SPI_SR_TXE));
  SET_PIN_HIGH(GPIOA,4);
  do
  {
    SET_PIN_LOW(GPIOA,4);
    SPI1->DR = W25_READ_STATUS1;
    while(!(SPI1->SR & SPI_SR_TXE));
    dummy = SPI1->DR;
    SPI1->DR = dummy;
    while(!(SPI1->SR & SPI_SR_RXNE));
    sr = SPI1->DR;
    SET_PIN_HIGH(GPIOA,4);
  }
  while(sr & W25_SR1_BUSY);
}
//------------------------------------------------------------------------------
void w25_sector_erase(uint32_t addr)
{
  uint8_t sr = 0x00;
  uint8_t dummy = 0x00;
  w25_write_enable();
  SET_PIN_LOW(GPIOA,4);
  SPI1->DR = W25_SECTOR_ERASE;
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 16);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 8);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 0);
  while(!(SPI1->SR & SPI_SR_TXE));
  SET_PIN_HIGH(GPIOA,4);
  do
  {
    SET_PIN_LOW(GPIOA,4);
    SPI1->DR = W25_READ_STATUS1;
    while(!(SPI1->SR & SPI_SR_TXE));
    dummy = SPI1->DR;
    SPI1->DR = dummy;
    while(!(SPI1->SR & SPI_SR_RXNE));
    sr = SPI1->DR;
    SET_PIN_HIGH(GPIOA,4);
  }
  while(sr & W25_SR1_BUSY);
}
//------------------------------------------------------------------------------
void w25_block64_erase(uint32_t addr)
{
  uint8_t sr = 0x00;
  uint8_t dummy = 0x00;
  w25_write_enable();
  SET_PIN_LOW(GPIOA,4);
  SPI1->DR = W25_BLOCK_ERASE_64;
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 16);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 8);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 0);
  while(!(SPI1->SR & SPI_SR_TXE));
  SET_PIN_HIGH(GPIOA,4);
  do
  {
    SET_PIN_LOW(GPIOA,4);
    SPI1->DR = W25_READ_STATUS1;
    while(!(SPI1->SR & SPI_SR_TXE));
    dummy = SPI1->DR;
    SPI1->DR = dummy;
    while(!(SPI1->SR & SPI_SR_RXNE));
    sr = SPI1->DR;
    SET_PIN_HIGH(GPIOA,4);
  }
  while(sr & W25_SR1_BUSY);
}
//------------------------------------------------------------------------------
void w25_page_read(uint32_t addr, uint8_t* buf)
{
  uint8_t mf = 0x00;
  uint8_t dummy = 0x00;
  SET_PIN_LOW(GPIOA,4);
  SPI1->DR = W25_READ_DATA;
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 16);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 8);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = 0x00;
  while(!(SPI1->SR & SPI_SR_TXE)); 
  mf = SPI1->DR;
  for(int i = 0; i < FLASH_PAGE_LEN; i++)
  {
    SPI1->DR = dummy;
    while(!(SPI1->SR & SPI_SR_RXNE));
    buf[i] = SPI1->DR;
  }
  SET_PIN_HIGH(GPIOA,4);
}
//------------------------------------------------------------------------------
void w25_page_write(uint32_t addr, uint8_t* buf)
{
  uint8_t sr = 0x00;
  uint8_t dummy = 0x00;
  w25_write_enable();
  SET_PIN_LOW(GPIOA,4);
  SPI1->DR = W25_PAGE_PROGRAM;
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 16);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = (uint8_t)(addr >> 8);
  while(!(SPI1->SR & SPI_SR_TXE));
  SPI1->DR = 0x00;
  while(!(SPI1->SR & SPI_SR_TXE));
  for(int i = 0; i < FLASH_PAGE_LEN; i++)
  {
    SPI1->DR = buf[i];
    while(!(SPI1->SR & SPI_SR_TXE));
  }
  SET_PIN_HIGH(GPIOA,4);
  do
  {
    SET_PIN_LOW(GPIOA,4);
    SPI1->DR = W25_READ_STATUS1;
    while(!(SPI1->SR & SPI_SR_TXE));
    dummy = SPI1->DR;
    SPI1->DR = dummy;
    while(!(SPI1->SR & SPI_SR_RXNE));
    sr = SPI1->DR;
    SET_PIN_HIGH(GPIOA,4);
  }
  while(sr & W25_SR1_BUSY);
}
//------------------------------------------------------------------------------
void w25_init(void)
{
  uint8_t rewr = 0;
  w25_page_read(W25_PARAMS_START, flashBuf);
  for(int i = 0; i < FLASH_BACKUP_PARAMS_LEN; i++)
  {
    if(i >= FLASH_PAGE_LEN/2)
      break;
    MODBUS_HR[FLASH_BACKUP_FIRST_ADDR + i] = flashBuf[i*2] | ((uint16_t)flashBuf[i*2 + 1] << 8);
  }
  for(int i = 0; i < FLASH_BACKUP_PARAMS_LEN; i++)
  {
    if(MODBUS_HR[i + FLASH_BACKUP_FIRST_ADDR] == 0xffff)//first time read
    {
      rewr = 1;
      break;
    }
  }
  if(rewr)//write defaults
  {
    w25_sector_erase(W25_PARAMS_START);
    for(int i = 0; i < FLASH_BACKUP_PARAMS_LEN; i++)
    {
      MODBUS_HR[i + FLASH_BACKUP_FIRST_ADDR] = defaultParams[i];
      flashBuf[i*2] = defaultParams[i] & 0xff;
      flashBuf[i*2 + 1] = (defaultParams[i] >> 8) & 0xff;
    }
    w25_page_write(W25_PARAMS_START, flashBuf);
  }
}
//------------------------------------------------------------------------------
void w25_params_write(void)
{
  w25_sector_erase(W25_PARAMS_START);
  for(int i = 0; i < FLASH_BACKUP_PARAMS_LEN; i++)
  {
    flashBuf[i*2] = MODBUS_HR[i + FLASH_BACKUP_FIRST_ADDR] & 0xff;
    flashBuf[i*2 + 1] = (MODBUS_HR[i + FLASH_BACKUP_FIRST_ADDR] >> 8) & 0xff;
  }
  w25_page_write(W25_PARAMS_START, flashBuf);
}
//------------------------------------------------------------------------------
//=== Запись полуслова во Flash ===//
void write_flash(uint32_t addr, uint16_t data)
{
  while(FLASH->SR & FLASH_SR_BSY);		// Дождаться конца незаконченной операции. Разблокировка проводилась при ините.
  // Программирование полуслова.
  FLASH->CR |= FLASH_CR_PG;		// Старт программирования.
  *(u16 *)addr=data;		// Запись данного data по адресу addr.
  while(FLASH->SR & FLASH_SR_BSY);		// Ожидание конца программирования.
  while((FLASH->SR & FLASH_SR_EOP)==0);		// Ожидание конца операции.
  FLASH->CR &= ~FLASH_CR_PG;		// Конец программирования.
  FLASH->SR |= FLASH_SR_EOP;		// Закончить операцию.
}
//------------------------------------------------------------------------------
//=== Стирание страницы Flash ===//
void erase_flash(uint32_t addr)
{		// addr - начальный адрес страницы.
  while(FLASH->SR & FLASH_SR_BSY);		// Дождаться конца незаконченной операции. Разблокировка проводилась при ините.
  FLASH->CR |= FLASH_CR_PER;		// Разрешение стирания страницы 2 кБайта.
  FLASH->AR = addr & 0xfffffc00;		// Занести адрес стираемой страницы.
  FLASH->CR |= FLASH_CR_STRT;		// Старт стирания.
  int a = 2;		// Обязательная задержка.
  while(FLASH->SR & FLASH_SR_BSY);		// Ожидание конца стирания.
  while((FLASH->SR & FLASH_SR_EOP)==0);		// Ожидание конца операции.
  FLASH->CR &= ~ FLASH_CR_PER;		// Вернуть взад.
  FLASH->SR |= FLASH_SR_EOP;		// Закончить операцию.
}
//------------------------------------------------------------------------------
void reflash(void)
{
  uint32_t addr = FLASH_FIRMWARE_START;
  for(int j = 0; j < FLASH_FIRMWARE_LEN; j+=FLASH_PAGE_LEN)
  {
    w25_page_read(addr + j, flashBuf);
    if((j % 0x400) == 0)
      erase_flash(addr + j);
    for(int i = 0; i < FLASH_PAGE_LEN/2; i++)//пишем 256 байт
      write_flash(addr+i*2, *(uint16_t*)&flashBuf[i*2]);
  }
  REBOOT();
}