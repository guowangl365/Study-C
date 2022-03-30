#include "tim.h"
#include "led.h"
#include "misc.h"



u16 CH2_Value=0;
u16 CH2_Duty=0;
u16 CH3_Value=0;
u16 CH3_Duty=0;
extern uint8 pulse1,pulse2;


void TIM2_CH2_Config(u16 ch2_fre,u16 ch2_duty)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
		
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = 0x0;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure);

	CH2_Value=1000000/ch2_fre; 
	CH2_Duty=CH2_Value*ch2_duty/100;
	pulse1=ch2_duty;
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CH2_Value;
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
			
	TIM_SetCompare2(TIM2,0x0);
	TIM_Cmd( TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
}
 
void TIM2_CH3_Config(u16 ch3_fre,u16 ch3_duty)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
		
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = 0x0;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure);

	CH3_Value=1000000/ch3_fre; 
	CH3_Duty=CH3_Value*ch3_duty/100;
	pulse2=ch3_duty;
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CH3_Value;
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
			
	TIM_SetCompare3(TIM2,0x0);
	TIM_Cmd( TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
}


u8 situation1=0;
u8 situation2=0;

void TIM2_IRQHandler(void)
{
  u16 capture;

	if(TIM_GetITStatus(TIM2, TIM_IT_CC2) == 1)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
		capture = TIM_GetCapture2(TIM2);
		if(situation1==0)
		{
			TIM_SetCompare2(TIM2,capture + CH2_Duty);
			situation1=1;
		}
		else
		{
			TIM_SetCompare2(TIM2,capture + CH2_Value - CH2_Duty);
			situation1=0;
		}
	}
	if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == 1)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
		capture = TIM_GetCapture3(TIM2);
		if(situation2==0)
		{
			TIM_SetCompare3(TIM2,capture + CH3_Duty);
			situation2=1;
		}
		else
		{
			TIM_SetCompare3(TIM2,capture + CH3_Value - CH3_Duty);
			situation2=0;
		}
	}
}
