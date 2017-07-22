/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "can.h"
uint8_t CAN1Buffer = 0;
extern int count5,count2,count3,count4,count1;
extern int period[2];
extern int board;
extern int led;
extern int mode[2];
extern  int step;
extern  int status;
extern int counti;
uint8_t data[9];
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/************************************************************/
/****************驱动器CAN1接口模块****start******************/

void CAN1_RX0_IRQHandler(void)//1号板用于接收按键切换。
{
	uint32_t StdId = 0,i;
	
	CanRxMsg RxMessage;
	if(CAN_MessagePending(CAN1,CAN_FIFO0)!=0)
	{
		
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
//		for(i=0;i<RxMessage.DLC;i++)
		CAN1Buffer=RxMessage.Data[0];
	}
	CAN_ClearFlag(CAN1, CAN_FLAG_FMP0);
}


void CAN2_RX0_IRQHandler(void)
{
	uint32_t StdId = 0,i;
	uint8_t CAN2Buffer[8] = {0};
	CanRxMsg RxMessage;
	if(CAN_MessagePending(CAN2,CAN_FIFO0)!=0)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
		for(i=0;i<RxMessage.DLC;i++)
		CAN2Buffer[i]=RxMessage.Data[i];
		led=CAN2Buffer[0];
		if(led!=4)
		{
			mode[led-1]=CAN2Buffer[1];
			period[led-1] =CAN2Buffer[2];
		}
		else if(led==4)
			count4=0;
		}
	CAN_ClearFlag(CAN2, CAN_FLAG_FMP0);
} 
uint8_t rec()
{
	return CAN1Buffer;
}
/****************驱动器CAN1接口模块****end******************/
/************************************************************/

/*************定时器2******start************/

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)==SET)
  {	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }	 
}


void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update)==SET)    
	{                                                
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}

void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8, TIM_IT_Update)==SET)    
	{                                                
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
	}
}

/********************************************************/
/*****************普通定时TIM5*****Start*****************/
void TIM5_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM5, TIM_IT_Update)==SET)    
	{              
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)==SET)    
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
	}
}



//定时器4  
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)==SET)
	{         
			count5++;
			count3++;
			count1++;
			count2++;
			count4++;
			if(count5>=period[0]*10000)
			{
				count5=0;
			}
			if(count1>=period[1]*10000)
			{
				count1=0;
			}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void UART5_IRQHandler(void)
{

	if(USART_GetITStatus(UART5, USART_IT_RXNE)==SET)   
	{
		USART_ClearITPendingBit( UART5,USART_IT_RXNE);	
	}
	 
}



void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)   
	{
		USART_ClearITPendingBit( USART1,USART_IT_RXNE);
	}
}


void USART3_IRQHandler(void)
{
	
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE)==SET)   
	{
//		data[counti] = USART_ReceiveData(USART3);
//		
////		USART_SendData(USART3,data);
//		if(data[counti]==' '||step>=8)
//				counti=0;

//		 if(counti==8)
//				counti=0;
//			counti++;
//		
//		if(data[0]=='B')
//			step++;
//		else if(data[0]=='S'&&data[1]=='t'&&data[2]=='a'&&data[3]=='t'&&data[4]=='u'&&data[5]=='s')
//		{
//			step=8;
//			status =1;
////			USART_OUT(USART3,(uint8_t*) "B%dLED%d%s%d\r\n",board ,led,mode ,period );
//			
//		}
//		switch(data[1])
//		{
//			case '1': { board =1; step++;break;}
//			case '2': { board =2; step++;break;}
//		}
//		if(data[2]=='L'&&data[3]=='E'&&data[4]=='D')
//			step=step+3;
//		switch(data[5])
//		{
//			case '1': { led  =1; step++;break;}
//			case '2': { led  =2; step++;break;}
//		}
//		switch(data[6])
//		{
//			case 'B': { 
//									if(led==1&&board ==1)
//									{
//										mode[0]  ='B';
//										step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										mode[1]  ='B';
//										step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										mode[2]  ='B';
//										step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										mode[3]  ='B';
//										step++;break;
//									}
//								}
//			case 'M': { if(led==1&&board ==1)
//									{
//										mode[0]  ='M';
//										step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										mode[1]  ='M';
//										step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										mode[2]  ='M';
//										step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										mode[3]  ='M';
//										step++;break;
//									}
//								}
//		}
//		switch(data[7])
//		{
//			case '1': { 
//									if(led==1&&board ==1)
//									{
//										period[0]  =1; step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										period[1]  =1; step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										period[2]  =1; step++;break;
//									}
//									if(led==2&&board ==2)
//									{
//										period[3]  =1; step++;break;
//									}
//								}
//			case '2': {
//									if(led==1&&board ==1)
//									{
//										period[0]  =2; step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										period[1]  =2; step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										period[2]  =2; step++;break;
//									}
//									if(led==2&&board ==2)
//									{
//										period[3]  =2; step++;break;
//									}				
//								}
//			case '3': { 	
//									if(led==1&&board ==1)
//									{
//										period[0]  =3; step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										period[1]  =3; step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										period[2]  =3; step++;break;
//									}
//									if(led==2&&board ==2)
//									{
//										period[3]  =3; step++;break;
//									}
//								}
//			case '4': {
//										if(led==1&&board ==1)
//									{
//										period[0]  =4; step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										period[1]  =4; step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										period[2]  =4; step++;break;
//									}
//									if(led==2&&board ==2)
//									{
//										period[3]  =4; step++;break;
//									}
//								}
//			case '5': {
//										if(led==1&&board ==1)
//									{
//										period[0]  =5; step++;break;
//									}
//									if(led==2&&board ==1)
//									{
//										period[1]  =5; step++;break;
//									}
//									if(led==1&&board ==2)
//									{
//										period[2]  =5; step++;break;
//									}
//									if(led==2&&board ==2)
//									{
//										period[3]  =5; step++;break;
//									}
//								}
//			
//		}
//		if(step<8)
//			status =2; 
//			USART_OUT(USART3,(uint8_t*) "CmdError");
		
		
		USART_ClearITPendingBit( USART3,USART_IT_RXNE);
	}
}



/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
   while (1)
   {
   }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{

  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{

  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
 
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

