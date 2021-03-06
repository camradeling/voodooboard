#include "includes.h"
//------------------------------------------------------------------------------
extern void TimingDelay_Decrement(void);
//------------------------------------------------------------------------------
extern int main( void );
void* _sidata;
void* _sdata;
void* _edata;
void* _sbss;
void* _ebss;
void Reset_Handler(void)
{
  unsigned long *pulSrc, *pulDest;

  //
  // Copy the data segment initializers from flash to SRAM.
  //
  pulSrc = &_sidata;
  for(pulDest = &_sdata; pulDest < &_edata; )
  {
    *(pulDest++) = *(pulSrc++);
  }

  //
  // Zero fill the bss segment.
  //
  for(pulDest = &_sbss; pulDest < &_ebss; )
  {
    *(pulDest++) = 0;
  }

  //
  // Call the application's entry point.
  //
  main();
}
//------------------------------------------------------------------------------
void NMIException(void)
{
}
//------------------------------------------------------------------------------
void HardFaultException(void)
{
}
//------------------------------------------------------------------------------
void MemManageException(void)
{
}
//------------------------------------------------------------------------------
void BusFaultException(void)
{
}
//------------------------------------------------------------------------------
void UsageFaultException(void)
{
}
//------------------------------------------------------------------------------
void DebugMonitor(void)
{
}
//------------------------------------------------------------------------------
void SVCHandler(void)
{
}
//------------------------------------------------------------------------------
void PendSVC(void)
{
}
//------------------------------------------------------------------------------
void SysTickHandler(void)
{
  /* Decrement the TimingDelay variable */
  //TimingDelay_Decrement();
}
//------------------------------------------------------------------------------
void WWDG_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void PVD_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void TAMPER_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void RTC_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void FLASH_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void RCC_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{

}
//------------------------------------------------------------------------------
void EXTI1_IRQHandler(void)
{

}
//------------------------------------------------------------------------------
void EXTI2_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void EXTI3_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void EXTI4_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void DMAChannel1_IRQHandler(void)
{  
}
//------------------------------------------------------------------------------
void DMAChannel2_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void DMAChannel3_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
/*void DMAChannel4_IRQHandler(void)
{
}*/
//------------------------------------------------------------------------------
/*void DMAChannel5_IRQHandler(void)
{
}*/
//------------------------------------------------------------------------------
//extern uint8_t i2cDMAflag;
void DMAChannel6_IRQHandler(void)
{
  /*if(DMA1->ISR & DMA_ISR_TCIF6)
  {
    i2cDMAflag = 0;
    DMA_Channel_TypeDef* Chan = (DMA_Channel_TypeDef*)DMA1_Channel6_BASE;
    Chan->CCR &=~ (DMA_CCR6_EN| DMA_CCR6_TCIE);
    DMA1->IFCR |= DMA_IFCR_CTCIF6 | DMA_IFCR_CTEIF6 | DMA_IFCR_CHTIF6;
  }
  else if(DMA1->ISR & DMA_ISR_TEIF6)
  {
    DMA1->IFCR |= DMA_IFCR_CTEIF6;
  }
  else if(DMA1->ISR & DMA_ISR_HTIF6)
  {
    DMA1->IFCR |= DMA_IFCR_CHTIF6;
  }*/
}
//------------------------------------------------------------------------------
void DMAChannel7_IRQHandler(void)
{
  /*if(DMA1->ISR & DMA_ISR_TCIF7)
  {
    i2cDMAflag = 0;
    DMA_Channel_TypeDef* Chan = (DMA_Channel_TypeDef*)DMA1_Channel7_BASE;
    Chan->CCR &=~ (DMA_CCR7_EN | DMA_CCR7_TCIE);
    DMA1->IFCR |= DMA_IFCR_CTCIF7 | DMA_IFCR_CTEIF7 | DMA_IFCR_CHTIF7;
  }
  else if(DMA1->ISR & DMA_ISR_TEIF7)
  {
    DMA1->IFCR |= DMA_IFCR_CTEIF7;
  }
  else if(DMA1->ISR & DMA_ISR_HTIF7)
  {
    DMA1->IFCR |= DMA_IFCR_CHTIF7;
  }*/
}
//------------------------------------------------------------------------------
void ADC_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void USB_HP_CAN_TX_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void USB_LP_CAN_RX0_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void CAN_RX1_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void CAN_SCE_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void EXTI9_5_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void TIM1_BRK_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
/*void TIM1_UP_IRQHandler(void)
{
}*/
//------------------------------------------------------------------------------
void TIM1_TRG_COM_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
/*void TIM1_CC_IRQHandler(void)
{
}*/
//------------------------------------------------------------------------------
void TIM2_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
//------------------------------------------------------------------------------
uint32_t timerOVF = 0;
//------------------------------------------------------------------------------
void TIM3_IRQHandler(void)
{
  timerOVF++;
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
//------------------------------------------------------------------------------
void TIM4_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
/*void I2C1_EV_IRQHandler(void)
{
}*/
//------------------------------------------------------------------------------
void I2C1_ER_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void I2C2_EV_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void I2C2_ER_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void SPI1_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void SPI2_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
/*void USART1_IRQHandler(void)
{
}*/
//------------------------------------------------------------------------------
void USART2_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void USART3_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void EXTI15_10_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void RTCAlarm_IRQHandler(void)
{
}
//------------------------------------------------------------------------------
void USBWakeUp_IRQHandler(void)
{
}
//------------------------------------------------------------------------------

