/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "timer.h"
#include "gpio.h"
#include "usart.h"
#include "can.h"
#include "update.h"
#include "debug.h"
#include "string.h"
#include <stdlib.h>
#include "action_driver.h"
#include "MotionCard.h"
#include "update.h"
#include "action_driver.h"
#include "threeWheelMove.h"


#define FLASH_NUM  0x08040000 	
//正常模式
#define NORMAL_MODE 1
//采集模式
#define SAMPLING_MODE 2


static int  mode = 1;

_Bool GyroscopeFlag = 0;

void RotateVelControl(float vel)
{
	if(vel>260) vel = 260;
	if(vel<-260) vel = -260;
	ThreeWheelVelControl(0,0,vel);
}


void Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

	//CAN1初始化，用于电机控制
	CAN_Config(CAN1,500,GPIOB,GPIO_Pin_8, GPIO_Pin_9); 
	
	
	//陀螺仪接收串口
	USART3_Init(115200);
	
	//蓝牙串口
	GYRO_USART2_Init(115200);
	
	//蜂鸣器初始化
	MyBeefInit();
	
	//行程开关
	MySwitchInit();
	
	//定时器初始化 10ms
	TIM_Init(TIM2, 999, 839, 0, 0);
	
	//初始化内存池
	BufferZizeInit(500);
	
	BeefON();
	
  TIM_Delayms(TIM5, 1000);
	
	BeefOFF();
	
	while(GyroscopeFlag == 0)
	{
		//如果等待陀螺仪初始化期间发生按键触发情况，进行采样模式
		if(ReadSwitch() == 1)
		{
				BeefON();
				mode = SAMPLING_MODE;
		}
		else
		{
				BeefOFF();
		}
	}


	/*********************MOTOR DRIVE INTI**************************/


		ActionSetHeartbeatInterval(1, 100);
		ActionSetHeartbeatInterval(2, 100);
		ActionSetHeartbeatInterval(3, 100);
		ActionSetOperationalMode(1); // 发送命令前，需要控制驱动器 在可操作模式
		ActionSetOperationalMode(2); // 发送命令前，需要控制驱动器 在可操作模
		ActionSetOperationalMode(3); // 发送命令前，需要控制驱动器 在可操作模
		ActionConfigVelocity(1,200000,200000);
		ActionConfigVelocity(2,200000,200000);
		ActionConfigVelocity(3,200000,200000);
	
		BeefON();

		TIM_Delayms(TIM5, 1000);


	/*********************TIMER INIT*******************************/
		BeefON();

		TIM_Delayms(TIM5, 1000);

		BeefOFF();

}





extern int Signal;
int main(void)
{

	Init();
	mode = 4;
	float angle=0,angle_old=0,err,output,ki=5.5,kd=1,err_old;
	while(1)
	{
		while(!Signal);
		Signal = 0;
		angle_old =angle ;
		angle=GetAngleZ() ;
		err=60-angle;
		err_old=60-angle_old;
		output=ki*err+kd*(err -err_old );
	 RotateVelControl(output );//每秒转x秒
		GetAngleZ();
		USART_OUT(SENDUSART,(uint8_t *)"%d\n",(int)GetAngleZ());
	}


}


