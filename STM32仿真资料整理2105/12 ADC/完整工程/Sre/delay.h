#ifndef __DELAY_H
#define __DELAY_H 	

#include "stm32f10x.h"
#include "core_cm3.h"
#include "sys.h"


uint32_t SysTick_Config1(uint32_t ticks);
void delay_ms(u32 ntime);
 
#endif
