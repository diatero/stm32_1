#ifndef __TIME_H
#define __TIME_H
#include <stdint.h>
#include "sys.h"
void TIM4_Int_Init(uint16_t arr,uint16_t psc);
int rec(void);
#endif