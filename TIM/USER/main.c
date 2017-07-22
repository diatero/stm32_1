#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
#include "timer.h"

int main(void)
{ 
	int num,presscnt=0,num2=0,mode=0;
	u8 tur;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	LED_Init();		  //初始化LED端口
	KEY_Init();
 	TIM4_Int_Init(5000-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms
	
	while(1)
	{
		num=rec();
		switch (mode)
		{
			case 1:
			{
				if((num%3)>=1)
				{
					GPIO_ResetBits(GPIOE,GPIO_Pin_2);
				}
				else if((num%3)<1)
				{
					GPIO_SetBits(GPIOE,GPIO_Pin_2);
				}
				break;
			}
			case 0:
			{
				if((num%2)==1)
				{
					GPIO_ResetBits(GPIOE,GPIO_Pin_2);
				}
				else if((num%2)==0)
				{
					GPIO_SetBits(GPIOE,GPIO_Pin_2);
				}
				break;
			}
		}
		if((tur=KEY_Scan(0))==1&&num!=num2)
		{
			presscnt++;
			num2=rec();
		}
		else if((tur=KEY_Scan(0))==0)
		{
			presscnt=0;
			num2=0;
		}
		if (presscnt>=6)
		{
			mode=!mode;
			presscnt=0;
			num2=0;
		}
			
			
		
	}
}
