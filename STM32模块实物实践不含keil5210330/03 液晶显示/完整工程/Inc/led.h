#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

//CT117E LED引脚号的定义：
#define LED0    GPIO_Pin_8
#define LED1    GPIO_Pin_9
#define LED2    GPIO_Pin_10
#define LED3    GPIO_Pin_11
#define LED4    GPIO_Pin_12
#define LED5    GPIO_Pin_13
#define LED6    GPIO_Pin_14
#define LED7    GPIO_Pin_15
#define LEDALL	GPIO_Pin_All

//led.c文件的函数申明：
void LED_Init(void);
void LED_Control(uint16_t LED,uint8_t LED_Status);

#endif //根据电路图，定义引脚号以及led.c文件中的函数说明。