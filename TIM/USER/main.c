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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();		  //��ʼ��LED�˿�
	KEY_Init();
 	TIM4_Int_Init(5000-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms
	
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
