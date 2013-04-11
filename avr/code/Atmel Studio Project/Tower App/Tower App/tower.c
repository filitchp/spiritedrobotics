//compiler includes
#include <avr/io.h>
#include <avr/interrupt.h>

#include "definitions.h"	


#include <util/delay.h>

#include "led_strip.h"
#include "motor_driver.h"
#include "communication.h"

 int16_t  main (void)
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
    
    init_led_strip();
	
	#warning "Deprecated Function Call to led_strip_standby"
    //led_strip_standby();

	for (;;)
	{
		if(Process_Incomming_Data_If_Available() == FAILURE)
		{
			PORTB &= ~(1<<0);
		}
		Transmit_Data_If_Available();
	    led_strip_update();	
	}
	return SUCCESS;
}
