#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "beep.h"

int main(void)
{
	u8 key_up=1;
	 int key = 0;           //�����ֵ
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿� 
	//BEEP_Init();      //��ʼ���������˿�
	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED0=0;				  	//�ȵ������
	int time = 100;
	int bei = 100;
	int en = 0;
	
	while(1)
	{	
			if(key_up&&(KEY0==0))
		{
			delay_ms(10);//ȥ���� 
			key_up=0;
			if(KEY0==0)LED0 = !LED0;
		}else if(KEY0==1)key_up=1; 	
			
	}
	while(1);



}
