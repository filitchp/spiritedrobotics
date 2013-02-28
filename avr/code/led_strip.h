#ifndef _LED_STRIP_H_
#define _LED_STRIP_H_

#include <stdlib.h>

/**************************************************
 *	     This code is designed to		  *
 *	     drive LPD8806 Led Strips		  *
 **************************************************/


/**************************************************
 *		   Led Structures		  *
 **************************************************/

typedef struct Light_Struct
{
    unsigned char red, green, blue;
} Light;

typedef struct Light_Strip_Struct
{
    int num_lights;
    Light* lights;
} LightStrip;


/**************************************************
 *		   LED Strip API		  *
 **************************************************/

void init_led_strip(LightStrip* strip, size_t length);

void set_led_color(LightStrip* strip, size_t index, unsigned char red, unsigned char green, unsigned char blue);

void Write_To_Led_Strip(LightStrip* lights);


/**************************************************
 *		  Color Paterns			  *
 **************************************************/

void rainbow(LightStrip* strip, unsigned int counter);


/**************************************************
 *		 Helper Functions		  *
 **************************************************/

void send_next_light(Light* light);

void send_end_of_sequence();


/**************************************************
 *		   SPI Driver Code		  *
 **************************************************/

void SPI_MasterInit(void);

void SPI_MasterTransmit(unsigned char cData);


#endif

