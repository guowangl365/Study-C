#ifndef __LED_H
#define __LED_H


#include "stm32f10x.h"
   

#define LED1			PCout(15)
#define LED2			PAout(3)
#define LED3			PAout(4)
#define LED4			PAout(5)
#define LED5			PBout(12)
#define LED6			PBout(13)



void LED_Config(void);

#endif
