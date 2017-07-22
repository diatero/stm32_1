#include "key.h"
#include "delay.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,  ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;
	if(KEY0==0)
		{
//			delay_ms(10);
			key_up=0;
			if(KEY0==0)
				return 1;
			else if(KEY0==1)
				key_up=1;
			
		}
		return 0;
}