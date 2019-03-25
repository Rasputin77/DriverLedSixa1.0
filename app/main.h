/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    07-Dec-2012
  * @brief   Header for main.c module
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


/* Define to prevent recursive inclusion -------------------------------------*/
#include "stm32f10x_it.h"

#ifndef __MAIN_H
  #define __MAIN_H

  #define TEMPO_VITA_LED         1000
  #define LOW_POWER_TIMEOUT      2000  // 2 seconds to go to sleep/halt
  
  #define LED_VITA_ON      GPIOB->BSRR|= 0x02
  #define LED_VITA_OFF     GPIOB->BSRR|=0x20000
  #define EXT_LED_VITA_ON  GPIOB->BSRR|= 0x10
  #define EXT_LED_VITA_OFF GPIOB->BSRR|= 0x100000
  #define POMPA_ON         GPIOB->BSRR|= 0x08
  #define POMPA_OFF        GPIOB->BSRR|=0x80000


#endif 



//------------------------------------------------------------------------------
#ifdef MAIN_C

  static __IO uint32_t SELStatus = 0;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  static __IO uint32_t TimingDelay = 0;
  __IO uint16_t RandomTimingCnt = 0;
  static __IO uint32_t LedShowStatus = 0;
  static __IO ErrorStatus HSEStartUpStatus = SUCCESS;
  volatile u16 LEDlight;                // current light level
  u16 HALTtimer;                       // timeout counter for low power mode
  unsigned char valore=0;
  unsigned long Time_led=0;
  float tensione=0.0;
  float temperatura_media=0.0;
  int jj=0;
   char temperatura_str[20];
#else
  

#endif
//Qui sotto i prototipi  
void PWM_LED(u16 lightlevel);
void SysTick_Configuration(void);
void Delay(__IO uint32_t nCount);
void Decrement_TimingDelay(void);
ErrorStatus Get_HSEStartUpStatus(void);
void HW_Sys_Tick_Handler(void);
void RCC_Configuration(void);
void SysTick_Configuration(void);
void PWM_LED(u16 lightlevel);
void InitPort(void);
unsigned char leggi_temperatura(unsigned long *tens);
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
