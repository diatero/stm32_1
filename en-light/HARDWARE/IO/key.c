#include "key.h"
#include "delay.h"

//������ʼ������
void KEY_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//ʹ��GPIOA��GPIOEʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//key0,1,2��Ӧ����
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  //GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
}

//������������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//�������ɿ���־ 
	if(key_up&&(KEY0==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 1;
	}else if(KEY0==1)key_up=1; 	    
 	return 0;// �ް�������

}
	