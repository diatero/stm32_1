#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#define KEY0   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) 
#define KEY0_PRES  1  
void KEY_Init(void);
u8 KEY_Scan(u8);
#endif