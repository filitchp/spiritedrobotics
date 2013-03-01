#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdlib.h>

/**************************************************
 *	     This code is designed to		  *
 *	     drive the L293			  *
 **************************************************/


/**************************************************
 *		   Motor Driver API		  *
 **************************************************/
void Init_PWM();
void Init_Motor1();
void Init_Motor2();
void Set_Motor1_Velocity(int velocity);
void Set_Motor2_Velocity(int velocity);

/**************************************************
 *		   Motor Driver API		  *
 **************************************************/

void Start_Motor_Timer(unsigned int time);
void Blocking_Wait_For_Motor_Timer_Complete();

#endif

