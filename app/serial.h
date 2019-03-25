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
#include "common_def.h"
// #define DEBUG_COM_ERR	// attiva debug dump su seriale 0 per errrori comunicazione
// #define TERM_DUMP					// attiva dump per il debug verso terminale su com PC

// -----------------------------------------------------------------------------
// ---------------------------- DEFINE VARI  -----------------------------------
// -----------------------------------------------------------------------------
#ifndef SERIAL_H
  #define SERIAL_H

  #define USART1_ENABLE_TX 	(USART1->CR1|=(1L<<3))
  #define USART1_DISABLE_TX (USART1->CR1&=~(1L<<3))

  #define USART2_ENABLE_TX 	(USART2->CR1|=(1L<<3))
  #define USART2_DISABLE_TX (USART2->CR1&=~(1L<<3))

  #define USART3_ENABLE_TX 	(USART3->CR1|=(1L<<3))
  #define USART3_DISABLE_TX (USART3->CR1&=~(1L<<3))

  #define USART1_ENABLE_RX 	(USART1->CR1|=(1L<<2))
  #define USART1_DISABLE_RX (USART1->CR1&=~(1L<<2))

  #define USART2_ENABLE_RX 	(USART2->CR1|=(1L<<2))
  #define USART2_DISABLE_RX (USART2->CR1&=~(1L<<2))
    
  #define USART3_ENABLE_RX 	(USART3->CR1|=(1L<<2))
  #define USART3_DISABLE_RX (USART3->CR1&=~(1L<<2))

  // -----------------------------------------------------------------------------
  // blu, rosso, verde
  // ---------------------------- DEFINE VARI  -----------------------------------
  // -----------------------------------------------------------------------------
  #define MODBUS_COM			2						  // abilitazione comunicazione MODBUS 485 usart 3
  #define DRIVE_COM			  1							// Com Iso verso Inverter  USE_COM_1 usart2
  #define WIFI_COM			  0             // SS 150414 COM PER WIFI USE_COM_0  usart 1
  
  //#define USE_COM_2                     // abilita uso UART3    COM MODBUS
  //#define USE_COM_1                     // abilita uso UART2    inverter
  #define USE_COM_0                      // abilita uso UART1    COM WIFI PC 

                                        //PIN PA2 PA3 PER COMUNICAZIONE INVERTER 

  // ------------------------------------------------------------------
  // gestione pacchetti

  // per campo validation
  #define RX_VALID			0x01	
  #define RX_PROCESSING	0x02
  #define RX_NOT_VALID	0x04	

  // 22/06/2011 8.50.40 MB #define COM1_485	// compensa mancanza pull-up rx max487 ma non compatibile con sistema
									// multi pacchetto che usa full duplex in RS232
  // serial com
  // l'header è lungo [, id, mitt, dest, tipo, addr x 4, len, cksum x 4, ] = 15 byte
  
  #define RX_BUF_LEN_0	64         //28/01/2015 15:11:00 SS  per wifi          
  #define TX_BUF_LEN_0	64         //28/01/2015 15:11:09 SS  Per wifi

  #define RX_BUF_LEN_1	64            // deve essere 2^n  INVERTER COM
  #define TX_BUF_LEN_1	64            // Questa è la com di comunicazione con inv

  #define RX_BUF_LEN_2	64             // 29/08/2011 16.04 VA  era 32
  #define TX_BUF_LEN_2	64             // 29/08/2011 16.04 VA  era 32
  #define RX_BUF_LEN_3	64             //
  #define TX_BUF_LEN_3	64             //


  #define RX_BUF_LEN_4	2048         //28/01/2015 15:11:00 SS  per wifi
  #define TX_BUF_LEN_4	1024         //28/01/2015 15:11:09 SS  Per wifi

  #define NUM_MAX_VAR_TO_WRITE      100 // lunghezza vettore degli indici delle 
                                        // var da scrivere


  #define EXT_CMD_STR_LEN 30
  
  //----------------------------------------------------------------------------
  
  // #define LSB_LOW							// per CPU PC ok, per H8 no
  #define FRAMING_TIMEOUT								50		// [ms] usato in RxDecode per link seriali std

  	//#define XTL 72000000l
	//#define XTL 16000000l
	//#define XTL 8000000l

	//#define XTL_TIM1  32000000L //64000000l //120131AN APB1 è a 32Mhz
	#define XTL_TIM2  64000000l
	#define XTL_TIM3  64000000l
	//#define XTL_TIM4  64000000l
  
 
  
  #define INV_BAUD_38400    38400L
  #define WIFI_BAUD_115200  115200L
  #define MODBUS_485_9600   9600L


  // ------------------------------------------------------------------
  //								G E S T I O N E    S E R I A L I
  // ------------------------------------------------------------------

  #define PACK_TYPE_INFO				'i'		// richiesta info ASCII da consolle
  #define PACK_TYPE_READ				'r'		// richiesta lettura
  #define PACK_TYPE_WRITE				'w'		// scrittura
  #define PACK_TYPE_SPONTANEOUS	's'		// pacchetto spedito spontaneamente dallo slave (per ora non prvede risposta)

  //comandi seriali per gestione Upgrade

	#define BOOT_FUNCTION				'B'
	#define BOOT_TOTALFRAME			'A'
	#define BOOT_WRITESRECORD		'W'
	
	// MB151103 aggiungo per la gestione del buffer di tipo 4
	#define BUFFER_TYPE_4				0x04
  
  //tempi di attesa e timeout per upgrade
	//fase WAIT_WR_SRECORD
	#define TIMEOUT_ANSWER_WR_SRECORD		5000 //ms 
	//fase WAIT_SINCRO
	#define TEMPO_ATTESA_SINCRONISMO		500 //ms  // era 1000
	//fase WAIT_SINCRO
	#define TIMEOUT_RESET_INVERTER			300//ms
  #define TEMPO_DI_RESET_INVERTER     200//ms  //80
  #define INACTIVITY_TIME_FRAME       10  // A 30 SI BLOCCA L'AGGIORNAMENTO //60 
  #define NUM_TENTATIVI_MAX           3
  #define WAIT_INV_ON_TIME            1000
  // gestione pacchetti

  // per campo validation
  #define RX_VALID  		0x01
  #define RX_PROCESSING	0x02
  #define RX_INCOMING   0x03  // Presa da SW Monitor PC
  #define TX_PROCESSING	0x04

  #define MASTER_TIMEOUT					150	// di norma manda un lcd slot ogni circa 110ms							04/02/2014 20:33:00
  //SS160118 era 500 e con oscilloscopio abbiamo visto che al amssimo 7 msec a 38400
  // attenzione possiamo andare a 9600 che 38400 
  #define MASTER_ANSWER_TIMEOUT   50
  #define MASTER_MAX_ERRORS				5		// 02/11/2012 09:53
  
 	//MB151103 aggiungo per gestione della ricezione buffer tipo 4
  #define TIME_OUT_RX_BUFFER_TYPE	750	//era 500 ricordarsi che possiamo andare a 38400 e 9600// ds testare
  
  #define NOTHING_TO_REQUEST  -1

  #define PACK_TYPE_READ_MAX  'M'
  #define PACK_TYPE_READ_MIN  'm'
  
  //AP 02/02/2017 15:27:36
	//vers. 1.0071
  #define PACK_TYPE_NEGATIVE_ANSWER	0x7F
		//codici di risposta negativa ad oggi gestiti
		#define NA_VARS_NOT_PRESENT		1	//parametro richiesto non presente
		#define NA_VARS_NOT_WRITABLE	2	//parametro non scrivibile
		#define NA_WR_LIM_MIN					3	//limite minimo superato, scrittura non avvenuta
		#define NA_WR_LIM_MAX					4 //limite massimo superato, scrittura non avvenuta


    //SS 160118
  // DEFINE PER SCANSIONE BAUD RATE
  #define ID_BAUD_9600  0
  #define ID_BAUD_38400 1
  #define ID_BAUD_MAX   2   
  

	// ---------------------------------------------------------
	// MB151103 aggiungo per gestione buffer tipo 0x04
	typedef struct _buff_data_payload
	{ 
    ulong   time_stamp;
		ulong   id_alarm; 
	}buff_data_payload;
	
	typedef struct _buff_type
  {
  //	buff_data_payload buff_data[SIZE_ALARM_LIST];
  	
    ulong		column_len;					// numero di colonne che compongono il dato completo ( al momento sono solo 2: id_alarm e timestamp, 
    														// vedi buff_data_payload )
    uchar   colum_size;					// quanti byte compongono una colonna
  	ulong		dati_length;				// dice quanti dati completi ci sono (viene calcolato).. non so se utile ma lo salvo lo stesso
  	ulong		dati_size;					// dimensione totale in byte di dati da scaricare
    ushort	dati_rx;						// contatore dei byte ricevuti in fase di ricezione (Rx_Decode_Master)
    
    ulong   Tout_rx_data_buffer;
  }buff_type;
	// ---------------------------------------------------------
	
	
	//
	
  //ss struttura per buffer circolare indici var da scrivere 
  typedef struct _buff_app
  {
    ulong  *rx_buf;			// buffer ricezione
    ushort  rx_buf_len; // mas 16535
    ushort  rx_in;			// puntatore buffer in
    ushort  rx_out;     // puntatore buffer out
     
  }buff_app;

  typedef struct _per_com
  {
    uchar  *rx_buf;			// buffer ricezione
    ushort  rx_buf_len; // MAX 256 !!!
    ushort  rx_in;			// puntatore buffer in
    ushort  rx_out;     // puntatore buffer out

    uchar  *tx_buf;     // buffer trasmissione
    ushort  tx_buf_len; // MAX 256 !!!
    ushort  tx_in;			// puntatore buffer in
    ushort  tx_out;     // puntatore buffer out

    // tipo pacchetti
    uchar   pack_type;   // L = lcd slot start frame, r, w
    uchar   validation;  // 0x01: rx validated
    // decodifica pacchetti
    uchar		fase_rx;
    uchar		*scan_ptr;
    uchar		ricevuti;

    unsigned long	frame_time;

  //	uchar id;
    uchar mitt;
    uchar dest;

    uchar service;
    uchar function;
    uchar service2;
    uchar type;           // ss 150211 Questo l'ho aggiunto io perchè noi gestiamo function, service e tipo 
    ulong service_value;	// contiene i dati di un pacchetto di scrittura, il valore da scrivere nella vars
    ulong address;
    ushort frame_len;		// 21/09/2009 12.12 added per ModBus, contiene lunghezza generica frame, non solo area dati
    uchar data_len;
    uchar data_ptr;			// ptr all'area dei dati ricevuti


    ushort	rx_ck;			// cksum ricevuto
    ushort	calc_ck;		// cksum caclolato

    ushort	tx_calc_ck;	// calcolato per il pacchetto da inviare
    // dim 42
    
    uchar		fwd_size;												// dimensione pacchetto da inoltrare
   // uchar		fwd_data[SIZE_MAX_STD_FRAME];   // dati pacchetto da inoltrare
    
    // bootloader handles
  //	ushort	car_da_scartare;	// da scartare quando uso echo
   // uchar		bl_buf[BOOT_INFO_BUFFER_SIZE];	
    
    uchar		lqi; // Zigbee
    
    // com quality 02/11/2012 10:11
    ushort	wr_ok;
    ushort	rd_ok;
    ushort	errors;
    ushort	master_tout_errs;				//	04/02/2014 20:33:59
    
  } per_com;


  


  // ------------------------------------------------------------------
  //								D I C H I A R A Z I O N E   V A R I A B I L I
  // ------------------------------------------------------------------


  #define DISABLE_RX(u)	(u->CR1 &= ~0x0002)
  #define ENABLE_RX(u)	(u->CR1 |= 0x0002)
	


#endif 


#ifdef SERIAL_C

 #ifdef USE_COM_4
    per_com com[5];
  #elif defined USE_COM_3
    per_com com[4];
  #elif defined USE_COM_2
    per_com com[3];
  #elif defined USE_COM_1
    per_com com[2];
  #else
    per_com com[1];
  #endif
  
  // seriale 0
  #ifdef USE_COM_0
  uchar   rx_buf_com0[RX_BUF_LEN_0];        // buffer ricezione sci1
  uchar   tx_buf_com0[TX_BUF_LEN_0];        // buffer ricezione sci1
  #endif
  
    
   

  // seriale 0
  #ifdef USE_COM_0
    uchar   rx_buf_com0[RX_BUF_LEN_0];        // buffer ricezione sci1
    uchar   tx_buf_com0[TX_BUF_LEN_0];        // buffer ricezione sci1
  #endif

  // seriale 1
  #ifdef USE_COM_1  // COM INVERTER USART2 
    uchar   rx_buf_com1[RX_BUF_LEN_1];        // buffer ricezione sci1
    uchar   tx_buf_com1[TX_BUF_LEN_1];        // buffer ricezione sci1
  #endif

  // seriale 2
  #ifdef USE_COM_2
    uchar   rx_buf_com2[RX_BUF_LEN_2];        // buffer ricezione sci1
    uchar   tx_buf_com2[TX_BUF_LEN_2];        // buffer ricezione sci1
  #endif

  // SPI 2
  #ifdef USE_COM_3_SPI2
    uchar   rx_buf_com3[BUF_LEN_3];     	   // buffer ricezione
    uchar   tx_buf_com3[BUF_LEN_3];       	 // buffer trasmissione
  #endif

  
  uchar	local_address = 0; // inizializzo a 0 e poi alla lettura dip assegno addr.
  // qui sotto definisco struttura e buffer per il vettore degli indici vars da scrivere
  unsigned long  buff_write[NUM_MAX_VAR_TO_WRITE];        // buffer ricezione sci1

  // per debug
  buff_app index_var_to_write;
  
  unsigned long timeout_ugrade;
//  char strapp[MAX_DIM_STRAPP];
  //char dim_record[3];
  //dimensione del frame da spedire
  unsigned long dimensione_frame = 0;
  //appoggio della riga letta da file
  		
  //dimensione del record attuale da leggere
  unsigned short num_byte_record = 0;
  //byte effettivamente letti
  unsigned int num_byte_rd = 0;
  
  unsigned char upgrade_progress  =0;
  
  // MB 151103 aggiungo per gestione buffer tipo 4
  buff_type buff_type_4;
  
 // buff_data_payload buffer_story_allarm[SIZE_ALARM_LIST];// buffe rdi appoggio 
  
  //SS 160118 sono  valori del brr per i baud 9600 e 38400 rispettivamente  
  //unsigned short uart2_brr[] ={0x3a9,0xea6};
  unsigned short uart2_brr[] ={0xea6, 0x3a9};
  unsigned char actual_id_baud = ID_BAUD_9600;
  unsigned char count_error_comunication = 0;
  unsigned char error_autoreset=0;
  
#else
  // ------------------------------------------------------------------
  //                            E X T E R N
  // ------------------------------------------------------------------

  
  extern unsigned char upgrade_progress;
 #ifdef USE_COM_4
    extern per_com com[5];
  #elif defined USE_COM_3
   extern  per_com com[4];
  #elif defined USE_COM_2
    extern per_com com[3];
  #elif defined USE_COM_1
    extern per_com com[2];
  #else
    extern per_com com[1];
  #endif
  extern buff_app index_var_to_write;
  
  // MB 151103 aggiungo per gestione buffer tipo 4 
  extern buff_type buff_type_4; 
  
  extern unsigned char count_error_comunication;
  extern unsigned char error_autoreset;
  
#endif

// ------------------------------------------------------------------
//                            P R O T O T Y P E S
// ------------------------------------------------------------------
//
void Put_and_ck(uchar _com, uchar car);
uchar GetByte(uchar _com);
uchar BytesInReceiveBuffer(uchar _com);
uchar BytesInTxBuffer(uchar _com);
void Com_Init(void);
uchar Get_and_ck(uchar _com);
void Sveglia_tx(uchar _com);
void Rx_decode(uchar _com);
void PutByte(uchar _com, uchar _ch);
void PutString(uchar _com, uchar *_str);
void Put_Hex(uchar _com, ulong _val, uchar _len);
void PutLong(uchar _com, long _val, uchar _len);
//void PutMODBUS_DATA(uchar _com);



void RxSer0(void);
void TxSer0(void);
void TxEndSer0(void);

void RxSer1(void);
void TxSer1(void);
void TxEndSer1(void);

void RxSer2(void);
void TxSer2(void);
void TxEndSer2(void);
void TxSer2_Complete(void);

void Setting_Baud_Rate(unsigned char setpoint_baud);






