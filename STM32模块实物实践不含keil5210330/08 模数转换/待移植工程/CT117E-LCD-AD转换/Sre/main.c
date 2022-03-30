/*******************************************************************************  
* 文件名称：ADC实验
* 实验目的：STM32处理器ADC的操作与配置方法
* 程序说明：调节电位器R37输出电压，观察LCD上显示的数值
*           ADC工作模式配置:
*			ADC1 独立模式,单次转换
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
uint8_t ADC_Flag;
/* Private function prototypes -----------------------------------------------*/
void Delay_Ms(uint32_t nTime);
void ADC_Config(void);
float Read_ADC(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{   	

	float adc_temp;
	uint8_t  string[20];  //ADC结果

    SysTick_Config(SystemCoreClock/1000);  //1ms中断一次

	ADC_Config();
	
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

	LCD_DisplayStringLine(Line1,"      ADC DEMO      ");
	LCD_DisplayStringLine(Line3,"  PB0-ADC channel 8 ");


	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);
		
    while(1){
		//200毫秒扫描一次ADC
		if(ADC_Flag){
			ADC_Flag = 0;
			adc_temp = Read_ADC();
			sprintf(string,"%s%.3f","ADC Value:",adc_temp);
			LCD_DisplayStringLine(Line7,string);
		} 
	}
}

/**
  * @说明     ADC时钟源及工作模式配置
  * @参数     none
  * @返回值   None
  */
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//PB0-ADC channel 8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// ADC1 工作模式配置
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  //单次转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_13Cycles5);    

	ADC_Cmd(ADC1, ENABLE);   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));
}

/**
  * @说明     读取ADC转换结果
  * @参数     none
  * @返回值   ADC_VALUE:ADC转换结果
  */

float Read_ADC(void)
{
	float ADC_VALUE;
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	Delay_Ms(5);
	ADC_VALUE = ADC_GetConversionValue(ADC1)*3.30/0xfff;
	
	return ADC_VALUE;
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
