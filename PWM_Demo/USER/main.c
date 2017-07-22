#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
int cnum=500,r=1,count=0;
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM2时钟

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM2

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM2,ENABLE); //使能定时器3

	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
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
	//                               初始化部分
	//=======================================================================================
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);      //设置系统中断优先级分组2
	delay_init (168);      //初始化延时函数
//	uart_init (115200);      //初始化串口波特率为115200
	USART3_Init(115200);
	TIM13_PWM_Init (500 - 1, 84 - 1);	  //84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.
	TIM2_Int_Init(5-1,1680-1);//0.1MS一次
	u16 led0pwmval=0;    
	u8 dir=1;   
	
	
	int interval=5000;
	
	
	//=======================================================================================
	//                               while (1) 循环
	//=======================================================================================	
	while (1)      //实现比较值从0-300递增，到300后从300-0递减，循环
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
		     //修改比较值，修改占空比
	}
}
