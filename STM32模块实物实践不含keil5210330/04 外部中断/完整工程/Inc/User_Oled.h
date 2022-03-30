#ifndef User_Oled
#define User_Oled

#include "stdint.h"	
#include "stm32f10x.h"

void OLED_WrCmd(uint8 cmd);
void OLED_WrDat(uint8 data);
void OLED_fill(uint8 bmp_data);
void OLED_Set_Pos(uint8 x, uint8 y);
void OLED_P8x16Str(uint8 x,uint8 y,uint8 ch[]);
void OLED_Print_Num(uint8 x, uint8 y, uint16 num);
void OLED_DisPlay_8x16Char(uint8 x,uint16 y,uint8 data);
void OLED_Print_8x16_4(uint8 x,uint8 y, int16 data);
void OLED_Print_8x16_2(uint8 x,uint8 y, int8 data);
void OLED_P16x16Str(uint8 x,uint8 y,uint8 ch[]);

u32 oled_pow(u8 m,u8 n);
void OLED_Showdecimal(u8 x,u8 y,float num,u8 len,u8 size2);

#endif



