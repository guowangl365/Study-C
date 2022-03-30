#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"

#include "delay.h"

extern u32 TimingDelay;
uint8_t ADC_Flag;

void ADC_Config(void);
float Read_ADC(void);

int main(void)
{
	float adc_temp;
	uint8  string[20];  //ADC结果

 	SysTick_Config1(SystemCoreClock/1000);
 
	ADC_Config();
	
  OLED_Init();
//  LED_Config();
  OLED_P8x16Str(0,0,"  ADC DEMO    ");
	OLED_P8x16Str(0,2,"PA1-ADC chnl 1");	
	while(1)
	{
		if(ADC_Flag)
			{
			  ADC_Flag = 0;
			  adc_temp = Read_ADC();
			  sprintf((char*)string,"%s%.3f","ADC Value:",adc_temp);
			  //LCD_DisplayStringLine(Line7,string);
				OLED_P8x16Str(0,4,string);
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
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//PB0-ADC channel 8
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//PA1-ADC channel 1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ADC1 工作模式配置
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  //单次转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

//	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_13Cycles5);    

  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_13Cycles5);    
 
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
	//Delay_Ms(5);
	delay_ms(5);
	ADC_VALUE = ADC_GetConversionValue(ADC1)*3.30/0xfff;
	
	return ADC_VALUE;
}
 
 
