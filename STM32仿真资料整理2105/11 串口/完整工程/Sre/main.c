#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "lcd1602.h"


uint8_t USART_RXBUF[5];
extern uint8_t RXOVER;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
//void Delay_Ms(uint32_t nTime);
void USART_Config(void);
//void USART_SendString(int8_t *str);
void USART_SendString(unsigned char *buf);

int main(void)
{
 	uint8_t i;

	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	//SysTick_Init();
	SysTick_Config(SystemCoreClock/100000);
   GPIO_Configuration(); 
   LCD1602_Init();
//  LED_Config();
//   LCD1602_Show_Str(0,0,"   USART DEMO    ");
//		OLED_P16x16Str(0+8,2,"湖工计算机学院");
//		LCD1602_Show_Str(0,0,"Receiv & Display");		
	LCD1602_Show_Str(0,0,"Receive:");	
	USART_Config();
		//USART_SendString(Tx_Buf);//发送字符串
		USART_SendString("Welcome to HBEU\r\n");//发送字符串
	while(1)
	{
		if(RXOVER == 1){
//			LCD_ClearLine(Line7);
//			LCD_DisplayStringLine(Line7,USART_RXBUF);
			LCD1602_Show_Str(0,2,USART_RXBUF);		
				
			for(i=0;i<5;i++){
				USART_RXBUF[i] =' ';  //清空接收区
			}
			RXOVER = 0;
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);/////////////////////////////////////////////////////////////
		}
		
		/*if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
		{
			USART_SendData(USART1,USART_ReceiveData(USART1));
			delay_ms(1000);
		}*/
				
	}
}
 
/*void USART_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//NVIC_Configuration();
    //配置USART2 TX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置USART2 RX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //串口2工作模式配置
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
	
	//USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1, ENABLE);
}*/

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	//DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	//DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	NVIC_Configuration();
	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = 9600;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USART1, &USART_InitStructure);

	// 使能串口
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1, ENABLE);	    
}

/**
  * @说明     USART2字符串发送函数
  * @参数     str: 指向字符串的指针
  * @返回值   None
  */
/*void USART_SendString(int8_t *str)
{
    uint8_t index = 0;
    
    do
    {
        USART_SendData(USART1,str[index]);
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
        index++;        
    }
    while(str[index] != 0);  //检查字符串结束标志
    
}*/

void USART_SendString(unsigned char *buf)
{
	while (*buf != '\0')
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, *buf++);

	}
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
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
 
 
