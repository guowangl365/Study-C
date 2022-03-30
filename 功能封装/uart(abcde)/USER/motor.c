#include "motor.h"


//GPIO 结构体初始化
//static GPIO_InitTypeDef GPIO_InitStructure;
//电机初始化
void motor_init(void)
	
{
	static GPIO_InitTypeDef GPIO_InitStructure;
	
   	//使能(打开)端口B的硬件时钟，就是对端口B供电
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

   //配置GPIO口为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_6 | GPIO_Pin_7;//PB5 PB8 PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//高速响应
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出，增加输出电流能力
	GPIO_Init(GPIOB, &GPIO_InitStructure);
/*给电机供电*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//让 PB5输出 高电平  打开电机驱动
}
//前进
void car_go(void)
{

    
	
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
void car_left(void)
{
                GPIO_SetBits(GPIOB, GPIO_Pin_8);
                GPIO_ResetBits(GPIOB, GPIO_Pin_9);
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
void car_stop(void)
{
   GPIO_ResetBits(GPIOB, GPIO_Pin_8);//让 PB8输出 低电平  
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//让 PB9输出 高电平
	
	  //反转
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//让 PB6输出 低电平  
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//让 PB7输出 高电平


}

