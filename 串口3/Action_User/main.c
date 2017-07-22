#include "stm32f4xx.h"
#include "usart.h"
#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "timer.h"
#include "stm32f4xx_it.h"
#include "gpio.h"
#include "usart.h"
#include "can.h"
#include "math.h"
#include "stm32f4xx_usart.h"
#include "arm_math.h"


int chuan_num = 0;
uint8_t data;

void init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	  
	TIM_Init(TIM2,999,839,0,0);					//主周期定时10ms	
	
	GPIO_Init_Pins(GPIOE,GPIO_Pin_2,GPIO_Mode_OUT);
	
	USART3_Init(115200);
	
}

int main(void)
{
	delay_ms(1000);
	init();
	
	USART_SendData(USART3,0);
	USART_OUT(USART3,(uint8_t*) "action");
	
	
	while(1)
	{
			data = '0';
			delay_ms(50);
			if(data == '0')
			{
				while(1)
				{
					GPIO_ResetBits(GPIOE, GPIO_Pin_2);//点亮
					GPIO_ResetBits(GPIOE, GPIO_Pin_4);//点亮
					delay_ms(100);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);//关
					GPIO_SetBits(GPIOE, GPIO_Pin_2);//关
					delay_ms(100);
				}
			}
			else 
			{
					GPIO_ResetBits(GPIOE, GPIO_Pin_2);//点亮
					GPIO_ResetBits(GPIOE, GPIO_Pin_4);//点亮
			}
	}
}


//extern uint8_t data;
//extern uint8_t arr[5];
//static int num;
//	if(USART_GetITStatus(USART3, USART_IT_RXNE)==SET)   
//	{
//			arr[num] = USART_ReceiveData(USART3);
//		  USART_SendData(USART3,arr[num]);
//			num++;
//			num = num%4;
//			if(arr[0]=='L'&&arr[1]=='E'&&arr[2]=='D'&&arr[3]=='0')
//			{
//				GPIO_ResetBits(GPIOE, GPIO_Pin_2);//点亮
//				GPIO_SetBits(GPIOE, GPIO_Pin_4);//关
//			}
//			else if(arr[0]=='L'&&arr[1]=='E'&&arr[2]=='D'&&arr[3]=='1')
//			{	
//				GPIO_SetBits(GPIOE, GPIO_Pin_2);//关
//				GPIO_ResetBits(GPIOE, GPIO_Pin_4);//点亮
//			}

//			USART_ClearITPendingBit( USART3,USART_IT_RXNE);
//	}
//	 

