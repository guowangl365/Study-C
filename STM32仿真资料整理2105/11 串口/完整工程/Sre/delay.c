#include "delay.h"
 

u32 TimingDelay=0;




void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	//SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
     								   
 //void delay_ms(u32 ntime)
 //{
//	 TimingDelay=ntime;
//	 while(TimingDelay!=0);
 //}
 
 void delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}
