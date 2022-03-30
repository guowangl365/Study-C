#ifndef __ADC_H
#define __ADC_H

#include "sys.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"


void ADC_Config(void);

u16 adc_read(u8 channel);



#endif
