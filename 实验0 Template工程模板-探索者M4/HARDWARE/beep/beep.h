#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"
#define BEEP PEout(7)
void BEEP_Init(void);
#endif