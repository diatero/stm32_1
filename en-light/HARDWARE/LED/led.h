#ifndef LED_H
#define LED_H
#include "sys.h"
//LED¶Ë¿Ú¶¨Òå
#define LED0 PEout(2)		//DS0
#define LED1 PEout(4)	//DS1

void LED_Init(void);
#endif
