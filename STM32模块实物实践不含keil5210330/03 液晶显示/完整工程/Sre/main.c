#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"

 
int main(void)
{
 	SysTick_Config1(SystemCoreClock/1000);
 
  OLED_Init();
//  LED_Config();
	
	while(1)
	{
		
    OLED_P8x16Str(0,0,"Welcome to HBEU");
		OLED_P16x16Str(0+6,2,"湖工计算机学院");
		OLED_P8x16Str(0,4,"  www.hbeu.cn");		
		OLED_P8x16Str(0,6,"Computer Depart");		
		
//单个字符显示如下：		
//		OLED_DisPlay_8x16Char(0,0,'W');
//    OLED_DisPlay_8x16Char(0+16-8,0,53);
//		 OLED_DisPlay_8x16Char(0+16-8,0,'e'-48);
//    OLED_DisPlay_8x16Char(0+24-8,0,60);
//    OLED_DisPlay_8x16Char(32-8,0,51);
//    OLED_DisPlay_8x16Char(40-8,0,63);
//    OLED_DisPlay_8x16Char(48-8,0,61);
//    OLED_DisPlay_8x16Char(56-8,0,53);

//    OLED_DisPlay_8x16Char(72-8,0,68);
//    OLED_DisPlay_8x16Char(80-8,0,63);
//		
//    OLED_DisPlay_8x16Char(88,0,0x77);
//    OLED_DisPlay_8x16Char(96,0,0x71);
//    OLED_DisPlay_8x16Char(96+8,0,0x74);
//    OLED_DisPlay_8x16Char(96+16,0,0x84);		

		
//				OLED_DisPlay_8x16Char(0,0,'W');

//		 OLED_DisPlay_8x16Char(0+16-8,0,'e');
//    OLED_DisPlay_8x16Char(0+24-8,0,'l');
//    OLED_DisPlay_8x16Char(32-8,0,'c');
//    OLED_DisPlay_8x16Char(40-8,0,'o');
//    OLED_DisPlay_8x16Char(48-8,0,'m');
//    OLED_DisPlay_8x16Char(56-8,0,'e');

//    OLED_DisPlay_8x16Char(72-8,0,'t');
//    OLED_DisPlay_8x16Char(80-8,0,'o');
//		
//    OLED_DisPlay_8x16Char(88,0,'H');
//    OLED_DisPlay_8x16Char(96,0,'B');
//    OLED_DisPlay_8x16Char(96+8,0,'E');
//    OLED_DisPlay_8x16Char(96+16,0,'U');	

		
//    OLED_DisPlay_8x16Char(0+16-8,4,71);
//    OLED_DisPlay_8x16Char(0+24-8,4,71);
//    OLED_DisPlay_8x16Char(32-8,4,71);
//    OLED_DisPlay_8x16Char(32,4,93);
//    OLED_DisPlay_8x16Char(40,4,56);
//    OLED_DisPlay_8x16Char(48,4,50);
//    OLED_DisPlay_8x16Char(56,4,53);
//    OLED_DisPlay_8x16Char(64,4,69);
//		OLED_DisPlay_8x16Char(72,4,93);
//		OLED_DisPlay_8x16Char(80,4,51);
//		OLED_DisPlay_8x16Char(88,4,62);
		
		
//    OLED_DisPlay_8x16Char(0+16-8,4,'w');
//    OLED_DisPlay_8x16Char(0+24-8,4,'w');
//    OLED_DisPlay_8x16Char(32-8,4,'w');
//    OLED_DisPlay_8x16Char(32,4,'.');
//    OLED_DisPlay_8x16Char(40,4,'h');
//    OLED_DisPlay_8x16Char(48,4,'b');
//    OLED_DisPlay_8x16Char(56,4,'e');
//    OLED_DisPlay_8x16Char(64,4,'u');
//		OLED_DisPlay_8x16Char(72,4,'.');
//		OLED_DisPlay_8x16Char(80,4,'c');
//		OLED_DisPlay_8x16Char(88,4,'n');		
		
		
				
	}
}
 

 
 
