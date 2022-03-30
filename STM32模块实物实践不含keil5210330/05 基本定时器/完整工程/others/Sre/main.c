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
uint8 led=0;

int main(void)
{  	
	SysTick_Config1(SystemCoreClock/1000);
  OLED_Init();
  LED_Config();
 
	TIM3_Config();
	
	while(1)
	{
		//50ms
		if(led_flag==1)
		{
			led++;
			led_flag=0;
		}
		
		//¼ä¸ô1sÁÁµÆ
		if(led==0)    //1ÁÁ
		{
			LED1=0;
			LED6=1;
			led_num=1;
		}
		
		if(led==20)    //2ÁÁ1Ãð
		{
			LED2=0;
			LED1=1;
			led_num=2;
		}
		
		if(led==40)    //3ÁÁ2Ãð
		{
			LED3=0;
			LED2=1;
			led_num=3;
		}
		
		if(led==60)     //4ÁÁ3Ãð
		{
			LED4=0;
			LED3=1;
			led_num=4;
		}
		
		if(led==80)      //5ÁÁ4Ãð
		{
			LED5=0;
			LED4=1;
			led_num=5;
		}
		
		if(led==100)     //6ÁÁ5Ãð
		{
			LED6=0;
			LED5=1;			
			led_num=6;
		}
    if(led==120)     
		{
			led=0;
			led_num=1;
		}			
 
		
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
		

		OLED_DisPlay_8x16Char(0+8,2,35);
		OLED_DisPlay_8x16Char(0+8+8,2,53);
		OLED_DisPlay_8x16Char(0+16+8,2,53);
	

		OLED_DisPlay_8x16Char(48 ,2,36);
		OLED_DisPlay_8x16Char(56 ,2,56);
		OLED_DisPlay_8x16Char(64  ,2,53);

		OLED_DisPlay_8x16Char(88+8-16,2,28);
		OLED_DisPlay_8x16Char(96+8-16,2,21);
		OLED_DisPlay_8x16Char(104+8-16,2,20);
		OLED_DisPlay_8x16Char(112+8-16,2,67);
		
		OLED_DisPlay_8x16Char(0,4,92);
		OLED_DisPlay_8x16Char(0+8,4,92);
		OLED_DisPlay_8x16Char(0+16,4,28);
		OLED_DisPlay_8x16Char(0+24,4,21);
		OLED_DisPlay_8x16Char(0+32,4,20);
		OLED_DisPlay_8x16Char(0+48,4,31);
		OLED_DisPlay_8x16Char(0+56,4,30);	
		OLED_DisPlay_8x16Char(0+64,4,10);	
		OLED_DisPlay_8x16Char(0+72,4,28);
		OLED_DisPlay_8x16Char(0+80,4,20);
		OLED_DisPlay_8x16Char(88,4,led_num);
	}
}
 

 
 
