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

bool Set_Pour_Pwm(int pwm);
bool Set_Reversing_Pwm(int pwm);
bool Set_Reversing_Time(unsigned int time);
unsigned int Calculate_Time(unsigned char b1, unsigned char b2);


void Pour_Drink(unsigned int time);
void Stop_Pouring(void);
void Start_Motor_Timer(unsigned int time);
void Blocking_Wait_For_Motor_Timer_Complete();

#endif

