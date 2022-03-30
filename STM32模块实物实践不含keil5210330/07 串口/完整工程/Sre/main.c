#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"

uint8_t USART_RXBUF[20];
extern uint8_t RXOVER;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
//void Delay_Ms(uint32_t nTime);
void USART_Config(void);
void USART_SendString(int8_t *str);

int main(void)
{
 	uint8_t i;
	SysTick_Config1(SystemCoreClock/1000);
 
  OLED_Init();
//  LED_Config();
    OLED_P8x16Str(0,0,"   USART DEMO    ");
//		OLED_P16x16Str(0+8,2,"湖工计算机学院");
		OLED_P8x16Str(0,2,"Receiv & Display");		
		OLED_P8x16Str(0,4,"Receive:");	
	USART_Config();
		USART_SendString("Welcome to HBEU\r\n");//发送字符串
	while(1)
	{
		
			if(RXOVER == 1){
//			LCD_ClearLine(Line7);
//			LCD_DisplayStringLine(Line7,USART_RXBUF);
			OLED_P8x16Str(0,6,USART_RXBUF);		
				
			for(i=0;i<20;i++){
				USART_RXBUF[i] =' ';  //清空接收区
			}
			RXOVER = 0;
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
		
		
				
	}
}
 
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
 
 
