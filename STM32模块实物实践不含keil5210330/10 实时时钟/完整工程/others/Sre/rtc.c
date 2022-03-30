#include "rtc.h"
#include "oled.h"
#include "User_Oled.h"
#include "misc.h"

u8 TimeDisplay=1;
extern u16 hour,minute,second;
uint32_t THH = 0, TMM = 0, TSS = 0;

void rtc_mode_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSICmd(ENABLE);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

	RTC_SetCounter(3600*hour+60*minute+second); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
  RTC_WaitForLastTask();	
  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
  RTC_WaitForLastTask();
}

void rtc_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void RTC_Config(void)
{
	rtc_mode_Config();
	rtc_NVIC_Configuration();
}
void Time_Display(uint32_t TimeVar)
{   
  /* Compute  hours */
  THH = TimeVar / 3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600) / 60;
  /* Compute seconds */
  TSS = (TimeVar % 3600) % 60;

  OLED_Print_8x16_2(40,4,THH);
  OLED_P8x16Str(48+8,4,":");
  OLED_Print_8x16_2(56+8,4,TMM);
  OLED_P8x16Str(64+8+8,4,":");
  OLED_Print_8x16_2(72+8+8,4,TSS);  
}

void RTC_IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    if (RTC_GetCounter() == 0x0001517F)
    {
       RTC_SetCounter(0x0);
       RTC_WaitForLastTask();
    }

    TimeDisplay = 1; 
    RTC_WaitForLastTask();    
  }
	RTC_ClearITPendingBit(RTC_IT_SEC);
}
