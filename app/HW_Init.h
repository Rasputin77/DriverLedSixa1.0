#include "includes.h"

#ifndef HW_INIT_H
  #define HW_INIT_H

  #define OP_COMPLETED 0
  #define OP_PENDING   1 
	

#endif 


#include "stm32f10x_conf.h"

#ifdef HW_INIT_C

	
  
#else


#endif

// Qui sotto :prototipi funzioni
void HW_PortBit_Init(GPIO_TypeDef *_port, unsigned long _pin, unsigned int _mode, unsigned int _speed);
void clk_init(void);
void InitSysTick(void);
void HW_Sys_Tick_Handler(void);
void HW_Port_Init(void);
void AdcInit(void);
unsigned char readADC1(unsigned long *value,unsigned char channel);



  