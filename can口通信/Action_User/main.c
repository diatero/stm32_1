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
int period[4],count=0,count2=0,count3=0,count1=0,count4=0,board,led,step=0, mode[4],beep=0,status=0,counti=0,period_re[4],mode_re[4];
	char MODE1[2],MODE2[2],MODE3[2],MODE4[2];
uint8_t data[9];



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
	mode[0]='M';
	period [0]=1;
	mode[1]='B';
	period [1]=2;
	data[0]=0;data[1]=0;data[2]=0;data[3]=0;data[4]=0;data[5]=0;data[6]=0;data[7]=0;data[8]=0;

	while(1)
	{
					step=0;
//				if(board==1&&led==1)
//					which=0;
//				if(board==1&&led==2)
//					which=1;
				if(board==2&&led==1)
					which=2;
				if(board==2&&led==2)
					which=3;
					if(mode[0]=='M')
					{
					
						if(count<=(period[0]*10000/2))
							TIM_SetCompare1(TIM13,500);
						if(count>=(period[0]*10000/2))
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
		
		switch(status)
		{
			case 1:
			{
				if(mode[0]=='B')
					MODE1[0]='B';
				else
					MODE1[0]='M';
				if(mode[1]=='B')
					MODE2[0]='B';
				else
					MODE2[0]='M';
				if(mode[2]=='B')
					MODE3[0]='B';
				else
					MODE3[0]='M';
				if(mode[3]=='B')
					MODE4[0]='B';
				else
					MODE4[0]='M';
				MODE1[1]='\0';
				MODE2[1]='\0';
				MODE3[1]='\0';
				MODE4[1]='\0';
				USART_OUT(USART1,(uint8_t*) "  B1LED1%s%d\r\n  B1LED2%s%d\r\n  B2LED1%s%d\r\n  B2LED2%s%d\r\n",MODE1,period[0],MODE2,period [1],MODE3,period [2],MODE4,period [3] );
				status=0;
				break;
			}
			case 2:
			{
				USART_OUT(USART1,(uint8_t*) "CmdError");
				status=0;
				break;
			}
			case 3:
			{
				mode[2]=mode[0];
				mode[3]=mode[1];
				period [2]=period [0];
				period [3]=period [1];
				message[0]=2;
				message [1]=mode[1];
				message[2]=period[1] ;
				CAN_TxMsg(CAN1,1,message,3);
				message[0]=1;
				message [1]=mode[0];
				message[2]=period[0] ;
				CAN_TxMsg(CAN1,1,message,3);
				
				period[1]=period_re [1];
				period [0]=period_re [0];
				mode[0]=mode_re[0];
				mode[1]=mode_re[1];
				status=0;
				USART_OUT(USART1,(uint8_t*) "StatusSwitch");
				break;
				
			}
		
		
		}
		if(board==2)
		{
				message[0]=led;
				message[1]=mode[led+1];
				message[2]=period[led+1] ;
				CAN_TxMsg(CAN1,1,message,3);
				board=0;
		}
		message[0]=4;
		CAN_TxMsg(CAN1,2,message,1);
		
		
}
	}
