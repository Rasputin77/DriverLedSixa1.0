
#include <stdio.h>
#include "math.h"
#include <time.h>
#include "stm32f10x.h"
 //---------------


#ifndef RTC_H
  #define RTC_H

//  static struct skew
//  {
//    char error;
//    unsigned char ticks;
//  } skew;

typedef   struct _RTC_t
   {
     unsigned char month;
     unsigned short year;
     unsigned char wday;
     unsigned char mday;
     unsigned short hour;
     unsigned short min;
     unsigned short sec;
     unsigned char dst;
   }RTC_t;

  

#endif




#ifdef RTC_C

RTC_t ioghy;
  


#else


#endif

void RTCInit(void);
unsigned char rtc_settime (const RTC_t *rtc);
void my_RTC_SetCounter(uint32_t cnt);
unsigned char rtc_gettime (RTC_t *rtc);
uint32_t struct_to_counter( const RTC_t *t );
void counter_to_struct( uint32_t sec, RTC_t *t );
unsigned char adjustDST( RTC_t *t );
unsigned char isDST( const RTC_t *t );