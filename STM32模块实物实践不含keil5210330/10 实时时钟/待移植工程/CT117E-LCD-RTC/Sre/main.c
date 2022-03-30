/*******************************************************************************  
* 文件名称：RTC应用实验
* 实验目的：掌握STM32外设RTC的配置和使用方法
* 程序说明：CT117E竞赛平台无外部低速晶振，因此例程中使用内部低速振荡器LSI作为
*           RTC时钟。
* 日期版本：2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define HH 10  //时
#define MM 59  //分
#define SS 55  //秒
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
uint32_t TimeDisplay = 0;
/* Private function prototypes -----------------------------------------------*/
void Delay_Ms(uint32_t nTime);
void RTC_Configuration(void);
void NVIC_Configuration(void);
void Time_Display(u32 TimeVar);
void GPIO_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{	 int i;
    SysTick_Config(SystemCoreClock/1000);  //1ms中断一次

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

	LCD_DisplayStringLine(Line1,"      RTC DEMO      ");
	LCD_DisplayStringLine(Line3," RTC_Calendar_Test  ");

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_Configuration();

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);
	
	

	RTC_Configuration();
	NVIC_Configuration();
			
    while(1)
			{		if(TimeDisplay == 1)
			    {Time_Display(RTC_GetCounter());
			     TimeDisplay = 0;  //清除标志位
		      }

							
			}
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //Buzzer
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOB, &GPIO_InitStructure);//更改虽有JTAG引脚状态
}

/**
  * @说明     配置RTC
  * @参数     None
  * @返回值   None
  */
void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSICmd(ENABLE);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);

	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	
	RTC_SetCounter(HH*3600+MM*60+SS);
	RTC_WaitForLastTask();
}

/**
  * @说明     显示当前时间
  * @参数     TimeVar:RTC Counter值
  * @返回值   None
  */

uint8_t text[20];
void Time_Display(u32 TimeVar)
{
	u32 THH = 0, TMM = 0, TSS = 0;

	/* Compute  hours */
	THH = TimeVar / 3600;
	/* Compute minutes */
	TMM = (TimeVar % 3600) / 60;
	/* Compute seconds */
	TSS = (TimeVar % 3600) % 60;

	sprintf(text,"Time: %0.2d:%0.2d:%0.2d",THH, TMM, TSS);
	LCD_DisplayStringLine(Line7,text);
}

/**
  * @说明     配置中断向量控制器
  * @参数     None
  * @返回值   None
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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
