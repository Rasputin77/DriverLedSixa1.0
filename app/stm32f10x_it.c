/**
  ******************************************************************************
  * @file    stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    29-June-2012
  * @brief   Main Interrupt Service Routines.
  *                      This file provides template for all exceptions handler
  *                      and peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "DALIslave.h"
#include "serial.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t Index = 0;
static __IO uint32_t AlarmStatus = 0;
static __IO uint32_t LedCounter = 0;
extern GPIO_TypeDef* DALIIN_port;
extern TRTC_1ms_Callback * RTC_1ms_Callback;
__IO uint16_t oneMScounter;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/


void NMIException()
{
}

/**
* @brief  This function handles NMI exception.
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
* @brief   This function handles PendSVC exception.
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
  HW_Sys_Tick_Handler();

}

/**
* @brief  This function handles RTC global interrupt request.
* @param  None
* @retval None
*/
void RTC_IRQHandler(void)
{

}
/**
* @brief  This function handles External interrupt Line 3 request.
* @param  None
* @retval None
*/
void EXTI4_IRQHandler(void)
{

}

/**
* @brief  This function handles External lines 0 interrupt request.
* @param  None
* @retval None
*/
void EXTI0_IRQHandler(void)
{
 
 //   EXTI_ClearITPendingBit(EXTI_Line0);
  
}
/**
* @brief  This function handles External lines 9 to 5 interrupt request.
* @param  None
* @retval None
*/
void EXTI9_5_IRQHandler(void)
{

}
/**
* @brief  This function handles TIM1 overflow and update interrupt
*          request.
* @param  None
* @retval None
*/
void TIM1_UP_IRQHandler(void)
{
  /* Clear the TIM1 Update pending bit */
 // TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
/**
* @brief  This function handles SPI2 global interrupt request.
* @param  None
* @retval None
*/
void SPI2_IRQHandler(void)
{

}
/**
* @brief  This function handles USART1 global interrupt request.
* @param  None
* @retval None
*/
void USART1_IRQHandler(void)
{
  	if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)
	{
		//u32 appo;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		//appo=USART1->SR;
		//appo=USART1->DR;
		RxSer0();
	}
  else if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	{
    TxSer0();
  }
  else if(USART_GetITStatus(USART1, USART_IT_TC)  ==  SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
		 
	}	
  // cancello comunque eventuali bit che riguardano errori nel frame di risposta 
  // che potrebbero riamnere pendenti 
  
  USART_ClearITPendingBit(USART1,USART_IT_ERR);
  
  USART_ClearITPendingBit(USART1,USART_IT_ORE);
 
}


/**
* @brief  This function handles External lines 15 to 10 interrupt request.
* @param  None
* @retval None
*/
void EXTI15_10_IRQHandler(void)
{


}
/**
* @brief  This function handles RTC Alarm interrupt request.
* @param  None
* @retval None
*/
void RTCAlarm_IRQHandler(void)
{

}
/**
* @brief  This function handles SDIO global interrupt request.
* @param  None
* @retval None
*/
void SDIO_IRQHandler(void)
{

}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
void PPP_IRQHandler(void)
{
}




