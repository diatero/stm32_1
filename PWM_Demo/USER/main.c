#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
int cnum=500,r=1,count=0;
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM2ʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM2

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��3

	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		count++;
  }
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
int main(void)
{ 
	//=======================================================================================
	//                               ��ʼ������
	//=======================================================================================
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);      //����ϵͳ�ж����ȼ�����2
	delay_init (168);      //��ʼ����ʱ����
//	uart_init (115200);      //��ʼ�����ڲ�����Ϊ115200
	USART3_Init(115200);
	TIM13_PWM_Init (500 - 1, 84 - 1);	  //84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.
	TIM2_Int_Init(5-1,1680-1);//0.1MSһ��
	u16 led0pwmval=0;    
	u8 dir=1;   
	
	
	int interval=5000;
	
	
	//=======================================================================================
	//                               while (1) ѭ��
	//=======================================================================================	
	while (1)      //ʵ�ֱȽ�ֵ��0-300��������300���300-0�ݼ���ѭ��
	{
			TIM_SetCompare1(TIM13,led0pwmval);	

				interval=(r*500*10/cnum);
			if (interval<=count)
			{
				count=0;
				 if(dir)
					 led0pwmval++;
				 else 
					 led0pwmval--;
				 if(led0pwmval>=cnum)
					 dir=0;
				 if(led0pwmval==0)
					 dir=1;
			 }
//		
		     //�޸ıȽ�ֵ���޸�ռ�ձ�
	}
}
