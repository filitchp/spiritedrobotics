#include <stdlib.h>
#include <avr/io.h>

#include "motor_driver.h"

//This initializes timer 0 (8 bits) to phase correct PWM
void Init_PWM()
{
    // Set timer 0 to wave generation mode phase correct PWM
    TCCR0A |= (1<<WGM00);
    TCCR0A &= ~(1<<WGM01);
    TCCR0B &= ~(1<<WGM02);

    // Set the clock source of the timer to be 
    // the I/O clock without prescaling
    TCCR0B |= (1<<CS00);
    TCCR0B &= ~(1<<CS01);
    TCCR0B &= ~(1<<CS02);

    // Zero both of the compare registers
    OCR0A = 0;
    OCR0B = 0;

    // Disable both PWM outputs
    TCCR0A &= ~( (1<<COM0A0) | (1<<COM0A1) );
    TCCR0A &= ~( (1<<COM0B0) | (1<<COM0B1) );
}

void Init_Motor1()
{
    // Set both the pwm pin and the direction pin to be outputs
    DDRD |= (1<<DDD6) | (1<<DDD7);

    // Enable the PWM output for timer 0 comare register B
    TCCR0A &= ~(1<<COM0A0);
    TCCR0A |= (1<<COM0A1);
}

void Init_Motor2()
{
    // Set both the pwm pin and the direction pin to be outputs
    DDRD |= ( (1<<DDD4) | (1<<DDD5) );

    // Enable the PWM output for timer 0 comare register A
    TCCR0A &= ~(1<<COM0B0);
    TCCR0A |= (1<<COM0B1);
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

