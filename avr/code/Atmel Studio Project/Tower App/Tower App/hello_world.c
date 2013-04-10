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
	LightStrip led_strip;
	int num_leds_on_strip = 160;

	init_led_strip(&led_strip, num_leds_on_strip);


	Init_PWM();
	Init_Motor1();
	Set_Motor1_Velocity(0);
	int motor_counter = 0;


	unsigned int counter = 0;
	for (;;)
	{
		rainbow(&led_strip, counter, 1000);
		Write_To_Led_Strip(&led_strip);
		counter += 50;
		motor_counter += 1;
		if (motor_counter == 255)
			motor_counter = -254;

		Set_Motor1_Velocity(motor_counter);

	}

	return 0;
}

