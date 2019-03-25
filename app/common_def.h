
#include "stm32f10x_conf.h"

#define VERSIONE_FIRMWARE				0x0001
#define VERSIONE_FIRMWARE_AUX		0x0081
		
#define VER_FIRM_ATT (VERSIONE_FIRMWARE * 0x10000 | VERSIONE_FIRMWARE_AUX)

// -----------------------------------------------------------------------------
// processor type


#ifndef COMMON_DEF_H
	#define COMMON_DEF_H

	
	


  #define false     0
  #define true      1
	



	
	
	
	// --------------------------------------------------------------------------- 
	// Gestione pressione tasti
	#define PB_OSR			0x0f // xxx modificato a 7f per mancate prese tasti 020703
	#define PB_OSF			0xf0
	#define PB_PRESSED	0xff
	#define PB_OFF			0x00
	
	
	//----------------------------- D A T A  T Y P E S --------------------------- 
	#define LONG_MAX		0xffffffff
	#define SHRT_MAX		0xffff
	

	#define uchar unsigned char
	#define ushort unsigned short
	#define ulong unsigned long
	
	typedef unsigned char       Uchar;
	typedef float               Float16;
	
	typedef unsigned char       Uint8;
	typedef unsigned int        Uint16;
	typedef unsigned long int   Uint32;
	
	typedef signed char         Int8;
	typedef int                 Int16;
	typedef long int            Int32;
	
	typedef unsigned char       Bool;
	typedef unsigned char       Byte;
	typedef unsigned int        Word;
	typedef unsigned long int   DWord;
	
	typedef union
	{
  Uint32 dw; // l changed in dw (double word) because l is used for signed long...
  Uint16 w[2];
  Uint8  b[4];
	} Union32;

	typedef union
	{
  Uint16 w;
  Uint8  b[2];
	} Union16;

	typedef union
	{
  uchar byte_1;
  struct
  {
    unsigned char Bit0:1;
    unsigned char Bit1:1;
    unsigned char Bit2:1;
    unsigned char Bit3:1;
    unsigned char Bit4:1;
    unsigned char Bit5:1;
    unsigned char Bit6:1;
    unsigned char Bit7:1;
  };
	} _bit_union;

	typedef union
	{
  ushort word_1;
  struct
  {
    unsigned char Bit0:1;
    unsigned char Bit1:1;
    unsigned char Bit2:1;
    unsigned char Bit3:1;
    unsigned char Bit4:1;
    unsigned char Bit5:1;
    unsigned char Bit6:1;
    unsigned char Bit7:1;

    unsigned char Bit8:1;
    unsigned char Bit9:1;
    unsigned char BitA:1;
    unsigned char BitB:1;
    unsigned char BitC:1;
    unsigned char BitD:1;
    unsigned char BitE:1;
    unsigned char BitF:1;
  };
	} _word_union;



	// macros
	#define SETBIT(x, y) x |= 0x01 << y
	#define CLRBIT(x, y) x &= ~(0x01 << y)
	#define INVBIT(x, y) x ^= 0x01 << y
	#define TESTBIT(x, y) (x & (0x01 << y))
	
	typedef struct
	{
		//float dState; // Last position input
		float iState; // Integrator state
		float iMax, iMin;// Maximum and minimum allowable integrator state
	
		float	iGain, // integral gain
		pGain/*, // proportional gain
		dGain*/; // derivative gain
		
		float result;
		float actual_speed;
	} SPid;

#endif
