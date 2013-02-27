//compiler includes
#include <avr/io.h>

//for delay calculations
#define F_CPU 1000000
#include <util/delay.h>

#include "led_strip.h"
#include "motor_driver.h"
#include "communication.h"


int main (void)
{

	initialize_communication();

	// Set the LED pins to output
	DDRB |= (1<<0) | (1<<1) | (1<<2);

	// Turn all of the LEDs off
	PORTB &= ~( (1<<0) | (1<<1) | (1<<2) );

	unsigned char received_byte;

	for (;;) // Loop forever 
	{ 
		PORTB &= ~(1<<2);

		received_byte = blocking_receive_byte();

		if (received_byte == 0)
			PORTB ^= (1<<0);
		else if (received_byte == 1)
			PORTB ^= (1<<1);

		PORTB |= (1<<2);

		blocking_transmit_byte(received_byte);
	}
	/*
	// PWM stuff for motor
	int velocity = 255;
	int vel_delta = 1;
	Init_PWM();
	Init_Motor1();
	Set_Motor1_Velocity(velocity);


	// Set the LED pins to output
	DDRB |= (1<<0) | (1<<1) | (1<<2);

	// Turn all of the LEDs off
	PORTB &= ~( (1<<0) | (1<<1) | (1<<2) );


	unsigned int counter = 0;
	unsigned char lights = 0;
	unsigned char last_lights = 0;
	for (;;)
	{
		counter += 1;
		if (counter == 2000)
		{
			counter = 0;
			++lights;

			velocity += vel_delta;

			if (velocity >= 254)
			{
				vel_delta = -1;
				PORTB |= (1<<0);
			}
			if (velocity <= -254)
			{
				vel_delta = 1;
				PORTB &= ~(1<<0);
			}
			Set_Motor1_Velocity(velocity);
		}

		if (last_lights != lights)
		{
			last_lights = lights;

			//if (lights & (1<<0))
			//	PORTB |= (1<<0);
			//else
			//	PORTB &= ~(1<<0);

			if (lights & (1<<1))
				PORTB |= (1<<1);
			else
				PORTB &= ~(1<<1);

			if (lights & (1<<2))
				PORTB |= (1<<2);
			else
				PORTB &= ~(1<<2);
		}
	}

	*/
	return 0;
}
