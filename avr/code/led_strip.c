#include <stdlib.h>
#include <avr/io.h>

#include "pin_definitions.h"
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

void set_led_color(LightStrip* strip, size_t index, char red, char green, char blue)
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

char get_u_brightness(char max, float percent)
{
    while (percent > 1.0)
	percent -= 1.0;
    while (percent < 0)
	percent += 1.0;

    if (percent < one_third)
	return (char) (max * (-3*percent + 1));
    else if (percent < two_thirds)
	return 0;
    else
	return (char) (max * (3*(percent - two_thirds)));
}

void rainbow(LightStrip* strip, unsigned int counter, int cycle_length)
{
    int num_lights = strip->num_lights;
    int c = counter % cycle_length;

    int offset_per_light = cycle_length / num_lights;
    
    char max_brightness = 100;
    int i;
    for (i=0; i<num_lights; ++i)
    {
	int c = (counter + offset_per_light*i) % cycle_length;
	float cycle_percent = (float) c / (float) cycle_length;
	
	strip->lights[i].red   = get_u_brightness(max_brightness, cycle_percent); 
	strip->lights[i].green = get_u_brightness(max_brightness, cycle_percent + one_third); 
	strip->lights[i].blue  = get_u_brightness(max_brightness, cycle_percent + two_thirds); 

    }

}


/**************************************************
 *		 Helper Functions		  *
 **************************************************/

void send_next_light(Light* light)
{
    char enable = 0x80;

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
	    (1<<MSTR)	; // SPI Master mode
	   //(1<<CPOL)	| // Reverse the clock polarity
	   //(1<<SPR1)	| // Sets the spi clock frequency
	   //(1<<SPR0)	; // Sets the spi clock frequency
}

void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    // There is an interrupt bit that can be set.
    // We can use this if we want to free up the processor
    while(!(SPSR & (1<<SPIF)))
    {}
}

