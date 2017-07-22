#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "beep.h"

int main(void)
{
	u8 key_up=1;
	 int key = 0;           //保存键值
	delay_init(168);  //初始化延时函数
	LED_Init();				//初始化LED端口 
	//BEEP_Init();      //初始化蜂鸣器端口
	KEY_Init();       //初始化与按键连接的硬件接口
	LED0=0;				  	//先点亮红灯
	int time = 100;
	int bei = 100;
	int en = 0;
	
	while(1)
	{	
			if(key_up&&(KEY0==0))
		{
			delay_ms(10);//去抖动 
			key_up=0;
			if(KEY0==0)LED0 = !LED0;
		}else if(KEY0==1)key_up=1; 	
			
	}
	while(1);



}
