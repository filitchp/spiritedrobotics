#include <stdlib.h>
#include <avr/io.h>
#include "definitions.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "led_strip.h"

/**************************************************
 *		   LED Strip API		  *
 **************************************************/

LIGHTSTRIP base;
LIGHTSTRIP top;
LIGHTSTRIP led_strip;
uint16_t state_firing_time;
volatile uint16_t state_counter;
uint16_t last_counter;
uint16_t saved_counter;
size_t state;
#define STANDBY 0
#define FIRING 1

void init_led_strip()
{

	LIGHTSTRIP* strip = &led_strip;
	 int16_t  num_leds_on_strip = 20;
	saved_counter = 0;

	if (strip == 0)
	{
		// throw error
		return;
	}

	SPI_MasterInit();


	// Enable the interrupt
	TIMSK2 |= (1<<TOIE2);

	// Tick every 10ms is 78 cycles of timer 2 with a 1024 prescaler (Tck @ 8MHz)
	// Set the clock source and prescaler
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); 

	// set the sate counter to zero
	state_counter = 0;
	last_counter = 1;

	// Sweet malloc bro (fix this so it is constant)
	strip->lights = (LIGHT*) malloc( num_leds_on_strip * sizeof(LIGHT));

	if (strip->lights == 0)
	{
		// error allocating memory.
		// we should do something to alert the user
	}
	else
	{
		strip->num_lights = num_leds_on_strip;

		 int16_t  i;
		for (i=0; i<strip->num_lights; ++i)
			set_led_color(strip, i, 0, 0, 0);
	}

	Write_To_Led_Strip(strip);
	Write_To_Led_Strip(strip);

	get_base_subset(strip, &base);
	get_top_subset(strip, &top);
	set_top(strip, 20,20,20);
}

void led_strip_standby()
{
	LIGHTSTRIP* strip = &led_strip;
	set_top(strip, strip->lights[1].red / 10, strip->lights[1].green / 10, strip->lights[1].blue / 10);
	state_counter = saved_counter;
	state = STANDBY;
}

void led_strip_fire(uint16_t time)
{
	LIGHTSTRIP* strip = &led_strip;
	saved_counter = state_counter;
	state_counter = 0;
	state_firing_time = (time);
	set_top(strip, strip->lights[0].red * 10, strip->lights[0].green * 10, strip->lights[0].blue* 10);
	set_base(strip, strip->lights[0].red * 10, strip->lights[0].green * 10, strip->lights[0].blue * 10);
	state = FIRING;
}

void led_strip_update()
{
	// if the state counter has not transitioned, nothing to do
	if (last_counter == state_counter) { return; }	
	
	last_counter = state_counter;
	double static led_counter = 0;

	if (state_counter % 16 == 0)
	{
		led_counter += 1;
	}

	switch (state)
	{
		case STANDBY:
			rainbow(&base, led_counter, 42);
			break;
		case FIRING:
			drain(&top, state_counter, state_firing_time, (&base)->lights[0]);
			break;
	}

	Write_To_Led_Strip(&led_strip);
}

void set_led_color(LIGHTSTRIP* strip, size_t index, uint8_t red, uint8_t green, uint8_t blue)
{
	if (index >= strip->num_lights)
		return;

	strip->lights[index].red = red;
	strip->lights[index].green = green;
	strip->lights[index].blue = blue;
}

void Write_To_Led_Strip(LIGHTSTRIP* lights)
{
	 int16_t  i;
	for (i=0; i<lights->num_lights; ++i)
	{
		send_next_light(&lights->lights[i]);
	}

	send_end_of_sequence();
}

/**************************************************
 *		  Color Paterns			  *
 **************************************************/

uint8_t get_brightness(uint16_t p)
{
	uint8_t out;
	if (p < 128)
		out = (uint8_t) p;
	else if (p < 256)
		out = (uint8_t)(255 - p);
	else
		out = (uint8_t)0;

	return out / 10;
}

void rainbow(LIGHTSTRIP* strip, uint16_t counter, uint16_t spread)
{
	const uint16_t cycle_length = 384;
	size_t num_lights = strip->num_lights;
	uint16_t c = counter % cycle_length;

	size_t i;
	for (i=0; i<num_lights; ++i)
	{
		uint16_t cycle_position = (((cycle_length * i * 10) / (num_lights * (spread + 1))) + c) % cycle_length;

		strip->lights[i].red   = get_brightness(cycle_position); 
		strip->lights[i].green = get_brightness((cycle_position + 128)%cycle_length); 
		strip->lights[i].blue  = get_brightness((cycle_position + 256)%cycle_length); 
	}
}

void mod_rainbow(LIGHTSTRIP* strip, uint16_t counter)
{
	LIGHTSTRIP base;
	get_base_subset(strip, &base);

	LIGHTSTRIP top;
	get_top_subset(strip, &top);

	rainbow(&base,counter,50);
	fill(&top, counter, 300, (&base)->lights[0]);
}

void fill(LIGHTSTRIP* strip, uint16_t counter, uint16_t total, LIGHT mimic)
{
	uint16_t red = mimic.red;
	uint16_t green = mimic.green;
	uint16_t blue = mimic.blue;

	//if(red+green+blue == 0){ red = 127; green = 127; blue = 127; }

	uint16_t c = counter; //% total;

	size_t i;

	for (i=0; i<((c * (strip->num_lights + 1)) /total); i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}

	for(;i < strip->num_lights; i++){
		strip->lights[i].red = 0;
		strip->lights[i].green = 0;
		strip->lights[i].blue = 0;
	}

}

void drain(LIGHTSTRIP* strip, uint16_t counter, uint16_t total, LIGHT mimic)
{
	uint16_t red = mimic.red;
	uint16_t green = mimic.green;
	uint16_t blue = mimic.blue;

	//if(red+green+blue == 0){ red = 127; green = 127; blue = 127; }



	uint16_t c = 0;
	if (total >= counter) { c = total - counter; } //% total;

	size_t i;
	uint16_t num = strip->num_lights;

	for (i=0; i<((c * (strip->num_lights + 1)) / (total+1)); i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}

	for(;i < strip->num_lights; i++){
		strip->lights[i].red = 0;
		strip->lights[i].green = 0;
		strip->lights[i].blue = 0;
	}

}


/**************************************************
 *		  Color Patern Helpers	  *
 **************************************************/


void set_left(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue)
{
	size_t i;
	for (i=0; i<=3; i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}
}

void set_front(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue)
{
	size_t i;
	for (i=4; i<=7; i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}
}

void set_right(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue)
{
	size_t i;
	for (i=8; i<=11; i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}
}

void set_top(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue)
{ 
	size_t i;
	for (i=12; i<=19; i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}
}

void set_base(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue)
{
	size_t i;
	for (i=0; i<=11; i++){
		strip->lights[i].red = red;
		strip->lights[i].green = green;
		strip->lights[i].blue = blue;
	}
}  

void get_base_subset(LIGHTSTRIP* strip, LIGHTSTRIP* subset)
{
	subset->lights = strip->lights;
	subset->num_lights = 12;
} 

void get_top_subset(LIGHTSTRIP* strip, LIGHTSTRIP* subset)
{
	subset->lights = strip->lights+12;
	subset->num_lights = 8;
} 

/**************************************************
 *		 Helper Functions		  *
 * *************************************************/

void send_next_light(LIGHT* light)
{
	uint8_t enable = 0x80;

	SPI_MasterTransmit(enable | (*light).green);
	SPI_MasterTransmit(enable | (*light).red);
	SPI_MasterTransmit(enable | (*light).blue);
}

void send_end_of_sequence()
{
	uint8_t zero = 0x00;
	 int16_t  i;
	for (i=0; i<3; i++)
	{
		SPI_MasterTransmit(zero);
	}
}


/**************************************************
 *		   SPI Driver Code		  *
 **************************************************/

void SPI_MasterInit(void)
{
	// !!!!! add 4.7K isolation resistors to MISO MOSI ASND SCK LINES TO PREVENT INTERFERENCE DURING PROGRAMMING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/* Set MOSI and SCK output */
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);
	/* Set MISO to input */
	DDR_SPI &=~ (1<<DD_MISO);

	/* Enable SPI, Master, set clock rate */
	SPCR =  (1<<SPE)	| // SPI Enable
		//(1<<DORD)	| // Reverse data order
		(1<<MSTR)	| // SPI Master mode
		//(1<<CPOL)	| // Reverse the clock polarity
		//(1<<SPR1)	| // Sets the spi clock frequency
		(1<<SPR0)	; // Sets the spi clock frequency

	//SPSR |= (1<<SPI2X); // Run the SPI twice as fast
}

void SPI_MasterTransmit(uint8_t cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	// There is an interrupt bit that can be set.
	// We can use this if we want to free up the processor
	while(!(SPSR & (1<<SPIF)))
	{}
}

ISR (TIMER2_OVF_vect)
{
	// overflow will occur in 78 tics (10ms)
	TCNT2 = 0xFF - 78;

	// increment the state counter
	state_counter += 1;
}

