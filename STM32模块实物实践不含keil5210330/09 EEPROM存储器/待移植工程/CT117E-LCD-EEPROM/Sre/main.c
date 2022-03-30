/*******************************************************************************  
* 文件名称：EEPROM读写实验
* 实验目的：1.掌握EEPROM AT24C02的操作方法
*           2.掌握I2C总线协议和通讯原理
* 程序说明：1.从EEPROM 0xff地址读出数据dat,++dat后重新写回0xff地址
*           2.通过LCD显示0xff地址存储的数据,每次复位后，数值加1
* 日期版本：2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
/* Private function prototypes -----------------------------------------------*/
void Delay_Ms(uint32_t nTime);
uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);
/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{
	uint8_t temp;
	uint8_t string[20];
	
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

	LCD_DisplayStringLine(Line1,"      I2C DEMO      ");
	LCD_DisplayStringLine(Line3,"     AT24C02 R/W    ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	i2c_init();	
	
	temp = x24c02_read(0xff);
	Delay_Ms(2);
	x24c02_write(0xff,++temp);
	Delay_Ms(2);
	
	sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
	LCD_DisplayStringLine(Line6,string);
		
    while(1){			
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
