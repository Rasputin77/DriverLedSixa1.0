#include "common_def.h"

#ifndef TIME_H
  #define TIME_H

 // IN QUESTA PORZIONE DI CODICE TUTTE LE DEFINE
	

	

#endif 
 
 

#ifdef __DECLARE_TIME_VARS

  // vars
  unsigned long tick100us=0;
  unsigned long main_time 				= 0;
  unsigned long main_time_100us 	= 0;
  unsigned long main_sec 				= 0;
  unsigned long timing_1ms       = 0;
  unsigned long main_min					=	0;
 

  unsigned long	timing_100us	= 10;
  unsigned long	timing_10ms		= 10;
  unsigned long	timing_100ms	= 100;
#else

  extern unsigned long main_time;
  extern unsigned long main_time_100us;
  extern unsigned long main_sec;
  extern unsigned long timing_1ms;
  extern unsigned long main_min;

  extern unsigned long  long_time;

  extern unsigned long	timing_100us;
  extern unsigned long	timing_10ms;
  extern unsigned long	timing_100ms;
  extern unsigned long tick100us;
#endif
  
  
//------------------------------------------------------------------------------
//
//---------------------------- prototypes---------------------------------------
//ms
void ResetOrol(unsigned long *_orol);
unsigned long GetTime(unsigned long *_orol);
//100us
void Reset100us(unsigned long *_orol);
unsigned long Get100us(unsigned long *_orol);
//Secondi
void ResetSec(unsigned long *_orol);
unsigned longGetSec(unsigned long *_orol);


