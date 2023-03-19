#include "user.h"
#include "stm32f10x.h"



// -- System clocks init -------------------------------------------------------
void RCC_init(void)
{

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,  ENABLE);

// Разрешаем тактирование первого DMA модуля	
//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}



// -- GPIOs init ---------------------------------------------------------------
void GPIO_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

/* Output lines for H-Bridge control */
	
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

GPIO_InitStruct.GPIO_Pin = T1H_Pin;
GPIO_Init(T1H_Port, &GPIO_InitStruct);

GPIO_InitStruct.GPIO_Pin = T1L_Pin;
GPIO_Init(T1L_Port, &GPIO_InitStruct);	
	
GPIO_InitStruct.GPIO_Pin = T2H_Pin;
GPIO_Init(T2H_Port, &GPIO_InitStruct);	
	
GPIO_InitStruct.GPIO_Pin = T2L_Pin;
GPIO_Init(T2L_Port, &GPIO_InitStruct);	

// ----------------------------------------------------------------------------
// Отладочный пин - PB10 
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;

GPIO_Init(GPIOB, &GPIO_InitStruct);	
}



extern uint16_t SinTbl[];

// -- TIM1 init ---------------------------------------------------------------
void TIM1_init(void)
{

// Fck_psc = 24MHz, Fck_cnt = 12 MHz, PSC[15:0] = 0x01
// Предделитель TIM1, Fck_cnt = Fck_psc/(PSC+1) = 12 MHz

TIM1-> PSC = 0x01;
TIM1-> ARR = 0xFF;								// TIM1 - like 8-bit timer
	
TIM1-> CR1 |= TIM_CR1_CMS;				// Center-Aligned Mode 1

TIM1 -> DIER |= TIM_DIER_UIE;			// Timer Update interrupt enable

TIM1 -> CCMR1 &= ~TIM_CCMR1_CC1S;	// CC1 Channel is configured as output
TIM1 -> CCMR1 &= ~TIM_CCMR1_CC2S;	// CC2 Channel is configured as output
	
TIM1 -> CCMR1 |= TIM_CCMR1_OC1PE;	// Output Compare 1 Preload enable	
TIM1 -> CCMR1 |= TIM_CCMR1_OC2PE;	// Output Compare 2 Preload enable	

	
// PWM 1 Mode for channel CC1 OCM[2:0] = 0b 110	
TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
TIM1 -> CCMR1 &= ~TIM_CCMR1_OC1M_0;

//	
TIM1 -> CCER |=	TIM_CCER_CC1E | TIM_CCER_CC1NE;
TIM1 -> CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);


// PWM 2 Mode for channel CC2 OCM[2:0] = 0b 111
TIM1 -> CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0;
//TIM1 -> CCMR1 &= ~TIM_CCMR1_OC2M_0;

//	
TIM1 -> CCER |=	TIM_CCER_CC2E | TIM_CCER_CC2NE;
TIM1 -> CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);


//	
TIM1 -> CCR1 = SinTbl[0];
TIM1 -> CCR2 = SinTbl[0];


TIM1 -> BDTR |= 24;								// Total dead-time value set (approx. 1 us total)
TIM1 -> BDTR |= TIM_BDTR_MOE; 

TIM1 -> CR1 |= TIM_CR1_CEN;				// Timer 1 Start



//----------------------------------------------------------------------





}
// *****************************************************************************

















// -- Настройка DMA ------------------------------------------------------------
/* DMA configuration -----------------------------------------------------------

*/
/*
extern uint16_t adc_buff[ADC_BUF_LENGTH];	// Буфер для DMA  ADC->RAM, определен в stm32f10x_it.c

void DMA1_init(void)
{
DMA_InitTypeDef		DMA_Init_struct;

DMA_Init_struct.DMA_PeripheralBaseAddr 	= ADC1_DR_addr;					// Адрес периферии - регистр результата преобразования АЦП для регулярных каналов
DMA_Init_struct.DMA_MemoryBaseAddr 		= (uint32_t)adc_buff;			// Адрес памяти для хранения результата преобразования АЦП_1 
DMA_Init_struct.DMA_DIR	= DMA_DIR_PeripheralSRC;								// Источник - периферия (АЦП)
DMA_Init_struct.DMA_BufferSize = ADC_BUF_LENGTH;								// Количество пересылаемых значений 
DMA_Init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// Запрет инкремента адреса периферии
DMA_Init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;						// Инкремент адреса памяти после пересылки
DMA_Init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_Init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
DMA_Init_struct.DMA_Mode = DMA_Mode_Circular;										// Работа DMA В циклическом режиме
DMA_Init_struct.DMA_Priority = DMA_Priority_Low;
DMA_Init_struct.DMA_M2M = DMA_M2M_Disable;
																
DMA_Init(DMA1_Channel1, &DMA_Init_struct);											// Initialise the DMA
DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);								// DMA 1, Channel 1, Transfer Complete Interrupt enable
//DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, DISABLE);
	
DMA_Cmd(DMA1_Channel1, ENABLE); 
}

*/



// -- Настройка прерываний в NVIC ----------------------------------------------
void NVIC_init(void)
{

NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0);	 // Priority set
NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
	
}



