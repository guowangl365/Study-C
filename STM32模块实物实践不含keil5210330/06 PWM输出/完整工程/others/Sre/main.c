#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"
#include "tim.h"
 

u8 led_num=0;
extern uint8 led_flag;
uint8 led=0,pulse1,pulse2;

int main(void)
{  	
	SysTick_Config1(SystemCoreClock/1000);
  OLED_Init();
  LED_Config();
 
	TIM2_CH2_Config(999,50);
  TIM2_CH3_Config(999,30);
	
	while(1)
	{
		OLED_DisPlay_8x16Char(32,0,36);
		OLED_DisPlay_8x16Char(40,0,25);
		OLED_DisPlay_8x16Char(48,0,29);
		OLED_DisPlay_8x16Char(56,0,21);		
		OLED_DisPlay_8x16Char(64,0,34);	
		OLED_P16x16Str(64+16,0," ");

		
		OLED_DisPlay_8x16Char(64+8+16,0,20);
		OLED_DisPlay_8x16Char(72+8+16,0,21);
		OLED_DisPlay_8x16Char(80+8+16,0,29);
		OLED_DisPlay_8x16Char(88+8+16,0,31);	
	

		OLED_DisPlay_8x16Char(0 ,2,36);
		OLED_DisPlay_8x16Char(8 ,2,25);
		OLED_DisPlay_8x16Char(16,2,29);
		OLED_DisPlay_8x16Char(24,2,2);
		
		OLED_DisPlay_8x16Char(40,2,32);
		OLED_DisPlay_8x16Char(48,2,39);
		OLED_DisPlay_8x16Char(56,2,29);
		
		OLED_DisPlay_8x16Char(72,2,29);
		OLED_DisPlay_8x16Char(80,2,31);		
		OLED_DisPlay_8x16Char(88,2,20);
		OLED_DisPlay_8x16Char(96,2,21);

		OLED_DisPlay_8x16Char(0,4,32);
		OLED_DisPlay_8x16Char(0+8,4,17);
		OLED_DisPlay_8x16Char(0+16,4,1);
		OLED_DisPlay_8x16Char(0+24,4,92);
		OLED_DisPlay_8x16Char(0+32,4,32);
		OLED_DisPlay_8x16Char(0+40,4,39);
		OLED_DisPlay_8x16Char(0+48,4,29);	
		OLED_DisPlay_8x16Char(0+64-8,4,38);	
		OLED_DisPlay_8x16Char(0+72-8,4,17);
		OLED_DisPlay_8x16Char(0+80-8,4,28);
		OLED_DisPlay_8x16Char(0+88-8,4,37);
		OLED_DisPlay_8x16Char(0+96-8,4,21);
		OLED_DisPlay_8x16Char(8+96-8,4,10);
    OLED_Print_8x16_2(112-8,4,pulse1);
		OLED_DisPlay_8x16Char(120,4,84);

		OLED_DisPlay_8x16Char(0,6,32);
		OLED_DisPlay_8x16Char(0+8,6,17);
		OLED_DisPlay_8x16Char(0+16,6,2);
		OLED_DisPlay_8x16Char(0+24,6,92);
		OLED_DisPlay_8x16Char(0+32,6,32);
		OLED_DisPlay_8x16Char(0+48-8,6,39);
		OLED_DisPlay_8x16Char(0+56-8,6,29);	
		OLED_DisPlay_8x16Char(0+64-8,6,38);	
		OLED_DisPlay_8x16Char(0+72-8,6,17);
		OLED_DisPlay_8x16Char(0+80-8,6,28);
		OLED_DisPlay_8x16Char(0+88-8,6,37);
		OLED_DisPlay_8x16Char(0+96-8,6,21);
		OLED_DisPlay_8x16Char(8+96-8,6,10);
    OLED_Print_8x16_2(112-8,6,pulse2);
		OLED_DisPlay_8x16Char(120,6,84);
	}
}
 

 
 
