/*******************************************************************************  
* 文件名称：定时器基础应用实验
* 实验目的：掌握STM32定时器功能和配置方法
* 程序说明：通过定时器TIM3 50毫秒中断一次,LED每隔1S移动一位
* 日期版本：2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
extern uint8_t leds;
/* Private function prototypes -----------------------------------------------*/
void Delay_Ms(uint32_t nTime);
void NVIC_Configuration(void);
void TIM_Config(void);
void LED_Init(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{   	
	uint8_t  string[20];  //

    SysTick_Config(SystemCoreClock/1000);  //1ms中断一次
	
	TIM_Config();
	LED_Init();
	
	//LCD工作模式配置
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);
    
	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,"     TIMER DEMO     ");
	LCD_DisplayStringLine(Line3,"    See The LEDs!   ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);
		
    while(1){
		//LED
		GPIO_Write(GPIOC,~(1<<(leds+7)));
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		//LCD
		sprintf(string,"%s%d","-- LED ON:LD",leds);
		LCD_DisplayStringLine(Line6,string);			
	}
}

/**
  * @说明     通用定时器TIM3配置函数
  * @参数     none
  * @返回值   None
  */
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    //LED引脚配置，PC08~PC15
    GPIO_InitStructure.GPIO_Pin = LED0 |LED1 | LED2 | LED3 | LED4 | LED5 | LED6\
                                  | LED7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //74HC573锁存引脚配置，PD2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
  * @说明     延时函数
  * @参数     nTime: 延时时间
  * @返回值   None
  */
void Delay_Ms(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}
/******************************************END OF FILE*************************/
