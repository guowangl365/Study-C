#ifndef __RTC_H
#define __RTC_H



#include "stm32f10x.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rtc.h"


void RTC_Config(void);
void Time_Display(uint32_t TimeVar);





#endif
