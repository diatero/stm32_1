#ifndef KEY_H
#define KEY_H
#include "sys.h"

//ͨ��ֱ�Ӳ����⺯����ȡIO
#define KEY0	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//KEY0-PE4
//#define KEY1	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//KEY1-PE3
//#define KEY2	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//KEY2-PE2
//#define WK_UP	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//MK_UP-PA0

#define KEY0_PRES	1
//#define KEY1_PRES	2
//#define KEY2_PRES	3
//#define WKUP_PRES	4

void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(void);			//����ɨ�躯��
#endif

