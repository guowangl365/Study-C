#ifndef  _MOTOR_H
#define  _MOTOR_H

#include "stm32f10x.h"
void motor_init(void);
void car_go(void);
void car_back(void);
void car_left(void);
void car_right(void);
void car_circle(void);
void car_stop(void);
#endif
