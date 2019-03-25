// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Project	: MT095 Brushless Driver
// Module		: SERIAL
// File			: SERIAL.H
// Created	: 14.7.5
// By				: Ing. Michele Dondi
// Abstract	: Comunicazioni seriali
//
// 050714 v1.00 creazione
//
//
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// FILE INCLUDE
#include "includes.h"
#include "common_def.h"

// prj includes
#include "hw_init.h"
//#include "vars.h"
#include "main.h"
#include "time.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
//#include "task_main.h"

 
#define SERIAL_C
  #include "serial.h"
#undef  SERIAL_C






// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
//							S T A R T   C O D I C E
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//																	gestione seriali
// ----------------------------------------------------------------------------

void Com_Init(void)
{
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;	
	
 // float usartdiv;
 // unsigned short mantissa,frac;
	
//  RCC_ClocksTypeDef _RCC_Clocks;

#ifdef USE_COM_0
	// Inizializzazione strutture gestione seriale 0
#ifdef EVALUATION_BOARD_GRANDE
 GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
#endif

	com[0].rx_buf			= rx_buf_com0;
	com[0].rx_buf_len = RX_BUF_LEN_0;
	com[0].rx_in			= 0;
	com[0].rx_out			= 0;

	com[0].tx_buf			= tx_buf_com0;
	com[0].tx_buf_len = TX_BUF_LEN_0;
	com[0].tx_in			= 0;
	com[0].tx_out			= 0;

	com[0].fase_rx 		= 0;
#endif

#ifdef USE_COM_1
	// Inizializzazione strutture gestione COM 1
  // utilizzata per comunicazione inverter 
	com[1].rx_buf			= rx_buf_com1;  // COM 1 USART 2
	com[1].rx_buf_len = RX_BUF_LEN_1;
	com[1].rx_in			= 0;
	com[1].rx_out			= 0;

	com[1].tx_buf			= tx_buf_com1;
	com[1].tx_buf_len = TX_BUF_LEN_1;
	com[1].tx_in			= 0;
	com[1].tx_out			= 0;

	com[1].fase_rx 		= 0;
#endif
	
#ifdef USE_COM_2  
	// Inizializzazione strutture gestione seriale 2  modbus chip 485
   
	com[2].rx_buf			= rx_buf_com2;
	com[2].rx_buf_len = RX_BUF_LEN_2;
	com[2].rx_in			= 0;
	com[2].rx_out			= 0;

	com[2].tx_buf			= tx_buf_com2;
	com[2].tx_buf_len = TX_BUF_LEN_2;
	com[2].tx_in			= 0;
	com[2].tx_out			= 0;
	com[2].fase_rx 		= 0;
#endif

#ifdef USE_COM_3_SPI2
	#define COM_NUM 3
	
	// Inizializzazione strutture gestione SPI2
	com[COM_NUM].rx_buf			= rx_buf_com3;
	com[COM_NUM].rx_buf_len = BUF_LEN_3;
	com[COM_NUM].rx_in			= 0;
	com[COM_NUM].rx_out			= 0;

	com[COM_NUM].tx_buf			= tx_buf_com3;
	com[COM_NUM].tx_buf_len = BUF_LEN_3;
	com[COM_NUM].tx_in			= 0;
	com[COM_NUM].tx_out			= 0;

	com[COM_NUM].fase_rx 		= 0;
	
	#undef COM_NUM
#endif

#ifdef USE_COM_0
   // MODULO WIFI 115200 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel 	= USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	
	// Inizializzazione HW seriale 1	
  USART_InitStruct.USART_BaudRate = WIFI_BAUD_115200; // CON IL MODULO WIFI VADO A 115200
  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
  USART_InitStruct.USART_StopBits=USART_StopBits_1;
  USART_InitStruct.USART_Parity=USART_Parity_No;
  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  
  // Per questa seriale HardwareFlowControl ON Su CTS  e RTS
  //USART_InitStruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_RTS_CTS;	
  USART_InitStruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;		
	USART_Init(USART1, &USART_InitStruct);	
	
	USART_Cmd(USART1, ENABLE);		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART_STM, USART_IT_TXE, ENABLE);	
	//USART_ITConfig(USART_STM, USART_IT_TC, ENABLE);
#else
  // canale non usato
  // xxx add eventuali power off
#endif

#ifdef USE_COM_1
	// Inizializzazione HW seriale 1

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel 	= USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	
  USART_InitStruct.USART_BaudRate = INV_BAUD_38400;//9600
  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
  USART_InitStruct.USART_StopBits=USART_StopBits_1;
  USART_InitStruct.USART_Parity=USART_Parity_No;
  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;		
	USART_Init(USART2, &USART_InitStruct);	
	
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  //USART_ITConfig(USART2, USART_IT_TC, ENABLE);
  // USART_IT_TXE VIENE attivato in sveglia tx
  
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	
	//USART_ITConfig(USART_485, USART_IT_TC, ENABLE);
#else
  // canale non usato
  // xxx add eventuali power off
#endif
	
// ----------------------- USART 3 	 --------------------------------------------------------------

#ifdef USE_COM_2
	// Inizializzazione HW seriale 2
  //120131AN usata per 485 in MT300.PNE

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
	
   
	
	NVIC_InitStructure.NVIC_IRQChannel 	= USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 12;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	
  USART_InitStruct.USART_BaudRate =  MODBUS_485_9600;
  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
  USART_InitStruct.USART_StopBits=USART_StopBits_1;
  USART_InitStruct.USART_Parity=USART_Parity_No;
  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;		
	USART_Init(USART3, &USART_InitStruct);	
	
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	
	//USART_ITConfig(USART_STM, USART_IT_TXE, ENABLE);	
	//USART_ITConfig(USART_485, USART_IT_TC, ENABLE);
#else
  // canale non usato
  // xxx add eventuali power off
#endif

}


// ----------------------------------------------------------------------------

void PutByte(uchar _com, uchar _ch)
{
	com[_com].tx_buf[com[_com].tx_in++] = _ch;
	if (com[_com].tx_in >= com[_com].tx_buf_len)
		com[_com].tx_in = 0;
}

void PutString(uchar _com, uchar *_str)
{
	while (*_str)
		PutByte(_com, *_str++);

}

void PutLong(uchar _com, long _val, uchar _len)
{
	uchar i;
	long mask = 1;

	if (_val < 0)
	{
		PutByte(_com, '-');
		_val *= -1;
		
		if (_len) _len--;
	}
		
	for(i = 0; i < _len - 1; i++)
		mask *= 10;

	for(i = 0; i < _len; i++)
	{
		PutByte(_com, _val / mask + '0');
		_val %= mask;
		mask /= 10;
	}

}

void Put_Hex(uchar _com, ulong _val, uchar _len)
{
	uchar i;
	ulong mask = 0x00000001;
	uchar appo;
	
	for(i = 0; i < _len - 1; i++)
		mask <<= 4;

	for(i = 0; i < _len; i++)
	{
		appo = _val / mask + '0';
		if (appo > '9')
			appo += 'A' - '0' - 10;
		_val %= mask;
		PutByte(_com, appo);
		//
		mask >>= 4;
	}

}




// ------------------------------------------------------------------------
//

void Put_and_ck(uchar _com, uchar car)
{
	com[_com].tx_calc_ck += (unsigned long)car;
	PutByte(_com, car);
}

// vede se risvegliare la Tx ----------------------------------------------
//
void Sveglia_tx(uchar _com)
{
	if (com[_com].tx_in != com[_com].tx_out)
	{
		switch(_com)
		{
		case 0:
			USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
			break;
		case 1:
    {
      USART2_DISABLE_RX;  // seriale half duplex a 1 filo 
			USART_ITConfig(USART2, USART_IT_TXE, ENABLE);// abilito trasmissione 
    }
		break;
		case 2:
			USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
			break;
		case 3:

			break;
		}
	}
}

// ------------------------------------------------------------------------
//
uchar BytesInReceiveBuffer(uchar _com)
{
	if (com[_com].rx_in == com[_com].rx_out)
		return 0;
	return 1;

}

uchar BytesInTxBuffer(uchar _com)
{
	if (com[_com].tx_in == com[_com].tx_out)
		return 0;
	return 1;
}

// ------------------------------------------------------------------------
//
uchar GetByte(uchar _com)
{
	uchar ret_val;
	if (com[_com].rx_in == com[_com].rx_out)
		return 0;
	
	ret_val = com[_com].rx_buf[com[_com].rx_out++];
	if (com[_com].rx_out >= com[_com].rx_buf_len)
		com[_com].rx_out = 0;

	return ret_val;
}

// ------------------------------------------------------------------------
//
uchar Get_and_ck(uchar _com)
{
	uchar car = GetByte(_com);
	com[_com].calc_ck += (unsigned long)car;
	return car;
}

// ------------------------------------------------------------------------
//									R X   D E C O D E
// ------------------------------------------------------------------------


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Rx_decode(uchar _com)
{ 
}




// ------------------------------------------------------------------------------------------------
// 											C O M U N I C A T I O N   M A N A G E R
// ------------------------------------------------------------------------------------------------
// communication master
// gestisce slot comunicazione per vari slave
//

void COM_Comunication_Manager(uchar _com)
{

}

// ----------------------------------------------------------------------------- 
// ----------------------------------------------------------------------------- 



void RxSer0(void)
{
#ifdef USE_COM_0
	rx_buf_com0[com[0].rx_in] = USART_ReceiveData(USART1);
	com[0].rx_in++;
	com[0].rx_in &= RX_BUF_LEN_0 - 1;
#endif
}


// tx empty ch 0 ----------------------------------------------------
void TxSer0(void)
{	
#ifdef USE_COM_0
	
	if (com[0].tx_in != com[0].tx_out) //  && TX0_READY credo inutile
	{
		// qualcosa da trasmettere		
		USART_SendData(USART1, tx_buf_com0[com[0].tx_out]);
		com[0].tx_out++;
		com[0].tx_out &= TX_BUF_LEN_0 - 1;

	}
	else
	{ // niente da trasmettere -> disabilito interrupt tx empty
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		TxEndSer0();
	}
#endif		
}

// tx completed (last char) ch 0 ----------------------------------
void TxEndSer0(void)
{

}

/// rx ch 1 --------------------------------------------------------
void RxSer1(void)
{
#ifdef USE_COM_1
		
#ifdef MEGABUFFER_COM
		megabuffer[megabuffer_in] = rx_buf_com1[com[1].rx_in] = USART_ReceiveData(USART2);
		com[1].rx_in++;
		com[1].rx_in &= RX_BUF_LEN_1 - 1;
		megabuffer_in++;
		if (megabuffer_in >= MEGABUFFER_SIZE)
			megabuffer_in = 0;
#else
		rx_buf_com1[com[1].rx_in] = USART_ReceiveData(USART2);
		com[1].rx_in++;
		com[1].rx_in &= RX_BUF_LEN_1 - 1;
#endif		
		
#endif
}


// tx empty ch 1 ----------------------------------------------------
void TxSer1(void)
{
#ifdef USE_COM_1

	if (com[1].tx_in != com[1].tx_out) //  && TX1_READY credo inutile
	{ // qualcosa da trasmettere
		
		USART_SendData(USART2, tx_buf_com1[com[1].tx_out]);
    
#ifdef MEGABUFFER_COM
		megabuffer[megabuffer_in] = tx_buf_com1[com[1].tx_out];
		megabuffer_in++;
		if (megabuffer_in >= MEGABUFFER_SIZE)
			megabuffer_in = 0;
#endif		
		com[1].tx_out++;
		com[1].tx_out &= TX_BUF_LEN_1 - 1;
	}
	else
	{ // niente da trasmettere -> disabilito interrupt tx empty
		USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
   
		//TxEndSer1();
	}

#endif
}

// tx completed (last char) ch 0 ----------------------------------
void TxEndSer1(void)
{
  // riabilitazione ricezione 
}

// rx ch 2 --------------------------------------------------------
void RxSer2(void)
{
#ifdef USE_COM_2

		rx_buf_com2[com[2].rx_in] = USART_ReceiveData(USART3);
		com[2].rx_in++;
		com[2].rx_in &= RX_BUF_LEN_2 - 1;
				
#endif
}

// tx empty ch 2 ----------------------------------------------------
void TxSer2(void)
{
#ifdef USE_COM_2

	if (com[2].tx_in != com[2].tx_out) //  && TX1_READY credo inutile
	{ // qualcosa da trasmettere
		
		//GPIO_WriteBit(_485_ENABLE_PORT,_485_ENABLE_PIN,_485_OUTPUT_MODE);
		//SET_485_OUTPUT_MODE;
   // _485EN_ON;
    
		DISABLE_RX(USART3);
    USART3_DISABLE_RX;
		USART_SendData(USART3, tx_buf_com2[com[2].tx_out]);
		com[2].tx_out++;
		com[2].tx_out &= TX_BUF_LEN_2 - 1;
	}
	else
	{ // niente da trasmettere -> disabilito interrupt tx empty
		USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    USART3_ENABLE_RX;
		TxEndSer2();
	}
#endif

}

// tx completed (last char) ch 0 ----------------------------------
void TxEndSer2(void)
{
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);	
}

void TxSer2_Complete()
{
	//GPIO_WriteBit(_485_ENABLE_PORT,  _485_ENABLE_PIN,_485_INPUT_MODE);
	//SET_485_INPUT_MODE;

  //_485EN_OFF;

	USART_ITConfig(USART3, USART_IT_TC, DISABLE);	
	ENABLE_RX(USART3);
}


//------------------------------------------------------------------------------
// SS160118
// Funzione che setta il bauda rate (registro BRR) per cambiare la 
// velocità di comunicazione in corsa.
//-------------------------------------------------------------------------------
void Setting_Baud_Rate(unsigned char setpoint_baud)
{
  static unsigned char baud_rate_setted = 0;
  
  if (baud_rate_setted  !=  setpoint_baud)
  {
    baud_rate_setted  = setpoint_baud;
    
    USART2->CR1&=0xdfff;// disable com
    USART2->BRR  = uart2_brr[setpoint_baud];  
    USART2->CR1|=0x2000;//enable com
  }
  
}
