/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/*
uint16_t SinTbl[]={127, 139, 152, 164, 175, 186, 196, 206, 214, 222, 228, 234,\
									 238, 240, 242, 242, 240, 238, 234, 228, 222, 214, 206, 196,\
									 186, 175, 164, 152, 139, 127, 115, 102, 90,  79,  68,  58, \
									 48,  40,  32,  26,  20,  16,  14,  12,  12,  14,  16,  20, \
									 26,  32,	 40,  48,	 58,  68,  79,  90,  102, 115};
*/
uint16_t SinTbl[]={127, 139, 152, 164, 175, 186, 196, 206, 214, 222, 228, 234,\
									 255, 255, 255, 255, 255, 255, 234, 228, 222, 214, 206, 196,\
									 186, 175, 164, 152, 139, 127, 115, 102, 90,  79,  68,  58, \
									 48,  40,  32,  26,  20,  0,   0,   0,   0,   0,   0,   20, \
									 26,  32,	 40,  48,	 58,  68,  79,  90,  102, 115};									 
									 
									 

void TIM1_UP_TIM16_IRQHandler(void)
{
	static uint8_t i=0, j=0;
	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) !=RESET)
	{
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	
	if (j==(sizeof(SinTbl)/sizeof(SinTbl[0]))) 
	{
	j=0;
		
			if (i==0)
			{
			GPIO_SetBits(GPIOB, GPIO_Pin_10);
			i++;
			}
			else
			{
			GPIO_ResetBits(GPIOB, GPIO_Pin_10);
			i=0;			
			}
	
	}

	//TIM1->CCR1 	= SinTbl[j];
	
	TIM1->CCR1 	= SinTbl[j];
	TIM1->CCR2 	= SinTbl[j];
	j++;	
	}


}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
