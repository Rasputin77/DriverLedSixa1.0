

#define MAIN_C
  #include "main.h"
#undef MAIN_C

#include <stdio.h>
#include <string.h>
#include "time.h"
#include "hw_init.h"
#include "rtc.h"
#include "serial.h"





unsigned char leggi_temperatura(unsigned long *tens)
{
  static unsigned long tensione_acc = 0;
  static unsigned short count_acc=0;
  static unsigned long tensione=0;
  unsigned char ret_val=0;
  
 // static unsigned char fase_temp= IDLE_STATE;
  
   
  
  if (readADC1(&tensione,ADC_Channel_0)== OP_COMPLETED)
  {
    tensione_acc+=tensione;
    count_acc++;
  }
   
  if (count_acc == 100)
  {
    *tens = tensione_acc/100;
    tensione_acc = 0;
    count_acc=0;
    ret_val= OP_COMPLETED;
  }
  else 
    ret_val = OP_PENDING;
 
return ret_val;
     
}






/* Private function ----------------------------------------------------------*/
/**
* @brief   main program body
* @param   None
* @retval  None
*/
int main(void)
{
  static unsigned long tens_val;
  RTC_t tempo;
  
  
  

  //RCC_Configuration();
  InitSysTick();// inizializzo contatore 100 usec
  
 
 
  
  HW_Port_Init();
  
  

  //RTCInit();
  //Com_Init();
  
  RCC_ClocksTypeDef dammi_il_clock2;
  RCC_GetClocksFreq(&dammi_il_clock2);
 
  AdcInit();

//http://www.keil.com/forum/61321/back-up-battery-for-rtc-of-stm32f103rb/
  
  
  LED_VITA_ON;
  EXT_LED_VITA_ON;
//  rtc_gettime (&tempo);
//  tempo.month =  7;
//  tempo.year  = 2017;
//  tempo.mday  = 5;
//  rtc_settime (&tempo);
  /* main program loop */
  while(1)
  {
   
  
    if (leggi_temperatura(&tens_val) == OP_COMPLETED)
    {
      
      
      tensione=((float)(tens_val)/4096.0)*3300;// tensione in mV sul sensore
      temperatura_media=((tensione -424)/6.25 ); //VO = (6.25 mV/°C × T°C) + 424 mV vedi datasheet
      //memset(temperatura_str,0,20); 
      temperatura_str[0]=0;
      sprintf(temperatura_str,"temp acqua: %2.1f",temperatura_media);
      jj  = 0;
      while (temperatura_str[jj]!=0)
        jj++;
      temperatura_str[jj] = 0x0d;//CR
      temperatura_str[jj+1] = 0x0d;//CR
      
    }
    if( GetTime(&Time_led)  >=  TEMPO_VITA_LED)
    { 
      ResetOrol(&Time_led);
//      if (com[WIFI_COM].tx_in == com[WIFI_COM].tx_out)
//      {
//     
//        jj  = 0;   
//        while (temperatura_str[jj]!=0)
//        {
//          
//          PutByte(WIFI_COM,temperatura_str[jj]);
//          
//          jj++;
//          
//        }
//      }
      if (valore)
      {
        valore  = 0;
        LED_VITA_ON;
        EXT_LED_VITA_ON;
        POMPA_ON;
      }
      else
      {
        valore  = 1;
        LED_VITA_OFF; 
        EXT_LED_VITA_OFF;
        POMPA_OFF;
      }
    }
   Sveglia_tx(WIFI_COM);  
  //  GPIOB->BSRR = 0x20000; 

  
  } /* while(1) loop */
}

/**
* @brief   PWM for LED light control on STM32 discovery board
*                : control of light level callback function - must be type
*                : TLightControlCallback - see dali.h
* @param   intensity value(mapped inside)
* @retval  None
*/
void PWM_LED(u16 lightlevel)
{
  
}






/**
* @brief   RCC configuration
* @param   None
* @retval  None
*/
void RCC_Configuration()
{
  //-------------------------------------------------------
	//												HSI
	//-------------------------------------------------------
  // 1. Clocking the controller from internal HSI RC (8 MHz)
  RCC_HSICmd(ENABLE);
  // wait until the HSI is ready
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
//  //Setto HSI come clock solo per
//  //fare i settaggi, alla fine metto
//  //PLL come System clock
//  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);


  //-------------------------------------------------------
	//												HSE
	//-------------------------------------------------------
  // 2. Enable ext. high frequency OSC
  RCC_HSEConfig(RCC_HSE_ON);
  // wait until the HSE is ready
  while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
  //Setto HSI come clock solo per
  //fare i settaggi, alla fine metto
  //PLL come System clock
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);


  //-------------------------------------------------------
	//												PLL
	//-------------------------------------------------------
	//HSE = 8MHz
	//Setto sorgenyte del PLL HSE e lo moltiplico per 8
	//RCC_CFGR.PLLSRC = 1	
	//RCC_CFGR.PLLMUL = 8
	//PLL allora 8*8 = 64 MHz

  
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
  RCC_PLLCmd(ENABLE);
  // wait until the PLL is ready
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

  //-------------------------------------------------------
	//												Vari prescaler
	//-------------------------------------------------------
  //Set system clock dividers
  //Qui si settano clock per clock le frequenze
  //che si vogliono in funzione della frequenza
  //di SYSCLK
  //Divisore dell'usb
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

//Divisore del systemclock
  RCC_HCLKConfig(RCC_SYSCLK_Div1);

	//64MHz è SYSCLK
	//lo divido per	8 ottengo
	//PCLK1 = 8MHz
	//Qui c'è la periferica CAN
	//oltre ad altre..
	//Divisore del PCLK1 -> APB1
	
	// 11/01/2012 15.05.41AN devo buttare a manetta PCLK1 perchè è quello che comanda SPI2
  // HCLK è a 64MHz ma PCLK1 può andare al massimo a 36MHz...
  // devo dividere almeno per 2
  // SPI2,3 - TIM2,3,4
	RCC_PCLK1Config(RCC_HCLK_Div2);  	// PCLK1	32MHz
	
  // Divisore del PCLK2 -> APB2
  // ADC - TIM1 - GPIO - SPI1 -
  RCC_PCLK2Config(RCC_HCLK_Div1);		// PCLK2 	64MHz

	//Divisore del clock ADC
	// Non superare mai 14MHz
  RCC_ADCCLKConfig(RCC_PCLK2_Div8);	// ADCCLK 8Mhz

	
  //-------------------------------------------------------
	//												FLASH
	//-------------------------------------------------------
//	#ifdef EMB_FLASH
		// 5. Init Embedded Flash
	  // Zero wait state, if 0 < HCLK 24 MHz
	  // One wait state, if 24 MHz < HCLK 48 MHz
	  // Two wait states, if 48 MHz < HCLK 72 MHz
	  // Flash wait state
	  FLASH_SetLatency(FLASH_Latency_2);
	  // Half cycle access
	  FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
	  // Prefetch buffer
	// 110317MD xxx vedere con AN tolto per vedere se dava problemi... va rimesso ???? 17/03/2011 17:12
//	  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//	#endif // EMB_FLASH
	
	
	//-------------------------------------------------------
	//				System clock di funzionamento
	//-------------------------------------------------------
  //Setto PLL come clock di sistema
  //RCC_CFGR.SW = 0x10
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
}

/**
* @brief   Configure a SysTick Base time
* @param   None
* @retval  None
*/
void SysTick_Configuration(void)
{
//  if (SysTick_Config(SystemCoreClock / 9600))
//  {
//    /* Capture error */
//    while (1);
//  }

 }


/**
* @brief   Inserts a delay time.
* @param   specifies the delay time length (time base 10 ms
* @retval  None
*/
void Delay(__IO uint32_t nCount)
{
  TimingDelay = nCount;

  /* Enable the SysTick Counter */
  SysTick->CTRL |= SysTick_CTRL_ENABLE;

  while(TimingDelay != 0);

  /* Disable the SysTick Counter */
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

  /* Clear the SysTick Counter */
  SysTick->VAL = (uint32_t)0x0;
}

/**
* @brief   Decrements the TimingDelay variable.
* @param   None
* @retval  None
*/
void Decrement_TimingDelay(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
  RandomTimingCnt++;
}

/**
* @brief   Returns the HSE StartUp Status
* @param   None
* @retval  HSE StartUp Status.
*/
ErrorStatus Get_HSEStartUpStatus(void)
{
  return (HSEStartUpStatus);
}

#ifdef USE_FULL_ASSERT
/**
* @brief   Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* @param    file: pointer to the source file name
* @param    line: assert error line source number
* @retval   None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif



/**
* @}
*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
