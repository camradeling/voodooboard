#include "includes.h"
//------------------------------------------------------------------------------
void recover_I2C1(void)
{
  uint32_t dummy;
  GPIOB->CRL &= 0x00ffffff;//reset state
  GPIOB->CRL |= 0x77000000;//output 50 mHz open-drain
  GPIOB->ODR |= (1 << 6)|(1 << 7);
  uint16_t reg = GPIOB->IDR;
  for(int j = 0; j < I2C_DELAY; j++)
  {
    reg = GPIOB->IDR;
    if(reg & (1 << 6))
      break;
  }
  for(int i = 0; i < 9; i++)
  {
    reg = GPIOB->IDR;
    if(reg & (1 << 7))
      break;
    GPIOB->ODR &=~ (1 << 6);
    for(int j = 0; j < I2C_DELAY; j++)
    {
      reg = GPIOB->IDR;
      if(!(reg & (1 << 6)))
        break;
    }
    GPIOB->ODR |= (1 << 6);
    reg = GPIOB->IDR;
    for(int j = 0; j < I2C_DELAY; j++)
    {
      reg = GPIOB->IDR;
      if(reg & (1 << 6))
        break;
    }
  }//getting rid of busy line
  init_I2C1();
}
//------------------------------------------------------------------------------
void init_I2C1(void)
{
  GPIOB->CRL &= 0x44ffffff;//reset state
  GPIOB->CRL |= 0xff000000;//alternative function 50mHz open-drain
  AFIO->MAPR &=~0x00000002;//ensure mapping i2c1 to PB6-PB7
  //now i2c
  I2C1->CR1 = 0x00000000;//reset
  I2C1->CR2 = 0x00000024;//reset, 36mHz PCLK1
  I2C1->CCR = 90;//36mHz, Sm mode, 200kHz bus
  I2C1->TRISE = 0x00000025;
  //interrupt
  I2C1->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN;
  I2C1->CR1 |= I2C_CR1_PE;
}
//------------------------------------------------------------------------------
void I2C1_EV_IRQHandler(void)
{
  if(I2C1->SR1 & I2C_SR1_SB)
  {
    if(I2C1State == I2C_INITIATING_CONVERSION || I2C1State == I2C_WRITING_POLLING_ADDR || I2C1State == I2C_WRITING_CONVERSION_ADDR)
      I2C1->DR = (i2cAddr & ~0x01);//slave address rw-bit = 0
    else
      I2C1->DR = (i2cAddr | 0x01);//slave address rw-bit = 1
    I2C1TransferStatus = I2C_ADDR_GONE;
  }
  else if(I2C1->SR1 & I2C_SR1_ADDR)
  {
    if(I2C1State == I2C_INITIATING_CONVERSION)
    {
      uint32_t dummy = I2C1->SR2;
      I2C1->DR = ADS_CONFIG_REG & 0xff;//address MSB
      I2C1TransferStatus = I2C_REGADDR_MSB_GONE;
    }
    else if(I2C1State == I2C_WRITING_POLLING_ADDR)
    {
      uint32_t dummy = I2C1->SR2;
      I2C1->DR = ADS_CONFIG_REG & 0xff;
      I2C1TransferStatus = I2C_REGADDR_MSB_GONE;
    }
    else if(I2C1State == I2C_POLLING)
    {
      uint32_t dummy = I2C1->SR2;
      I2C1->CR1 |= I2C_CR1_ACK;
      I2C1TransferStatus = I2C_READING_LSB;
    }
    else if(I2C1State == I2C_WRITING_CONVERSION_ADDR)
    {
      uint32_t dummy = I2C1->SR2;
      I2C1->DR = ADS_CONVERSION_REG  & 0xff;
      I2C1TransferStatus = I2C_REGADDR_MSB_GONE;
    }
    else if(I2C1State == I2C_READING_DATA)
    {
      uint32_t dummy = I2C1->SR2;
      I2C1->CR1 |= I2C_CR1_ACK;
      I2C1TransferStatus = I2C_READING_LSB;
    }
  }
  else if(I2C1->SR1 & I2C_SR1_TXE)
  {
    if(I2C1TransferStatus == I2C_REGADDR_MSB_GONE)
    {
      if(I2C1State == I2C_INITIATING_CONVERSION)
      {
        I2C1->DR = ADS1115_DIFSIG_Config_Buf[0];
        I2C1TransferStatus = I2C_CONFIG1_GONE;
      }
      else if(I2C1State == I2C_WRITING_POLLING_ADDR)
      {
        I2C1State = I2C_POLLING;
        I2C1->CR1 |= I2C_CR1_START;
      }
      else if(I2C1State == I2C_WRITING_CONVERSION_ADDR)
      {
        I2C1State = I2C_READING_DATA;
        I2C1->CR1 |= I2C_CR1_START;
      }
    }
    else if(I2C1TransferStatus == I2C_CONFIG1_GONE)
    {
      I2C1->DR = ADS1115_DIFSIG_Config_Buf[1];
      I2C1TransferStatus = I2C_CONFIG2_GONE;
    }
    else if(I2C1TransferStatus == I2C_CONFIG2_GONE)
    {
      uint32_t reg = I2C1->SR1;
      I2C1State = I2C_WRITING_POLLING_ADDR;
      I2C1->CR1 |= I2C_CR1_START;
    }
  }
  else if(I2C1->SR1 & I2C_SR1_RXNE)
  {
    if(I2C1State == I2C_POLLING)
    {
      if(I2C1TransferStatus == I2C_READING_LSB)
      {
        ADS_READ_Buf[0] = I2C1->DR;
        I2C1TransferStatus = I2C_READING_MSB;
        I2C1->CR1 &=~ I2C_CR1_ACK;
      }
      else if(I2C1TransferStatus == I2C_READING_MSB)
      {
        ADS_READ_Buf[1] = I2C1->DR;
        if(ADS_READ_Buf[0] & 0x80)
        {
          I2C1State = I2C_WRITING_CONVERSION_ADDR;
        }
        else
        {
          I2C1State = I2C_WRITING_POLLING_ADDR;
        }
        I2C1->CR1 |= I2C_CR1_START;
      }
    }
    else if(I2C1State == I2C_READING_DATA)
    {
      if(I2C1TransferStatus == I2C_READING_LSB)
      {
        ADS_READ_Buf[0] = I2C1->DR;
        I2C1TransferStatus = I2C_READING_MSB;
        I2C1->CR1 &=~ I2C_CR1_ACK;
      }
      else if(I2C1TransferStatus == I2C_READING_MSB)
      {
        ADS_READ_Buf[1] = I2C1->DR;
        MODBUS_HR[MBHR_ADS1115_RAW_DIFVAL1] = ADS_READ_Buf[1] | (ADS_READ_Buf[0] << 8);
        I2C1State = I2C_INITIATING_CONVERSION;
        I2C1->CR1 |= I2C_CR1_START;
      }
    }
  }
}
//------------------------------------------------------------------------------
