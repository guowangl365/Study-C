#include "key.h"
#include "delay.h"
 



void key_Config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
	//PA0-BUTTON1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);

	/* Configure EXTI0 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
 	EXTI_Init(&EXTI_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);


	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	/////////////////////////
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);

	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

uint8 key1_sum=0;
uint8 key2_sum=0;
uint8 key3_sum=0;
uint8 key4_sum=0; 
uint8 button=0;
void key_read(void)
{
	 if(KEY1==0)
	 {
		 //¶Ì°´
		 if(++key1_sum==1)
		 {
       button=1;
		 }
	 }
	 else
	 {
		 key1_sum=0;
	 }
	 
 
	 if(KEY2==0)
	 {
		 //¶Ì°´
		 if(++key2_sum==1)
		 {
 	     button=2;
		 } 
	 }
	 else
	 {
		 key2_sum=0;
	 }
 
 
		 if(KEY3==0)
	   {
		 //¶Ì°´
			 if(++key3_sum==1)
			 {
				 button=3;
			 } 
			 else
			{
				key3_sum=0;
			}
    }
	 
		if(KEY4==0)
		{
		 if(++key4_sum==1)
		 {
			 button=4;
		 }
		}
		else
		{
		 key4_sum=0;
		}
	 
}
 


