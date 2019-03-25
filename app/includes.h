/***************************************************************************
 **
 **    MASTER INCLUDE FILE
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 19125 $
 **
 ***************************************************************************/
#ifndef __INCLUDES_H
#define __INCLUDES_H

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <string.h>

#include    <intrinsics.h>

//#include    "stm32f10x_lib.h"

//#include    "arm_comm.h"
//#include    "drv_hd44780_cnfg.h"
//#include    "drv_hd44780_l.h"
//#include    "drv_hd44780.h"

#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

/* define compiler specific symbols */
#if defined ( __CC_ARM   )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                                       /*!< asm keyword for IAR Compiler          */
  #define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */

#elif defined   (  __GNUC__  )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */

#elif defined   (  __TASKING__  )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler      */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */

#endif

//#define ApplicationAddress    0x8005000
//#define BootloaderAddress    	0x8000000

//tipo di micro utilizzato
//#define HIGH_DENSITY_DEVICE
#define MEDIUM_DENSITY_DEVICE

//tipo si supporto per sapere come impostare gli I/O
//#define EVALUATION_BOARD_GRANDE
//#define EVALUATION_BOARD_PICCOLA
//#define DEDICATED_PCB

/*
#ifdef EVALUATION_BOARD_GRANDE
  #pragma message("*** DEFINED EVALUATION_BOARD_GRANDE ***")
#endif
#ifdef EVALUATION_BOARD_PICCOLA
#pragma message("*** DEFINED EVALUATION_BOARD_PICCOLA ***")
#endif

#ifdef DEDICATED_PCB
#pragma message("*** DEFINED DEDICATED_PCB ***")
#endif
*/
#define ushort unsigned short
#define uchar unsigned char
#define ulong unsigned long
//#define u32 unsigned long

typedef  void (*pFunction)(void);

//typedef u32 dword;

#endif /* __INCLUDES_H */
