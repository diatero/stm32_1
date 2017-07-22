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
#include "stm32f4xx_tim.h"
#include "arm_math.h"

//GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) 0Îª°´ÏÂ
int period[2],count5=0,count2=0,count3=0,count1=0,count4=0,board,led, mode[2],step=0,beep=0,status=0,counti=0;

int main(void)
{

	uint8_t message[3]={0},mbox;
	int led0pwmval=0,dir=1,which,led0pwmval1=0,dir1=1;
	uint8_t* po;
	po=message;
	uint8_t CANSendData[8] = {0};
	CAN1_Init();
	CAN2_Init();
	LEDInit();
	KeyInit();
	BeepInit();
	TIM4_Int_Init(5-1,1680-1);//0.1ms
	TIM13_Pwm_Init(500 - 1, 84 - 1);
	TIM14_Pwm_Init(500 - 1, 84 - 1);
	USARTx_Init(115200);
	mode[0]='B';
	period [0]=3;
	mode[1]='M';
	period [1]=4;
	
	while(1)
	{
		step=0;
	
				if(mode[0]=='M')
					{
					
						if(count5<=(period[0]*10000/2))
							TIM_SetCompare1(TIM13,500);
						if(count5>=(period[0]*10000/2))
							TIM_SetCompare1(TIM13,0);
						
					}
					if(mode[1]=='M')
					{
						
						if(count1<=(period[1]*10000/2))
							TIM_SetCompare1(TIM14,500);
						if(count1>=(period[1]*10000/2))
							TIM_SetCompare1(TIM14,0);
						
					}
					if(mode[0]=='B')
					{
						TIM_SetCompare1(TIM13,led0pwmval);
						if (10*period[0]<=count2)
							{
								count2=0;
								 if(dir)
									 led0pwmval++;
								 else 
									 led0pwmval--;
								 if(led0pwmval>=500)
									 dir=0;
								 if(led0pwmval<=0)
									 dir=1;
							}
					}
					if(mode[1]=='B')
					{
						TIM_SetCompare1(TIM14,led0pwmval1);
						if (10*period[1]<=count3)
						{
							count3=0;
							 if(dir1)
								 led0pwmval1++;
							 else 
								 led0pwmval1--;
							 if(led0pwmval1>=500)
								 dir1=0;
							 if(led0pwmval1<=0)
								 dir1=1;
						 }
					
								
					}
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)==0)
		{
			message[0]=1;
			message[1]=mode[0];
			message[2]=period[0];
			CAN_TxMsg(CAN2,0,message,3);
			message[0]=2;
			message[1]=mode[1];
			message[2]=period[1];
			CAN_TxMsg(CAN2,0,message,3);
		}
		if(count4>=10000)
				GPIO_SetBits(GPIOE,GPIO_Pin_7);
	}
}
