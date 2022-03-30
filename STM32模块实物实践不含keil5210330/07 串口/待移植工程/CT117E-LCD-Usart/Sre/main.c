/*******************************************************************************  
* 文件名称：USART接收实验
* 实验目的：掌握STM32 USART的操作与配置方法
* 程序说明：1.通过串口调试工具显示连接PC机与串口调试软件，将波特率设定为19200
*           2.发送字符串"asdasdad"+x,在LCD第7行显示asdasdad,以'x'位结束标志
* 日期版本：2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
uint8_t USART_RXBUF[20];
extern uint8_t RXOVER;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
void Delay_Ms(uint32_t nTime);
void USART_Config(void);
void USART_SendString(int8_t *str);
/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{	
	uint8_t i;
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

	LCD_DisplayStringLine(Line1,"      USART DEMO      ");
	LCD_DisplayStringLine(Line3,"   Receive & Display  ");


	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	USART_Config();
	LCD_DisplayStringLine(Line6,"Receive:");
	
	USART_SendString("Welcome to HBEU\r\n");//发送字符串
	
    while(1){			
		if(RXOVER == 1){
			LCD_ClearLine(Line7);
			LCD_DisplayStringLine(Line7,USART_RXBUF);
			for(i=0;i<20;i++){
				USART_RXBUF[i] =' ';  //清空接收区
			}
			RXOVER = 0;
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
	}
}

/**
  * @说明     USART2 相关GPIO和工作模式配置
  * @参数     None 
  * @返回值   None
  */
void USART_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	NVIC_Configuration();
    //配置USART2 TX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置USART2 RX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //串口2工作模式配置
    USART_InitStructure.USART_BaudRate = 19200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2, ENABLE);
}

/**
  * @说明     USART2字符串发送函数
  * @参数     str: 指向字符串的指针
  * @返回值   None
  */
void USART_SendString(int8_t *str)
{
    uint8_t index = 0;
    
    do
    {
        USART_SendData(USART2,str[index]);
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
        index++;        
    }
    while(str[index] != 0);  //检查字符串结束标志
    
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
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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
