#include "stm32f10x.h"//f103芯片头文件
#include "delay.h"
#include "stdio.h"
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
//电机初始化
void motor_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;   
	//使能(打开)端口B的硬件时钟，就是对端口B供电
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

   //配置GPIO口为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_6 | GPIO_Pin_7;//PB5 PB8 PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//高速响应
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出，增加输出电流能力
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_5);//让 PB5输出 高电平  打开电机驱动
}
//前进
void car_go(void)
{

    /*给电机供电*/
	
	
	//正转
	GPIO_SetBits(GPIOB, GPIO_Pin_8);//让 PB8输出 高电平  
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//让 PB9输出 低电平
	
	//反转
	//GPIO_ResetBits(GPIOB, GPIO_Pin_8);//让 PB8输出 低电平  
	//GPIO_SetBits(GPIOB, GPIO_Pin_9);//让 PB9输出 高电平
	
  	
	//正转
	GPIO_SetBits(GPIOB, GPIO_Pin_6);//让 PB6输出 高电平  
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//让 PB7输出 低电平


}
//前进
void car_left(void)
{

	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//让 PB8输出 高电平  
	GPIO_SetBits(GPIOB, GPIO_Pin_8);//让 PB9输出 低电平

}
void car_stop(void)
{

    /*给电机供电*/
	
	
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);//让 PB8输出 高电平  
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//让 PB9输出 低电平
	
	//反转
	//GPIO_ResetBits(GPIOB, GPIO_Pin_8);//让 PB8输出 低电平  
	//GPIO_SetBits(GPIOB, GPIO_Pin_9);//让 PB9输出 高电平
	

	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//让 PB6输出 高电平  
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//让 PB7输出 低电平


	
}
void car_right(void)
{
                GPIO_SetBits(GPIOB, GPIO_Pin_6);	
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);


}
void car_circle(void)
{
    
                GPIO_SetBits(GPIOB, GPIO_Pin_8);
                GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);

}
void car_back(void)
{
      /*给电机供电*/
//	GPIO_SetBits(GPIOB, GPIO_Pin_5);//让 PB5输出 高电平  打开电机驱动
  //反转
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);//让 PB8输出 低电平  
	GPIO_SetBits(GPIOB, GPIO_Pin_9);//让 PB9输出 高电平
	
	  //反转
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//让 PB6输出 低电平  
	GPIO_SetBits(GPIOB, GPIO_Pin_7);//让 PB7输出 高电平

}
int main()//入口
{  

	motor_init();
  delay_init(); 
  uart_init();	
	while(1)
	{
	    
		  //等待数据传输完毕
    if(uart_rev == 'a')
		{
		   car_go();
		   //小车前进
		  
		}
    if(uart_rev == 'b')
		{
		
		   //小车停止
		  car_stop();
		}
		if(uart_rev == '3')	
    {
			car_left();
		}			
			if(uart_rev == '2')	
    {
			car_right();
		}			
		if(uart_rev == 'c')	
    {
			car_back();
		}			
			if(uart_rev == 'd')	
    {
			car_circle();
		}			
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



