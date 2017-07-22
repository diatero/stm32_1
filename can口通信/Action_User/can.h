#ifndef __CAN_H
#define __CAN_H
#include "stm32f4xx_can.h"

void CAN1_Init(void);
void CAN2_Init(void);

uint8_t CAN_RxMsg(CAN_TypeDef* CANx,
				  uint32_t * StdId,
				  uint8_t * buf,
				  uint8_t len);

uint8_t CAN_TxMsg(CAN_TypeDef* CANx,
				  uint32_t StdId,
				  uint8_t * buf,
				  uint8_t len);

#endif
