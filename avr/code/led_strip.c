#include <stdlib.h>
#include <avr/io.h>

#include "definitions.h"
#include "led_strip.h"


/**************************************************
 *		   LED Strip API		  *
 **************************************************/

void init_led_strip(LightStrip* strip, size_t length)
{
    if (strip == 0)
    {
       	// throw error
	return;
    }


    SPI_MasterInit();

    strip->lights = (Light*) malloc( length * sizeof(Light));

    if (strip->lights == 0)
    {
	// error allocating memory.
	// we should do something to alert the user
    }
    else
    {
	strip->num_lights = length;

	int i;
	for (i=0; i<strip->num_lights; ++i)
	    set_led_color(strip, i, 0, 0, 0);
    }
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

	return out;
}

void rainbow(LightStrip* strip, unsigned int counter)
{
	const unsigned int cycle_length = 384;
    size_t num_lights = strip->num_lights;
    unsigned int c = counter % cycle_length;

    unsigned int offset_per_light = cycle_length / num_lights;
    
    size_t i;
	for (i=0; i<num_lights; ++i)
	{
		unsigned int cycle_position = (((cycle_length * i) / num_lights) + c) % cycle_length;

		strip->lights[i].red   = get_brightness(cycle_position); 
		strip->lights[i].green = get_brightness((cycle_position + 128)%384); 
		strip->lights[i].blue  = get_brightness((cycle_position + 256)%384); 
	}
}


/**************************************************
 *		 Helper Functions		  *
 **************************************************/

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

    /* Enable SPI, Master, set clock rate fck/4444 */
    SPCR =  (1<<SPE)	| // SPI Enable
	    //(1<<DORD)	| // Reverse data order
	    (1<<MSTR)	| // SPI Master mode
	   //(1<<CPOL)	| // Reverse the clock polarity
	   //(1<<SPR1)	| // Sets the spi clock frequency
	   (1<<SPR0)	; // Sets the spi clock frequency

	SPSR |= (1<<SPI2X); // Run the SPI twice as fast
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

