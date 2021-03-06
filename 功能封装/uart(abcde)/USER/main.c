#include "stm32f10x.h"//f103芯片头文件
#include "delay.h"
#include "stdio.h"
#include "motor.h"

char uart_rev;
//串口初始化
void uart_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
    //1.打开硬件时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,ENABLE);
    //2.设置GPIO参数
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
   //3.设置uart参数
	  USART_InitStructure.USART_BaudRate = 115200;//波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数据位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
    USART_Init(USART1, &USART_InitStructure);

   
    /* 选择中断分组 */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    /* 配置中断参数 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//中断通道 串口1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能
    NVIC_Init(&NVIC_InitStructure);

    //使能串口的接收中断
		 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	 //4.使能串口
    USART_Cmd( USART1, ENABLE);
}

//通过串口发送字符串
void uart_send_string(char *p)
{
     while(*p != '\0')
		{
		
		   USART_SendData(USART1,*p);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) 
			{}
		   p++;
		}
}
//printf重定向
//重定向fput这个函数，printf函数会调用到
int fputc(int ch,FILE *f)
{
	//发送数据
		   USART_SendData(USART1,ch);
	
	//检查是否发送完成
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
	
	return ch;

}

//初始化超声波模块
void sr04_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	  //1.打开硬件时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //2.设置GPIO参数
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
     GPIO_ResetBits( GPIOB, GPIO_Pin_11);	
}
//获取超声波检测距离
int get_distance(void)
{
    int n=0;
   //1.PB11发送启动信号 大于10us的高电平信号
	  GPIO_SetBits( GPIOB, GPIO_Pin_11);
	  delay_us(15);
    GPIO_ResetBits( GPIOB, GPIO_Pin_11);	

   //2.检测输入到PB12（输入模式）的电平信号 
		while(GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_12)!=1);
	
	 //3.获取echo高电平持续的时间
    while(GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_12)!=0)
		{
		
		   delay_us(9);
        			
		   n++;
		    
		}

   // 4.计算距离
   return    3*n/2;


}

int main()//入口
{  
  int distance ;
	delay_init();
	sr04_init();
	uart_init();
	 car_go();
	 printf("sr04 test\n"); 


	while(1)
	{
	  
	   distance =  get_distance();
	   printf("sr04 get distance is  %d mm\n",distance);	
	   delay_ms(1000);
		if(distance<=300) car_stop();
  //  	else car_stop();
	}
	
	
   
}
//串口中断服务函数
void USART1_IRQHandler(void)
{
   //检测中断是否正在发生
	 if(USART_GetITStatus(USART1,USART_IT_RXNE)==1)
	 {
	     //执行中断任务代码 
	    uart_rev = USART_ReceiveData( USART1);
		   USART_SendData(USART1,uart_rev);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) ;
	 }
   
   //清空中断标志位 以便于接收下一次中断

   USART_ClearITPendingBit(USART1,USART_IT_RXNE);

}





