#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "lcd1602.h"

 int main(void)
 {	
	 
	u8 str[] = "Welcome HG";
	NVIC_Configuration();
	delay_init();      //延时函数初始化	
	GPIO_Configuration();     
	LCD1602_Init();

	while(1)
	{

		LCD1602_Show_Str(5, 0, str);
    LCD1602_Show_Str(0, 1, "Computer Depart");

	}

 }

