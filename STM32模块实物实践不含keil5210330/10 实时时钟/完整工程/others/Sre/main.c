#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"
#include "rtc.h"
#include "buzzer.h"


 
u16 hour=10,minute=59,second=55;
extern u8 TimeDisplay;
u8 i;

int main(void)
{  	
	SysTick_Config1(SystemCoreClock/1000);
  OLED_Init();
 
  RTC_Config();
	buzzer_Init();
	
	while(1)
	{
			OLED_DisPlay_8x16Char(40,0,34);
			OLED_DisPlay_8x16Char(48,0,36);
			OLED_DisPlay_8x16Char(56,0,19);		

			OLED_P16x16Str(56+16,0," ");

			OLED_DisPlay_8x16Char(72+8,0,20);
			OLED_DisPlay_8x16Char(88,0,21);
			OLED_DisPlay_8x16Char(96,0,29);
			OLED_DisPlay_8x16Char(104,0,31);	
			
 
			OLED_DisPlay_8x16Char(0,2,34);
			OLED_DisPlay_8x16Char(0+8,2,36);
			OLED_DisPlay_8x16Char(0+16,2,19);

			OLED_DisPlay_8x16Char(24+8,2,19); 
			OLED_DisPlay_8x16Char(40,2,49);
			OLED_DisPlay_8x16Char(48 ,2,60);
			OLED_DisPlay_8x16Char(56,2,53);
			OLED_DisPlay_8x16Char(64 ,2,62);
			OLED_DisPlay_8x16Char(72 ,2,52);
			OLED_DisPlay_8x16Char(80,2,49);
			OLED_DisPlay_8x16Char(88 ,2,66);
			
			OLED_DisPlay_8x16Char(104-8,2,36);
			OLED_DisPlay_8x16Char(112-8,2,53);
			OLED_DisPlay_8x16Char(120-8,2,67);
			OLED_DisPlay_8x16Char(128-8,2,68);
 
			OLED_DisPlay_8x16Char(0,4,36);
			OLED_DisPlay_8x16Char(8,4,57);
			OLED_DisPlay_8x16Char(8+8,4,61);
			OLED_DisPlay_8x16Char(16+8,4,53);
			OLED_DisPlay_8x16Char(24+8,4,10);
 
		  if(TimeDisplay == 1)
		  {
			  Time_Display(RTC_GetCounter());
			  TimeDisplay = 0;
		  }	
      
			if(RTC_GetCounter()%3600==0)
			{
				for(i=0;i<=4;i++)
				{
					 GPIO_ResetBits(GPIOB, GPIO_Pin_9);
					 delay_ms(500);
					 GPIO_SetBits(GPIOB, GPIO_Pin_9);
					 delay_ms(500);					
				}
			}
	}
}
 

 
 
