#include "stm32f10x.h"
#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @说明     主函数
  * @参数     None 
  * @返回值   None
  */
int main(void)
{
    unsigned int i;
    
    LED_Init();
    LED_Control(LEDALL,0);//关闭所有LED灯
	
    while(1){
        LED_Control(LED6,1);//已改端口C14
        for(i=0x3fffff; i>0; i--);
        LED_Control(LED6,0);
        for(i=0x3fffff; i>0; i--);
        
		LED_Control(LED7,1); //已改端口C15
        for(i=0x3fffff; i>0; i--);
        LED_Control(LED7,0);
        for(i=0x3fffff; i>0; i--);
    }          //LED0和LED1灯轮流闪烁。
}
