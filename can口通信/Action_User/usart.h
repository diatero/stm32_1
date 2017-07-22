#ifndef __USART_H
#define __USART_H

#include "stdint.h"
#include "stm32f4xx_usart.h"

void USARTx_Init(uint32_t BaudRate);
void USART_OUT(USART_TypeDef* USARTx,const uint8_t *Data,...);



#endif

