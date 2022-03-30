#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"
#include "tim.h"
#include "adc.h"

 
u16 ADC_Value=0;
float ADC_Value1;
u8 ADC_Value2=0;
extern u8 adc_flag;

int main(void)
{  	
	SysTick_Config1(SystemCoreClock/1000);
  OLED_Init();
  LED_Config();
 
	ADC_Config();
	TIM3_Config();	
	
	while(1)
	{

		OLED_DisPlay_8x16Char(48,0,17);
		OLED_DisPlay_8x16Char(56,0,20);		
		OLED_DisPlay_8x16Char(64,0,19);	
		OLED_P16x16Str(64+16,0," ");

		
		OLED_DisPlay_8x16Char(64+8+16,0,20);
		OLED_DisPlay_8x16Char(72+8+16,0,21);
		OLED_DisPlay_8x16Char(80+8+16,0,29);
		OLED_DisPlay_8x16Char(88+8+16,0,31);	
		
		OLED_DisPlay_8x16Char(0,2,32);
		OLED_DisPlay_8x16Char(0+8,2,17);
		OLED_DisPlay_8x16Char(0+8+8,2,1);
		OLED_DisPlay_8x16Char(0+16+8,2,92);	
		OLED_DisPlay_8x16Char(24+8,2,17);
		OLED_DisPlay_8x16Char(32+8,2,20);
		OLED_DisPlay_8x16Char(40+8,2,19);

		OLED_DisPlay_8x16Char(56+8,2,51);
		OLED_DisPlay_8x16Char(56+8+8,2,56);
		OLED_DisPlay_8x16Char(64+8+8,2,49);
		OLED_DisPlay_8x16Char(72+8+8,2,62);
		OLED_DisPlay_8x16Char(80+8+8,2,62);
		OLED_DisPlay_8x16Char(88+8+8,2,53);
		OLED_DisPlay_8x16Char(96+8+8,2,60);
		OLED_DisPlay_8x16Char(112+8,2,1);
		
    if(adc_flag==1)
    {
			ADC_Value=adc_read(ADC_Channel_1);
			ADC_Value1=(float)(ADC_Value*3.3/0xfff);
			ADC_Value=ADC_Value1;       //小数点前的数字
			ADC_Value1=ADC_Value1-ADC_Value; //小数点后几位
			ADC_Value1=ADC_Value1*100;       //小数点后两位
			ADC_Value2=(u16)(ADC_Value1*1000)%10; //小数点后第三位 
			adc_flag=0;
		}
		
		OLED_DisPlay_8x16Char(0,4,17);
		OLED_DisPlay_8x16Char(0+8,4,20);
		OLED_DisPlay_8x16Char(0+16,4,19);

		OLED_DisPlay_8x16Char(0+32,4,38);
		OLED_DisPlay_8x16Char(0+48-8,4,49);
		OLED_DisPlay_8x16Char(0+56-8,4,60);	
		OLED_DisPlay_8x16Char(0+64-8,4,69);	
		OLED_DisPlay_8x16Char(0+72-8,4,53);
		OLED_DisPlay_8x16Char(0+80-8,4,10);
		OLED_DisPlay_8x16Char(0+88-8,4,ADC_Value);
		OLED_DisPlay_8x16Char(0+96-8,4,93);
		OLED_Print_8x16_2(88+8,4,ADC_Value1);
		OLED_DisPlay_8x16Char(96+16,4,ADC_Value2);
		OLED_DisPlay_8x16Char(96+16+8,4,38);
	}
}
 

 
 
