#include "stm32f4xx.h"
#include "led.h"
#include "beep.h"
#include "delay.h"

//实际上这一部分就是呼吸灯的循环体部分
//给出了 light % 的亮度
void SetLight_1ms(uint16_t light)
{
#define PERIOD_TIM_US 1001u
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);//点亮
	delay_us(light);//持续light us
	GPIO_SetBits(GPIOE, GPIO_Pin_2);	//熄灭
	delay_us(PERIOD_TIM_US - light);  //持续 （2000-light） us
}

int main(void)
{
#define HORSE		0
#define BREATH		1

	int LED_Mode = BREATH;
	int time = 0;
	int pressCnt = 0;

    delay_init(168);
    LED_Init();
	KeyInit();
	BEEP_Init();

    while(1)
	{
		//计循环数 在1~1999 循环
		time++;
		if(time == 2000)
			time = 1;
		
		//如果连续3000次检测都为触发，则改变状态
		if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))
		{
			pressCnt++;
		}
		else
		{
			pressCnt=0;
		}

		if(pressCnt >= 3000)
		{
			LED_Mode=1-LED_Mode;
			pressCnt=0;
		}
		
		
        switch(LED_Mode)
		{
			case HORSE:
				if(0 < time && time <= 1000)
				{
					GPIO_ResetBits(GPIOE,GPIO_Pin_2);
					GPIO_ResetBits(GPIOE,GPIO_Pin_4);
					
				}
				else if(time > 1000)
				{
					GPIO_SetBits(GPIOE,GPIO_Pin_4);
					GPIO_SetBits(GPIOE,GPIO_Pin_2);
				}
				delay_ms(1);
				break;
			case BREATH:
				if (0 < time && time < 1000)
				{
					GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_4);
					delay_us(time);
					GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_4);
					delay_us(1000-time);
				}
				else if (time > 1000 )
				{
					GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_4);
					delay_us(2000-time);
					GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_4);
					delay_us(time-1000);
				}
				break;
			default:
				break;
		}
	}
}

