#include "delay.h"
 

u32 TimingDelay=0;

						   
 void delay_ms(u32 ntime)
 {
	 TimingDelay=ntime;
	 while(TimingDelay!=0);
 }
