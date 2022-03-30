#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"
#include "tim.h"
#include "i2c.h"


 
extern u8 TimeDisplay;
u8 i;
u8 dat;

int main(void)
{  	
	SysTick_Config1(SystemCoreClock/1000);
  OLED_Init();
 
  i2c_init();
	
	dat=m24c02_read(0xff);
	delay_ms(10);
	m24c02_write(0xff,++dat);
	delay_ms(10);
	
	while(1)
	{
			OLED_DisPlay_8x16Char(40,0,25);
			OLED_DisPlay_8x16Char(48,0,2);
			OLED_DisPlay_8x16Char(56,0,19);		

			OLED_P16x16Str(56+16,0," ");

			OLED_DisPlay_8x16Char(72+8,0,20);
			OLED_DisPlay_8x16Char(88,0,21);
			OLED_DisPlay_8x16Char(96,0,29);
			OLED_DisPlay_8x16Char(104,0,31);	
			
 
			OLED_DisPlay_8x16Char(0+8,2,17);
			OLED_DisPlay_8x16Char(0+16,2,36);
			OLED_DisPlay_8x16Char(24,2,2);
			OLED_DisPlay_8x16Char(32,2,4);
			OLED_DisPlay_8x16Char(40,2,19);
			OLED_DisPlay_8x16Char(48 ,2,0);
			OLED_DisPlay_8x16Char(56,2,2);
		
			OLED_DisPlay_8x16Char(72 ,2,34);
			OLED_DisPlay_8x16Char(80,2,94);
			OLED_DisPlay_8x16Char(88 ,2,39);
			

 
			OLED_DisPlay_8x16Char(0,4,17);
			OLED_DisPlay_8x16Char(8,4,20);
			OLED_DisPlay_8x16Char(8+8,4,20);
			OLED_DisPlay_8x16Char(16+8,4,34);
			OLED_DisPlay_8x16Char(24+8,4,10);
			OLED_DisPlay_8x16Char(40,4,0);
			OLED_DisPlay_8x16Char(40+8,4,72);
			OLED_DisPlay_8x16Char(48+8,4,22);
			OLED_DisPlay_8x16Char(56+8,4,22);			
			OLED_DisPlay_8x16Char(64+8,4,91);		 
			OLED_DisPlay_8x16Char(72+8,4,38);
			OLED_DisPlay_8x16Char(80+8,4,17);
			OLED_DisPlay_8x16Char(88+8,4,28);	
			OLED_DisPlay_8x16Char(96+8,4,10);	
      OLED_Print_8x16_2(104+8,4,dat);			
	}
}
 

 
 
