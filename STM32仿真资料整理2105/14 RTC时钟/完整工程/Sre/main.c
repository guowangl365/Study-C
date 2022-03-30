#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "lcd1602.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define HH 10  //时
#define MM 59  //分
#define SS 55  //秒

u32 THH = 0, TMM = 0, TSS = 0;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//uint32_t TimingDelay = 0;
uint32_t TimeDisplay = 0;

/* Private function prototypes -----------------------------------------------*/
//void Delay_Ms(uint32_t nTime);
void RTC_Configuration(void);
void NVIC_Configuration(void);
void Time_Display(u32 TimeVar);
void BuzzerGPIO_Configuration(void);

int main(void)
{
 	SysTick_Config1(SystemCoreClock/1000);
 GPIO_Configuration();
  LCD1602_Init();
//  LED_Config();
//	  LCD1602_Show_Str(0,0,"    RTC DEMO    ");
	//OLED_P16x16Str(0+8,2,"湖工计算机学院");
		LCD1602_Show_Str(0,0,"RTC_Calendr_Test");		
	//OLED_P8x16Str(0,6,"Computer Depart");		
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);

	BuzzerGPIO_Configuration();
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//先关掉蜂鸣器
	
	RTC_Configuration();
	NVIC_Configuration();
	
	while(1)
	{
				if(TimeDisplay == 1)
			   {
					Time_Display(RTC_GetCounter());
					TimeDisplay = 0;  //清除标志位
					if((TMM==0)&&(TSS==0))
					{
						GPIO_ResetBits(GPIOB,GPIO_Pin_9);//先关掉蜂鸣器
					}
					if(TSS<10)
					{
						if(TSS%2)  GPIO_SetBits(GPIOB,GPIO_Pin_9);
						else  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
					}
					else  GPIO_SetBits(GPIOB,GPIO_Pin_9);
		      }			
	}
}
 

void BuzzerGPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //Buzzer
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOB, &GPIO_InitStructure);//
}

/**
  * @说明     配置RTC
  * @参数     None
  * @返回值   None
  */
void RTC_Configuration(void)
{	  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
       /* 使能 PWR 和 BKP 时钟 */
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);   /* 允许访问 BKP，备份域 */

  /* Reset Backup Domain */
  BKP_DeInit();  /* 对备份域进行软件复位 */

  /* Enable the LSI OSC */
  RCC_LSICmd(ENABLE); /* 使能低速内部时钟 LSI */
  /* Wait till LSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {}/* 等待 LSI 起振稳定 */
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
        /* 选择 LSI 作为 RTC 外设的时钟*/
  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);  /* 便能 RTC 时钟 */

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro(); /* 等待 RTC 寄存器与 APB1 同步*/

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();/* 等待对 RTC 的写操作完成*/

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);/* 使能 RTC 秒中断 */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();/* 等待对 RTC 的写操作完成 */

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(39999);/* RTC 周期 = RTCCLK/RTC_PR = (40 KHz)/(39999+1) */
/* 设置 RTC 时钟分频: 使 RTC 定时周期为 1 秒，经测试不准，可以通过程序校准*/

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask(); /* 等待对 RTC 的写操作完成 */


	RTC_SetCounter(HH*3600+MM*60+SS);//  设置RTC计数器，总秒数
	RTC_WaitForLastTask(); /* 等待对 RTC 的写操作完成 */
}

/**
  * @说明     显示当前时间
  * @参数     TimeVar:RTC Counter值
  * @返回值   None
  */

uint8_t text[20];
void Time_Display(u32 TimeVar)
{
	//u32 THH = 0, TMM = 0, TSS = 0;

	/* Compute  hours */
	THH = TimeVar / 3600;
	/* Compute minutes */
	TMM = (TimeVar % 3600) / 60;
	/* Compute seconds */
	TSS = (TimeVar % 3600) % 60;

	sprintf(text,"Time: %0.2d:%0.2d:%0.2d",THH, TMM, TSS);
//	LCD_DisplayStringLine(Line7,text);
	LCD1602_Show_Str(0,2,text);	
}

/**
  * @说明     配置中断向量控制器
  * @参数     None
  * @返回值   None
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

 
 
