

#define __DECLARE_TIME_VARS
  #include "time.h"
#undef __DECLARE_TIME_VARS

// ----------------------------------------------------------------------------
//								GESTIONE TEMPO
/******************************************************************/
// Base 1ms
/******************************************************************/
//
void ResetOrol(unsigned long *_orol)
{

	*_orol = main_time;

}

unsigned long GetTime(unsigned long *_orol)
{
	 unsigned long  app;

	app = main_time;

	return app - *_orol;
}
/******************************************************************/
// Base 100us
/******************************************************************/
//
void Reset100us(unsigned long *_orol)
{
	*_orol = main_time_100us;

}

unsigned long Get100us(unsigned long *_orol)
{
	unsigned long app;

	app = main_time_100us;

	return app - *_orol;
}
/******************************************************************/
// Base 1s
/******************************************************************/
//
void ResetSec(unsigned long *_orol)
{

	*_orol = main_sec;

}

unsigned long GetSec(unsigned long *_orol)
{
	unsigned long app;

	app = main_sec;

	return app - *_orol;
}



