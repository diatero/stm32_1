#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "time.h"
int main(void)
{
	int num;
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM4_Int_Init(5000-1,8400-1);
	while(1)
	{
		num=rec();
		
	}
}

