#include <stdlib.h>
#include <avr/io.h>
#include "definitions.h"
#include <util/delay.h>

#include "led_strip.h"


/**************************************************
 *		   LED Strip API		  *
 **************************************************/

LightStrip base;
LightStrip top;
LightStrip led_strip;
unsigned int state_firing_time;
unsigned int state_counter;
unsigned int saved_counter;
size_t state;
#define STANDBY 0
#define FIRING 1

void init_led_strip()
{
    
    LightStrip* strip = &led_strip;
    int num_leds_on_strip = 20;
    saved_counter = 0;

    if (strip == 0)
    {
       	// throw error
	return;
    }

    SPI_MasterInit();

    strip->lights = (Light*) malloc( num_leds_on_strip * sizeof(Light));

    if (strip->lights == 0)
    {
	// error allocating memory.
	// we should do something to alert the user
    }
    else
    {
	strip->num_lights = num_leds_on_strip;

	int i;
	for (i=0; i<strip->num_lights; ++i)
	    set_led_color(strip, i, 0, 0, 0);
    }

    Write_To_Led_Strip(strip);
    Write_To_Led_Strip(strip);

    get_base_subset(strip, &base);
    get_top_subset(strip, &top);
    set_top(strip, 20,20,20);
    //TODO start timer
}

void led_strip_standby(){
    LightStrip* strip = &led_strip;
    set_top(strip, strip->lights[12].red / 10, strip->lights[12].green / 10, strip->lights[12].blue / 10);
    state_counter = saved_counter;
    state = STANDBY;
}

void led_strip_fire(unsigned int time){
    LightStrip* strip = &led_strip;
    saved_counter = state_counter;
    state_counter = 0;
    state_firing_time = (time);
    set_top(strip, strip->lights[0].red * 10, strip->lights[0].green * 10, strip->lights[0].blue* 10);
    set_base(strip, strip->lights[0].red * 10, strip->lights[0].green * 10, strip->lights[0].blue * 10);
    state = FIRING;
}

void led_strip_update(){
    state_counter += 1;
    _delay_ms(65);

    switch (state)
    {
        case STANDBY:
            rainbow(&base, state_counter/3, 42);
        break;
        case FIRING:
            drain(&top, state_counter, state_firing_time, (&base)->lights[0]);
        break;
    }

    Write_To_Led_Strip(&led_strip);
}

void set_led_color(LightStrip* strip, size_t index, unsigned char red, unsigned char green, unsigned char blue)
{
    if (index >= strip->num_lights)
		return;

    strip->lights[index].red = red;
    strip->lights[index].green = green;
    strip->lights[index].blue = blue;
}

void Write_To_Led_Strip(LightStrip* lights)
{
    int i;
    for (i=0; i<lights->num_lights; ++i)
    {
	send_next_light(&lights->lights[i]);
    }

    send_end_of_sequence();
}

/**************************************************
 *		  Color Paterns			  *
 **************************************************/

const float one_third = 1.0 / 3.0;
const float two_thirds = 2.0 / 3.0;

unsigned char get_brightness(unsigned int p)
{
	unsigned char out;
	if (p < 128)
		out = (unsigned char) p;
	else if (p < 256)
		out = (unsigned char)(255 - p);
	else
		out = (unsigned char)0;

	return out / 10;
}

void rainbow(LightStrip* strip, unsigned int counter, unsigned int spread)
{
	const unsigned int cycle_length = 384;
    size_t num_lights = strip->num_lights;
    unsigned int c = counter % cycle_length;

    size_t i;
	for (i=0; i<num_lights; ++i)
	{
		unsigned int cycle_position = (((cycle_length * i * 10) / (num_lights * (spread + 1))) + c) % cycle_length;

		strip->lights[i].red   = get_brightness(cycle_position); 
		strip->lights[i].green = get_brightness((cycle_position + 128)%384); 
		strip->lights[i].blue  = get_brightness((cycle_position + 256)%384); 
	}
}

void mod_rainbow(LightStrip* strip, unsigned int counter)
{
    LightStrip base;
    get_base_subset(strip, &base);
    
    LightStrip top;
    get_top_subset(strip, &top);
    
    rainbow(&base,counter,50);
    fill(&top, counter, 300, (&base)->lights[0]);
}

void fill(LightStrip* strip, unsigned int counter, unsigned int total, Light mimic)
{
    unsigned int red = mimic.red;
    unsigned int green = mimic.green;
    unsigned int blue = mimic.blue;

   //if(red+green+blue == 0){ red = 127; green = 127; blue = 127; }

    unsigned int c = counter; //% total;

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

void drain(LightStrip* strip, unsigned int counter, unsigned int total, Light mimic)
{
    unsigned int red = mimic.red;
    unsigned int green = mimic.green;
    unsigned int blue = mimic.blue;

   //if(red+green+blue == 0){ red = 127; green = 127; blue = 127; }
    


    unsigned int c = 0;
    if (total >= counter) { c = total - counter; } //% total;

    size_t i;
    unsigned int num = strip->num_lights;

    for (i=0; i<((c * (strip->num_lights + 1)) / total); i++){
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

void set_left(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue)
{
	size_t i;
    for (i=0; i<=3; i++){
        strip->lights[i].red = red;
        strip->lights[i].green = green;
        strip->lights[i].blue = blue;
    }
}

void set_front(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue)
{
	size_t i;
     for (i=4; i<=7; i++){
        strip->lights[i].red = red;
        strip->lights[i].green = green;
        strip->lights[i].blue = blue;
    }
}

void set_right(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue)
 {
	size_t i;
    for (i=8; i<=11; i++){
        strip->lights[i].red = red;
        strip->lights[i].green = green;
        strip->lights[i].blue = blue;
     }
}

void set_top(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue)
{ 
	size_t i;
    for (i=12; i<=19; i++){
        strip->lights[i].red = red;
        strip->lights[i].green = green;
        strip->lights[i].blue = blue;
     }
}

void set_base(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue)
{
	size_t i;
    for (i=0; i<=11; i++){
        strip->lights[i].red = red;
        strip->lights[i].green = green;
        strip->lights[i].blue = blue;
     }
}  

void get_base_subset(LightStrip* strip, LightStrip* subset)
{
    subset->lights = strip->lights;
    subset->num_lights = 12;
} 

void get_top_subset(LightStrip* strip, LightStrip* subset)
{
    subset->lights = strip->lights+12;
    subset->num_lights = 8;
} 

/**************************************************
 *		 Helper Functions		  *
 * *************************************************/

void send_next_light(Light* light)
{
    unsigned char enable = 0x80;

    SPI_MasterTransmit(enable | (*light).green);
    SPI_MasterTransmit(enable | (*light).red);
    SPI_MasterTransmit(enable | (*light).blue);
}

void send_end_of_sequence()
{
    char zero = 0x00;
    int i;
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

void SPI_MasterTransmit(unsigned char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    // There is an interrupt bit that can be set.
    // We can use this if we want to free up the processor
    while(!(SPSR & (1<<SPIF)))
    {}
}

