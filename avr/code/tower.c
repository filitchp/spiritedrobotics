//compiler includes
#include <avr/io.h>
#include <avr/interrupt.h>

#include "definitions.h"	


#include <util/delay.h>

#include "led_strip.h"
#include "motor_driver.h"
#include "communication.h"

int main (void)
{	
	sei(); // Enable Global Interrupts

	// PWM Stuff
	Init_PWM();
	Init_Motor1();

	// Set up the SPI
	initialize_communication();

	// Set the LED pins to output
	DDRB |= (1<<0) | (1<<1) | (1<<2);

	// Turn all of the LEDs off
	PORTB |= ( (1<<0) | (1<<1) | (1<<2) );
	LightStrip led_strip;
	int num_leds_on_strip = 20;

	init_led_strip(&led_strip, num_leds_on_strip);
	Write_To_Led_Strip(&led_strip);
	Write_To_Led_Strip(&led_strip);

	unsigned int counter = 0;
	for (;;)
	{
//		if(Process_Incomming_Data_If_Available() == FAILURE)
//		{
//			PORTB &= ~(1<<0);
//		}
//		Transmit_Data_If_Available();
		
		mod_rainbow(&led_strip, counter);
		Write_To_Led_Strip(&led_strip);
		counter += 10;
		_delay_ms(25);
	/
	}
	return SUCCESS;
}

/* 
LED Test
	// Set the LED pins to output
	DDRB |= (1<<0) | (1<<1) | (1<<2);

	LightStrip led_strip;
	int num_leds_on_strip = 20;

	init_led_strip(&led_strip, num_leds_on_strip);

	unsigned int counter = 0;
	for (;;)
	{
		//Toggle the led
		PORTB ^= (1<<0);

		rainbow(&led_strip, counter);
		Write_To_Led_Strip(&led_strip);
		counter += 10;
		_delay_ms(25);
	}

Receive Test 
	initialize_communication();

	// Set the LED pins to output
	DDRB |= (1<<0) | (1<<1) | (1<<2);

	// Turn all of the LEDs on
	PORTB &= ~( (1<<0) | (1<<1) | (1<<2) );

	unsigned char received_byte;

	for (;;) // Loop forever 
	{ 

		received_byte = blocking_receive_byte();

		PORTB ^= (1<<2);

		if (received_byte == 0)
			PORTB ^= (1<<0);
		else if (received_byte == 1)
			PORTB ^= (1<<1);


		//blocking_transmit_byte(received_byte);
	}

Transmit Test  
	initialize_communication();

	// Set the LED pins to output
	DDRB |= (1<<0) | (1<<1) | (1<<2);

	// Turn all of the LEDs off
	PORTB |= (1<<0) | (1<<1) | (1<<2);

	unsigned char received_byte;
	unsigned char sending_byte;

	for (;;) // Loop forever 
	{ 
		// Turn all of the LEDs off
		PORTB |= (1<<0) | (1<<1) | (1<<2);

		_delay_ms(1000);

		PORTB &= ~(1<<0);

		sending_byte = 0;
		blocking_transmit_byte(sending_byte);

		_delay_ms(1000);

		PORTB &= ~(1<<1);

		sending_byte = 1;
		blocking_transmit_byte(sending_byte);

		_delay_ms(1000);

		PORTB &= ~(1<<2);

		sending_byte = 2;
		blocking_transmit_byte(sending_byte);

		_delay_ms(3000);
	}

	


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
