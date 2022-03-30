#ifndef __KEY_H
#define __KEY_H



#include "stm32f10x.h"
#include "stm32f10x_exti.h"

#define KEY1			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define KEY2			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define KEY3			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define KEY4			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)

void key_Config(void);
void key_read(void);








#endif
