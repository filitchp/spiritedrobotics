#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "definitions.h"
#include "motor_driver.h"
#include "led_strip.h"

volatile bool reversing = FALSE;

// Motor stuff
volatile unsigned int remainder_cycles = 0;
volatile unsigned int cycles_remaining = 0;

static volatile int				pour_pwm = 160;
static volatile int				reversing_pwm = -200;
static volatile unsigned int	reversing_time = 0x056E;


//This initializes timer 0 (8 bits) to phase correct PWM
void Init_PWM()
{
	// Set timer 0 to wave generation mode phase correct PWM
	TCCR0A |= (1<<WGM00);
	TCCR0A &= ~(1<<WGM01);
	TCCR0B &= ~(1<<WGM02);

	// Set the clock source of the timer to be 
	// the I/O clock/8  prescaling
	TCCR0B &= ~(1<<CS00);
	TCCR0B |= (1<<CS01);
	TCCR0B &= ~(1<<CS02);

	// Zero both of the compare registers
	OCR0A = 0;
	OCR0B = 0;

	// Disable both PWM outputs
	TCCR0A &= ~( (1<<COM0A0) | (1<<COM0A1) );
	TCCR0A &= ~( (1<<COM0B0) | (1<<COM0B1) );

	// for towers to prevent spilling
	reversing = FALSE;
}

void Init_Motor1()
{
	// Set both the pwm pin and the direction pin to be outputs
	DDRD |= ( (1<<DDD4) | (1<<DDD5) );

	// Enable the PWM output for timer 0 comare register A
	TCCR0A &= ~(1<<COM0B0);
	TCCR0A |= (1<<COM0B1);

	// Enable the overflow interrupt
	TIMSK1 |= (1<<TOIE1); 
}

void Init_Motor2()
{
	// Set both the pwm pin and the direction pin to be outputs
	DDRD |= (1<<DDD6) | (1<<DDD7);

	// Enable the PWM output for timer 0 comare register B
	TCCR0A &= ~(1<<COM0A0);
	TCCR0A |= (1<<COM0A1);
}

void Set_Motor1_Velocity(int velocity)
{

	// Max velocity is 255, we are going to limit it to 254
	if(velocity > 254)
		velocity = 254;
	else if (velocity < -254)
		velocity = -254;

	if(velocity >= 0)
	{
		// Set the data direction bit
		PORTD |= (1<<PD4);

		// Set the velocity
		OCR0B = velocity;
	}
	else
	{
		//set the data direction bit
		PORTD &= ~(1<<PD4);

		// Make the velocity positive
		velocity = -velocity;

		// Set the velocity
		OCR0B = velocity;
	}
}

void Set_Motor2_Velocity(int velocity)
{

	// Max velocity is 255, we are going to limit it to 254
	if(velocity > 254)
		velocity = 254;
	else if (velocity < -254)
		velocity = -254;

	if(velocity >= 0)
	{
		// Set the data direction bit
		PORTD |= (1<<PD7);

		// Set the velocity
		OCR0A = velocity;
	}
	else
	{
		//set the data direction bit
		PORTD &= ~(1<<PD7);

		// Make the velocity positive
		velocity = -velocity;

		// Set the velocity
		OCR0A = velocity;
	}
}


bool Set_Pour_Pwm(int pwm)
{
	if ( (pwm <= 0) || (pwm >= 255) ) { return FAILURE; }
	
	pour_pwm = pwm;
	return SUCCESS;
}

bool Set_Reversing_Pwm(int pwm)
{
	if ( (pwm <= 0) || (pwm >= 255) ) { return FAILURE; }
	
	reversing_pwm = -pwm;
	return SUCCESS;
}

bool Set_Reversing_Time(unsigned int time)
{
	reversing_time = time;
	return SUCCESS;
}

unsigned int Calculate_Time(unsigned char b1, unsigned char b2)
{
	return (((unsigned int)b1)<<7) | ((unsigned int)b2);
}




void Pour_Drink(unsigned int time)
{
	PORTB &= ~(1<<2);

	Set_Motor1_Velocity(pour_pwm); //nominally 160

	cycles_remaining = (time>>12);
	remainder_cycles = (time<<4);
	Start_Motor_Timer(remainder_cycles);
}

void Stop_Pouring(void)
{
	// Turn off the clock 
	TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));

	Set_Motor1_Velocity(0);
	PORTB |= (1<<2);
	led_strip_standby();
	reversing = FALSE;
}

void Start_Motor_Timer(unsigned int time)
{
	unsigned int result = 0xFFFF;
	result -= time;

	// Set the timer value
	TCNT1 = result;

	// Set the clock to be Fosc / 1024
	TCCR1B |= ((1<<CS12) | (1<<CS10));
}

void Blocking_Wait_For_Motor_Timer_Complete()
{
	while(!(TIFR1 & (1<<TOV1)))
	{}

	// Turn off the timer
	TCCR1B &= ~((1<<CS12) | (1<<CS10));

	// Clear the interrupt flag by writing one to it
	TIFR1 |= (1<<TOV1);
}


ISR (TIMER1_OVF_vect)
{
	// TODO: figure out why this does not reverse the motor
	if (cycles_remaining == 0)
	{
		// This is happens after we reverse the motor 
		if (reversing == TRUE)
		{
			// Turn off the clock 
			TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
			Set_Motor1_Velocity(0);
			PORTB |= (1<<2);
			led_strip_standby();
			reversing = FALSE;
		}
		// When the acutal time stops, reverse the motor
		else
		{
			Set_Motor1_Velocity(reversing_pwm);
			Start_Motor_Timer(reversing_time);
			reversing = TRUE;
		}
	}
	else
	{
		--cycles_remaining;
	}
}


