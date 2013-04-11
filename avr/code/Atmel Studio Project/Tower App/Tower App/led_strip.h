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
    uint8_t red, green, blue;
} LIGHT;

typedef struct Light_Strip_Struct
{
    int16_t num_lights;
    LIGHT* lights;
} LIGHTSTRIP;

typedef enum 
{
	LIGHT_PATTERN_0,
	LIGHT_PATTERN_1,
	LIGHT_PATTERN_2,
	LIGHT_PATTERN_3,
	LIGHT_PATTERN_DRAIN	
} e_LIGHT_PATTERN;


/**************************************************
 *		   LED Strip API		  *
 **************************************************/

void init_led_strip();
void led_strip_standby();
void led_strip_fire(uint16_t time);
void led_strip_update();

void set_led_color(LIGHTSTRIP* strip, size_t index, uint8_t red, uint8_t green, uint8_t blue);

void Write_To_Led_Strip(LIGHTSTRIP* lights);


/**************************************************
 *		  Color Paterns			  *
 **************************************************/

void rainbow(LIGHTSTRIP* strip, uint16_t counter, uint16_t spread);
void mod_rainbow(LIGHTSTRIP* strip, uint16_t counter);
void fill(LIGHTSTRIP* strip, uint16_t counter, uint16_t total, LIGHT mimic);
void drain(LIGHTSTRIP* strip, uint16_t counter, uint16_t total, LIGHT mimic);

/**************************************************
 *		  Color Patern Helpers	  *
 *************************p*************************/

void set_left(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue);
void set_front(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue);
void set_right(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue);
void set_base(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue);
void set_top(LIGHTSTRIP* strip, uint8_t red, uint8_t green, uint8_t blue);

void get_base_subset(LIGHTSTRIP* strip, LIGHTSTRIP* subset);
void get_top_subset(LIGHTSTRIP* strip, LIGHTSTRIP* subset);

/**************************************************
 *		 Helper Functions		  *
 **************************************************/

void send_next_light(LIGHT* light);

void send_end_of_sequence();


/**************************************************
 *		   SPI Driver Code		  *
 **************************************************/

void SPI_MasterInit(void);

void SPI_MasterTransmit(uint8_t cData);


#endif

