#include "threeWheelMove.h"
#include "action_driver.h"
#include "update.h"
#include "math.h"
#include "debug.h"



float Pulse2Vel(float pulse);
float Vel2Pulse(float vel);


void VelControlTriWheel(float v1,float v2,float v3)
{
		ActionSetVelocity(1,Vel2Pulse(-v3));
		ActionSetVelocity(2,Vel2Pulse(-v2));
		ActionSetVelocity(3,Vel2Pulse(-v1));
}


/**
  * @brief  ��׼��λ�ٶ�ת��Ϊ�����ٶ�
  * @param  vel:�ٶ� mm/s
  * @retval velpulse:�ٶ� ����/s
  */
float Vel2Pulse(float vel)
{
	float pulse = 0.0f;
	pulse = vel / (2.0f * PI * WHEELRADIUS) * STDPULSE * REDUCTION;
	return pulse;
}


/**
  * @brief  �����ٶ�ת��Ϊ��׼��λ�ٶ�
  * @param  pulse:�ٶ� ����/s
  * @retval vel:�ٶ� mm/s
  */
float Pulse2Vel(float pulse)
{
	float vel = 0.0f;
	vel = pulse * (2.0f * PI * WHEELRADIUS) / REDUCTION / STDPULSE;
	return vel;
}



float GetAccMax(void)
{
	return 630.0f;
}

float GetVelMax(void)
{
	return 5000.0f;
}

float GetRobotRadius(void)
{
	return 291.32f;
}
