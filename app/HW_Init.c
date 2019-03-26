
//------------------------------------------------------------------------------
//SS160110 Conteggio della base dei tempi 
//ecco qui
//------------------------------------------------------------------------------
#include "time.h"


//------------------------------------------------------------------------------
// data creazione SS160110
//
//
//
//------------------------------------------------------------------------------
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define HW_INIT_C
	#include "HW_Init.h"
#undef HW_INIT_C


//------------------------------------------------------------------------------
//  72 MHZ è il clock del timer 
//  contare 72000000-> 1sec
//  72000  -> 1msec
//  7200 ->100 usec
//------------------------------------------------------------------------------
void InitSysTick(void)
{
  SysTick->LOAD = 7200 - 1;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE | SysTick_CTRL_TICKINT | SysTick_CTRL_ENABLE;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void HW_Sys_Tick_Handler(void)
{ 
  #define MSEC_1  9  //[va da 0..9]
 
	
  
   if (tick100us>= MSEC_1)
   {
     tick100us  = 0;
     main_time++;
   }
  
  
  
  main_time_100us++;
	
  tick100us++;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//120126AN commissionata e creata su specifica di MD
void HW_PortBit_Init(GPIO_TypeDef *_port, unsigned long _pin, unsigned int _mode, unsigned int _speed)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = _pin;
  GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)_mode;
  GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)_speed;
  GPIO_Init(_port, &GPIO_InitStructure);
}


void HW_Port_Init(void)
{

 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);

  // ingresso analogico digitale sul pin GPIA_in0 e in 1
  HW_PortBit_Init(GPIOA,GPIO_Pin_0,  GPIO_Mode_AIN, GPIO_Speed_50MHz );
  HW_PortBit_Init(GPIOA,GPIO_Pin_1,  GPIO_Mode_AIN, GPIO_Speed_50MHz );
  
  HW_PortBit_Init(GPIOA,GPIO_Pin_2,  GPIO_Mode_Out_PP, GPIO_Speed_50MHz );
  
  HW_PortBit_Init(GPIOA,GPIO_Pin_9,  GPIO_Mode_AF_PP          , GPIO_Speed_50MHz );      //TX1 per wifi
  HW_PortBit_Init(GPIOA,GPIO_Pin_10,    GPIO_Mode_IPU           , GPIO_Speed_50MHz );      //RX1
  

  // colpo di reset e accensione della periferica
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,DISABLE);
  // remap pin per port b pb3 e pb4 normalmente usate dal debugger
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 
  AFIO->MAPR = AFIO_MAPR_SWJ_CFG_1; 

  HW_PortBit_Init(GPIOB,GPIO_Pin_1,  GPIO_Mode_Out_PP, GPIO_Speed_50MHz );
  HW_PortBit_Init(GPIOB,GPIO_Pin_2,  GPIO_Mode_Out_PP, GPIO_Speed_50MHz );
  HW_PortBit_Init(GPIOB,GPIO_Pin_3,  GPIO_Mode_Out_PP, GPIO_Speed_50MHz );
  //GPIO_PinRemapConfig();
  HW_PortBit_Init(GPIOB,GPIO_Pin_4,  GPIO_Mode_Out_PP, GPIO_Speed_50MHz );
  HW_PortBit_Init(GPIOB,GPIO_Pin_11,  GPIO_Mode_Out_PP, GPIO_Speed_50MHz );
                               	
}


void clk_init(void)
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
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_8);
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
 // RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void AdcInit(void)
{
  //http://www.micromouseonline.com/2009/05/26/simple-adc-use-on-the-stm32/
   ADC_InitTypeDef  ADC_InitStructure;
  /* PCLK2 is the APB2 clock */
  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  /* Enable ADC1 clock so that we can talk to it */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Put everything back to power-on defaults */
  ADC_DeInit(ADC1);

  /* ADC1 Configuration ------------------------------------------------------*/
  /* ADC1 and ADC2 operate independently */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  /* Disable the scan conversion so we do one at a time */
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  /* Don't do contimuous conversions - do them on demand */
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  /* Start conversin by software, not an external trigger */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  /* Conversions are 12 bit - put them in the lower 12 bits of the result */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  /* Say how many channels would be used by the sequencer */
  ADC_InitStructure.ADC_NbrOfChannel = 1;

  /* Now do the setup */
  ADC_Init(ADC1, &ADC_InitStructure);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
 
  
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
unsigned char readADC1(unsigned long *value,unsigned char channel)
{
  unsigned char retval;
  enum
  {
    IDLE_STATE,
    ATTENDI_FINE,
  };
  
  static char fase_automa = IDLE_STATE;
  
  
  retval  = OP_PENDING;
  
  switch (fase_automa)
  {
    case IDLE_STATE:
    {
      ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
      // Start the conversion
      ADC_SoftwareStartConvCmd(ADC1, ENABLE);
      fase_automa = ATTENDI_FINE;
      
      
    }
    break;
    case ATTENDI_FINE:
    {
      if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
        break; 
     // Get the conversion value
     *value  = ADC_GetConversionValue(ADC1);
     
     fase_automa = IDLE_STATE;
     
     retval  = OP_COMPLETED;
    }
    break;
    
  }
    
  return retval;

  
}


