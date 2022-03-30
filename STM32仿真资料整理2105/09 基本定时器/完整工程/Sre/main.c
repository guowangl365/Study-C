#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "lcd1602.h"


//uint32_t TimingDelay = 0; //在delay.c中已定义，且在main函数中没有用到
extern uint8_t leds;
unsigned int gpc=0;

void NVIC_Configuration(void);
void TIM_Config(void);
void LED_Init(void);

int main(void)
{
	uint8_t  string[20]; 
 	SysTick_Config(SystemCoreClock/1000);
 
	TIM_Config();
	LED_Init();
	
	GPIO_Configuration();     
	LCD1602_Init();
//  LED_Config();
	LCD1602_Show_Str(0, 0, "TIMER DEMO");
//	  OLED_P8x16Str(0,0," TIMER DEMO ");
//		OLED_P8x16Str(0,2,"See The LEDs!");		
//		OLED_P8x16Str(0,4,"Computer Depart");		
	
	while(1)
	{
		

		
		//LED
		gpc=~(1<<(leds+7));
		GPIO_Write(GPIOC,gpc);
			GPIO_Write(GPIOA,~(1<<(leds+7)));
		
//		GPIO_SetBits(GPIOD,GPIO_Pin_2);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		//LCD
		sprintf(string,"%s%d","--LED ON:LD",leds);
//		LCD_DisplayStringLine(Line6,string);			
		LCD1602_Show_Str(0,4,string);		
	}
}
 
void TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//中断向量配置
	NVIC_Configuration();		
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 50000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//TIM3预分频设置:1MHZ,APB1分频系数2，TIM3时钟为36MHzx2 = 72MHz  
	TIM_PrescalerConfig(TIM3,71, TIM_PSCReloadMode_Immediate);	
	
	//通用定时器TIM3中断配置
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

/**
  * @说明     中断向量配置函数
  * @参数     none
  * @返回值   None
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @说明     LED 相关GPIO引脚工作模式及时钟源配置
  * @参数     None 
  * @返回值   None
  */
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//

    //LED引脚配置，PC08~PC15
    GPIO_InitStructure.GPIO_Pin = LED0 |LED1 | LED2 | LED3 | LED4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //74HC573锁存引脚配置，PD2
    GPIO_InitStructure.GPIO_Pin = LED5 | LED6 | LED7;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

 
 
