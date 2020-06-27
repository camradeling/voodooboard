#include "includes.h"
//------------------------------------------------------------------------------
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_TC) == SET)
  {
    USART_ClearITPendingBit(USART1, USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
    DMA_USART_prepare_recieve();
    transmitActive = 0;
  }
}
//------------------------------------------------------------------------------
void TIM1_CC_IRQHandler(void)
{
  //�������� ������
  TIM1->CR1 |= TIM_CR1_CEN;
  //���� ����� ��� ��������� ���������
  TIM1->EGR |= TIM_EventSource_Update;
  //�������� ���������� update
  TIM1->DIER |= TIM_IT_Update;
  //������� ���� ���������� update  � CC
  TIM1->SR = ~(TIM_IT_CC3 | TIM_IT_Update);
}
//------------------------------------------------------------------------------
void TIM1_UP_IRQHandler(void)//���������� �� ������� ������� - 
{//������ ������ ��������� ���� ������
  //��������� ������
  TIM1->CR1 &= ~TIM_CR1_CEN;
  //��������� ���������� update
  TIM1->DIER &= ~TIM_IT_Update;
  //������� ���� ���������� update
  TIM1->SR = ~TIM_IT_Update;
  //������� ����� � �����
  Com1RxWriteInd++;
  if(Com1RxWriteInd >= MAX_COM_QUEUE_LENGTH)
    Com1RxWriteInd = 0;
  ComMessage* cMes = &Com1RxQueue[Com1RxWriteInd];
  cMes->length = TXRX_BUFFER_SIZE - DMA1_Channel5->CNDTR;
  for(int i = 0; i < cMes->length; i++)
    cMes->data[i] = com1RxBuffer[i];
  BaseType_t typt;
  xSemaphoreGiveFromISR(Com1RxSemaphore, &typt);
}
//------------------------------------------------------------------------------
void DMAChannel4_IRQHandler(void)
{
  if(DMA_GetITStatus( DMA1_IT_TC4 ) == SET)
  {
    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA_ClearITPendingBit(DMA1_IT_GL4);
    USART_ClearITPendingBit(USART1, USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);
  }
}
//------------------------------------------------------------------------------
void DMAChannel5_IRQHandler(void)
{//TODO �������� ��������� �������, ��� ������� ������������ ���-�� ����
  //� ���������� ��������� ���
  if(DMA_GetITStatus( DMA1_IT_TC5 ) == SET)
  {
    DMA_ClearITPendingBit(DMA1_IT_GL5);
  }
}
//------------------------------------------------------------------------------
void DMA_USART_prepare_transmit(uint8_t length)
{
  DMA_DeInit(DMA1_Channel4);
  DMA_InitTypeDef dma;
  DMA_StructInit(&dma);
  dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
  dma.DMA_MemoryBaseAddr = (uint32_t)&com1TxBuffer;
  dma.DMA_BufferSize = length;
  dma.DMA_DIR = DMA_DIR_PeripheralDST;
  dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_Init(DMA1_Channel4, &dma);
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
  DMA_Cmd(DMA1_Channel4, ENABLE);
}
//------------------------------------------------------------------------------
void DMA_USART_prepare_recieve(void)
{
  DMA_DeInit(DMA1_Channel5);
  DMA_InitTypeDef dma;
  DMA_StructInit(&dma);
  dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
  dma.DMA_MemoryBaseAddr = (uint32_t)&com1RxBuffer;
  dma.DMA_BufferSize = TXRX_BUFFER_SIZE;
  dma.DMA_DIR = DMA_DIR_PeripheralSRC;
  dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_Init(DMA1_Channel5, &dma);
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
  DMA_Cmd(DMA1_Channel5, ENABLE);
}
//------------------------------------------------------------------------------
void init_com_timer()
{
  //��������� ����������� preload-���������, sampling rate = CK_INT, edge-align mode
  //upcounting ����������� �����, one-pulse mode �� ��������
  //update event �������
  TIM1->CR1 &= ~(TIM_CR1_ARPE | TIM_CR1_CKD | TIM_CR1_CMS | TIM_CR1_DIR | TIM_CR1_OPM | TIM_CR1_UDIS);
  //������ overflow �������� update interrupt
  TIM1->CR1 |= TIM_CR1_URS;
  //������ CH3 �� TI1
  TIM1->CR2 |= TIM_CR2_TI1S;
  //������������ �������� �� rising ������, ������������ �� �������� ���������, ������ �������� ��������
  //master-slave mode �� �����, ���������, ������ ����� �� trigger source
  TIM1->SMCR &= ~(TIM_SMCR_ETP | TIM_SMCR_ECE | TIM_SMCR_ETF | TIM_SMCR_MSM | TIM_SMCR_TS);
  //� ������ �������� trigger source TI1F_ED, ���� �� ���� ��������� ��� ��� ���
  TIM1->SMCR |= TIM_SMCR_TS_2;
  //������ ����� �� slave mode �����
  TIM1->SMCR &= ~TIM_SMCR_SMS;
  //� ������ �������� ����� slave mode reset
  TIM1->SMCR |= TIM_SMCR_SMS_2;
  //������ cc1, cc2 � cc4 ��� �� �����, ������ �� ��� ������
  TIM1->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
  TIM1->CCMR2 &= ~(TIM_CCMR2_CC4S | TIM_CCMR2_CC3S);
  //����� cc3 ������ ��� ����, trigger source TI1
  TIM1->CCMR2 |= TIM_CCMR2_CC3S_0;
  //���������� �� �����, ���������, ������ �� �����, ���������
  TIM1->CCMR2 &= ~(TIM_CCMR2_IC3PSC | TIM_CCMR2_IC3F);
  //������� ������
  TIM1->CCER &= 0x0000;
  //�������� ����� cc3
  TIM1->CCER |= TIM_CCER_CC3E;
  //������� � ����
  TIM1->CNT = 0x00;
  //���������� � ����
  TIM1->PSC = INIT_COM_TIMER_PRESCALER;//0
  //������������� ������ overflow �������
  TIM1->ARR = INIT_COM_TIMER_PERIOD;
  //update event ��� ����� ������ ���, ��� ������ �����������
  TIM1->RCR = 0x00;
  //������� ����� ����������
  TIM1->SR = ~(TIM_IT_CC3 | TIM_IT_Update);
  //�������� ���������� CC3
  TIM1->DIER |= TIM_IT_CC3;
}
//------------------------------------------------------------------------------
void vPacketsManagerTask (void *pvParameters)
{
  ( void ) pvParameters;
  init_com_timer();
  DMA_USART_prepare_recieve();
  for(;;)
  {
    xSemaphoreTake(Com1RxSemaphore, portMAX_DELAY );
    if(Com1RxReadInd != Com1RxWriteInd)
    {
      Com1RxReadInd++;
      if(Com1RxReadInd >= MAX_COM_QUEUE_LENGTH)
        Com1RxReadInd = 0;
      ComMessage* cMesIn = &Com1RxQueue[Com1RxReadInd];
      uint8_t num = Com1TxWriteInd + 1;
      if(num >= MAX_COM_QUEUE_LENGTH)
        num = 0;
      ComMessage* cMesOut = &Com1TxQueue[num];
      if(process_net_packet(cMesIn, cMesOut) == MODBUS_PACKET_VALID_AND_PROCESSED)
        Com1TxWriteInd = num;
      else
        DMA_USART_prepare_recieve();
    }
    if(Com1TxReadInd != Com1TxWriteInd)
    {
      if(!transmitActive)
      {
        Com1TxReadInd++;
        if(Com1TxReadInd >= MAX_COM_QUEUE_LENGTH)
          Com1TxReadInd = 0;
        ComMessage* cMesOut = &Com1TxQueue[Com1TxReadInd];
        for(int i = 0; i < cMesOut->length; i++)
          com1TxBuffer[i] = cMesOut->data[i];
        DMA_USART_prepare_transmit(cMesOut->length);
        transmitActive= 1;
      }
    }
  }
}
//------------------------------------------------------------------------------

	
