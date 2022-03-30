#ifndef  __I2C_H__
#define  __I2C_H__


#include "sys.h"
#include "stm32f10x_i2c.h"

void i2c_init(void);
void delay1(unsigned int n);

void I2CStart(void);
void I2CStop(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
unsigned char I2CWaitAck(void);

void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);


u16 m24c02_read(u16 address);
void m24c02_write(u16 address,u16 info);



#endif
