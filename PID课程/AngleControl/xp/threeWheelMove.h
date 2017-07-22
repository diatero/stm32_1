#ifndef _THREEWHEELMOVE_H
#define _THREEWHEELMOVE_H
#include "MotionCard.h"


//�Ƕ���ת��Ϊ������ϵ��
#define CHANGE_TO_RADIAN    0.017453f   
//������ת��Ϊ�Ƕ���ϵ��
#define CHANGE_TO_ANGLE     57.2958f				
//Բ����
#define PI                  3.1415926f

#define NULL 0


//���ٱ�
#define REDUCTION (15.0f/1.0f)
//���ְ뾶 ��λ:mm
#define WHEELRADIUS 63.5f
//ÿȦ������
#define STDPULSE 2000.0f



/**
  * @brief  �����ٶ�ת��Ϊ��׼��λ�ٶ�
  * @param  pulse:�ٶ� ����/s
  * @retval vel:�ٶ� mm/s
  */
float Pulse2Vel(float pulse);
float Vel2Pulse(float vel);


void ThreeWheelVellControl(float speed, float angle, float angularVell);


#endif

