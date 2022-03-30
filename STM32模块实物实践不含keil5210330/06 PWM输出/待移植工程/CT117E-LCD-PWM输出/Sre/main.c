/*******************************************************************************  
* 文件名称：定时器PWM输出实验
* 实验目的：掌握STM32定时器功能和配置方法
* 程序说明：配置TIM2 CH2、CH3为PWM输出模式，CH2输出1KHZ，占空比50%信号，
*           CH3输出1KHz，占空比70%信号
* 日期版本：2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
//#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
uint16_t Channel2Pulse = 0, Channel3Pulse = 0;
/* Private function prototypes -----------------------------------------------*/
void Delay_Ms(uint32_t nTime);
void NVIC_Configuration(void);
void TIM_Config(uint16_t Channel2Pulse, uint16_t Channel3Pulse);
void PWM_IO_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{   	
    SysTick_Config(SystemCoreClock/1000);  //1ms中断一次

	PWM_IO_Config();
	
	TIM_Config(998/2,998*7/10);
	
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
	LCD_DisplayStringLine(Line3,"    TIM2 PWM MODE   ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);
	
	LCD_DisplayStringLine(Line6,"PA1-PWMVALUE:50%    ");
	LCD_DisplayStringLine(Line8,"PA2-PWMVALUE:70%    ");
		
    while(1){			
		;
	}
}

/**
  * @说明     通用定时器TIM2配置函数,PWM输出工作模式
  * @参数     none
  * @返回值   None
  */
void TIM_Config(uint16_t Channel2Pulse, uint16_t Channel3Pulse)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;  //1KHz
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM2预分频设置:1MHZ,APB1分频系数2，输入到TIM3时钟为36MHzx2 = 72MHz  


	/* Channel 2 and 3 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	//使能TIM2定时计数器
	TIM_Cmd(TIM2, ENABLE);
	//使能TIM2 PWM输出模式
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}

/**
  * @说明     PWM输出模式 PA1(TIM2-CH2)、PA2(TIM2-CH3)引脚配置
  * @参数     None 
  * @返回值   None
  */
void PWM_IO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
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
