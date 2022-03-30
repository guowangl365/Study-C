#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "lcd1602.h"

#include "i2c.h"
 
#define KEY_ON	1
#define KEY_OFF	0
 
uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);

int main(void)
{
	uint8_t temp;
	uint8_t string[20];
	
 	SysTick_Config(SystemCoreClock/1000);
 GPIO_Configuration();
  LCD1602_Init();
//  LED_Config();
//	  LCD1602_Show_Str(0,0,"   I2C DEMO  ");
		LCD1602_Show_Str(0,0,"  AT24C02 R/W");		
		//OLED_P8x16Str(0,6,"Computer Depart");	
	
	i2c_init();	
	temp = x24c02_read(0xff);
	delay_ms(2);
	//x24c02_write(0xff,++temp);
	//delay_ms(2);
	
	sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
	LCD1602_Show_Str(0,2,string);
	while(1)
	{
		
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))//判断按键按下
		{
			delay_ms(2);
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))
			{
				x24c02_write(0xff,++temp);
			                delay_ms(2);
				
				temp = x24c02_read(0xff);
				delay_ms(2);
				sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
				LCD1602_Show_Str(0,2,string);
				while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15));//等待按键松开
			}
		}
		

	}
}
 

/**
  * @说明     从AT24C02指定地址读出一个字节数据
  * @参数     address:AT24C02内部存储地址
  * @返回值   val:读出数据
  */
uint8_t x24c02_read(uint8_t address)
{
	unsigned char val;
	
	I2CStart(); 
	I2CSendByte(0xa0);
	I2CWaitAck(); 
	
	I2CSendByte(address);
	I2CWaitAck(); 
	
	I2CStart();
	I2CSendByte(0xa1); 
	I2CWaitAck();
	val = I2CReceiveByte(); 
	I2CWaitAck();
	I2CStop();
	
	return(val);
}

/**
  * @说明     向AT24C02指定地址写入一个字节数据
  * @参数     address:AT24C02内部存储地址
  * @参数     info:写入数据
  * @返回值   None
  */
void x24c02_write(unsigned char address,unsigned char info)
{
	I2CStart(); 
	I2CSendByte(0xa0); 
	I2CWaitAck(); 
	I2CSendByte(address);	
	I2CWaitAck(); 
	I2CSendByte(info); 
	I2CWaitAck(); 
	I2CStop();
}
 
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);       
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //当按键没有按下时，IO口检测为高电平，为上拉电阻模式，按下IO口与地连接，为低电平   
//  GPIO_InitStructure.GPIO_Speed =    GPIO_Speed_50MHz; //与按键相连的IO口为输入，不需要设置接口速度，只有输出才用
	GPIO_Init(GPIOB,&GPIO_InitStructure) ; 

}


