/**
  ******************************************************************************
  * @file    can.c
  * @author  Calcus Lee
  * @version V1.0.1
  * @date    9-August-2013
  * @brief   functions of CAN
  ******************************************************************************
  * @attention
  * 1.the default CAN mode is normal
  * 2.by default, the CAN Rx Interrupt is ON
  * 3.CAN_IT_FMP0, CAN_IT_FMP1 IRQ is auto cleared.
  ******************************************************************************
**/

#include "can.h"
#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "String.h"
extern int count4;


void CAN1_Init(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef  	   NVIC_InitStructure;
	
	/*Enable the CAN controller interface clock*/

	
	/*Enable the clock for the CAN GPIOs*/


	/*Connect the involved CAN pins to AF9*/

	
	/*Configure these CAN pins in alternate function mode*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1); 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);

	CAN_DeInit(CAN1);

	/*Initialise and configure the CAN*/
	CAN_InitStructure.CAN_TTCM = DISABLE;        		 //time triggered communication mode
	CAN_InitStructure.CAN_ABOM = ENABLE;         		//automatic bus-off management
	CAN_InitStructure.CAN_AWUM = DISABLE;         		//automatic wake-up mode
	CAN_InitStructure.CAN_NART = DISABLE;        		 //non-automatic retransmission mode
	CAN_InitStructure.CAN_RFLM = DISABLE;         		//Receive FIFO Locked mode
	CAN_InitStructure.CAN_TXFP = DISABLE;         		//transmit FIFO priority
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; 		//CAN operating mode
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;   			// keep CAN_SJW == 1, never change it
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq; 			//max=16
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq; 			//max=8
	CAN_InitStructure.CAN_Prescaler = 4;	
	/* CAN Baudrate =APB1_CLK/((CAN_SJW_tq+CAN_BS1_tq+CAN_BS2_tq)*CAN_Prescaler) */
	CAN_Init(CAN1, &CAN_InitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;	    //Filter 0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	 //32 Bit
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;               	//32 Bis ID
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;          	 //32 Bit Mask
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;          	 //activate Filter
	CAN_FilterInit(&CAN_FilterInitStructure);							//intialize Filter
	
	/*Initialise and configure NVIC and IT*/
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn ; 	//CAN1Ω” ‹	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0x00 ;        
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x03 ;                      
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             
	NVIC_Init(&NVIC_InitStructure);                               
	CAN_ITConfig(CAN1,CAN_IT_FMP0 , ENABLE);
}	

void CAN2_Init(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef  	   NVIC_InitStructure;
	
	/*Enable the CAN controller interface clock*/

	
	/*Enable the clock for the CAN GPIOs*/

	/*Connect the involved CAN pins to AF9*/

	
	/*Configure these CAN pins in alternate function mode*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	CAN_DeInit(CAN2);

	/*Initialise and configure the CAN*/
	CAN_InitStructure.CAN_TTCM = DISABLE;        		 //time triggered communication mode
	CAN_InitStructure.CAN_ABOM = ENABLE;         		//automatic bus-off management
	CAN_InitStructure.CAN_AWUM = DISABLE;         		//automatic wake-up mode
	CAN_InitStructure.CAN_NART = DISABLE;        		 //non-automatic retransmission mode
	CAN_InitStructure.CAN_RFLM = DISABLE;         		//Receive FIFO Locked mode
	CAN_InitStructure.CAN_TXFP = DISABLE;         		//transmit FIFO priority
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; 		//CAN operating mode
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;   			// keep CAN_SJW == 1, never change it
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq; 			//max=16
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq; 			//max=8
	CAN_InitStructure.CAN_Prescaler = 4;	
	/* CAN Baudrate =APB1_CLK/((CAN_SJW_tq+CAN_BS1_tq+CAN_BS2_tq)*CAN_Prescaler) */
	CAN_Init(CAN2, &CAN_InitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=14;	    //Filter 14
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	 //32 Bit
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;               	//32 Bis ID
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;          	 //32 Bit Mask
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;          	 //activate Filter
	CAN_FilterInit(&CAN_FilterInitStructure);							//intialize Filter
	
	/*Initialise and configure NVIC and IT*/
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn ; 		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;        
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                      
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             
	NVIC_Init(&NVIC_InitStructure);                    
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}

/**
  * @brief  transmit an array 
  * @param  CANx:  CANx, where x can be 1,2.
  * @param  StdId: the StdId you want to select as StdId.
  * @param  Msg:   a pointer that point the array you want to transmit.
  * @param  len:   the length of the the array that you want to transmit.
  * @retval 1, if transmit successful. 
  * @author Calcus Lee
**/
uint8_t CAN_TxMsg(CAN_TypeDef* CANx,
				  uint32_t StdId,
				  uint8_t * Msg,
				  uint8_t len)
{
	uint8_t mbox;
	uint8_t i = 0;
	int count3;
	CanTxMsg TxMessage;
	TxMessage.StdId=StdId;
	TxMessage.ExtId=StdId;
	TxMessage.IDE=CAN_Id_Standard ;
	TxMessage.RTR=CAN_RTR_Data ;
	TxMessage.DLC=len;
	for(i=0;i<TxMessage.DLC;i++)
	TxMessage.Data[i]=Msg[i];
	mbox= CAN_Transmit(CANx, &TxMessage);
	while((CAN_TransmitStatus(CANx, mbox)!= CAN_TxStatus_Ok))
	{
				if (count4>=50000)
			GPIO_SetBits(GPIOE,GPIO_Pin_7);
			
	}
	count4=0;
	return 1;		
}


/**
  * @brief  Receive an array 
  * @param  CANx:  CANx, where x can be 1,2.
  * @param  StdId: the StdId you want to select as StdId.
  * @param  Msg:   a array you want to transmit.
  * @param  len:   the length of the the array that you want to transmit.
  * @retval 1, if receive successful
  * @author Calcus Lee
**/
uint8_t CAN_RxMsg(CAN_TypeDef* CANx,
				  uint32_t * StdId,
				  uint8_t * buf,
				  uint8_t len)
{
	uint8_t i=0;
	CanRxMsg RxMessage;
	
		CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
		for(i=0;i<RxMessage.DLC;i++)
		buf[i] =RxMessage.Data[i];
	return 1;
}





