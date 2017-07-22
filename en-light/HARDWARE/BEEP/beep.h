#ifndef BEEP_H
#define BEEP_H
#include "sys.h"
//LED端口定义
#define BEEP PFout(8) //蜂鸣器控制IO
void BEEP_Init(void);
#endif
