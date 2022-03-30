#include "stm32f10x.h"
#include "lcd1602.h"
u32 TimingDelay=0;
void delay_ms(u32 ntime);
 int main(void)
 {	
	
	u8 str[] = "Welcome to HBEU";

	SysTick_Config(SystemCoreClock/1000); 
	GPIO_Configuration();     
	LCD1602_Init();

	while(1)
	{

		LCD1602_Show_Str(0, 0, str);
    LCD1602_Show_Str(0, 1, "Computer Depart");

	}

 }
 void delay_ms(u32 ntime)
 {
	 TimingDelay=ntime;
	 while(TimingDelay!=0);
 }
