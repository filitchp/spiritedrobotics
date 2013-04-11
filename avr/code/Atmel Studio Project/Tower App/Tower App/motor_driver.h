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
void Set_Motor1_Velocity( int16_t  velocity);
void Set_Motor2_Velocity( int16_t  velocity);

bool Set_Pour_Pwm( int16_t pwmDutyCycle);
bool Set_Reversing_Pwm( int16_t pwmDutyCycle);
bool Set_Reversing_Time(uint16_t reversingTime);
uint16_t Calculate_Time(uint8_t timeHighByte, uint8_t timeLowByte);


void Pour_Drink(uint16_t time);
void Stop_Pouring(void);
void Start_Motor_Timer(uint16_t time);
void Blocking_Wait_For_Motor_Timer_Complete();

#endif

