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

void init_led_strip();
void led_strip_standby();
void led_strip_fire(unsigned int time);
void led_strip_update();

void set_led_color(LightStrip* strip, size_t index, unsigned char red, unsigned char green, unsigned char blue);

void Write_To_Led_Strip(LightStrip* lights);


/**************************************************
 *		  Color Paterns			  *
 **************************************************/

void rainbow(LightStrip* strip, unsigned int counter, unsigned int spread);
void mod_rainbow(LightStrip* strip, unsigned int counter);
void fill(LightStrip* strip, unsigned int counter, unsigned int total, Light mimic);
void drain(LightStrip* strip, unsigned int counter, unsigned int total, Light mimic);

/**************************************************
 *		  Color Patern Helpers	  *
 *************************p*************************/

void set_left(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue);
void set_front(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue);
void set_right(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue);
void set_base(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue);
void set_top(LightStrip* strip, unsigned char red, unsigned char green, unsigned char blue);

void get_base_subset(LightStrip* strip, LightStrip* subset);
void get_top_subset(LightStrip* strip, LightStrip* subset);

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

