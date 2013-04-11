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
	LIGHT_PATTERN_ALL_RED	= 0x00,
	LIGHT_PATTERN_ALL_GREEN = 0x01,
	LIGHT_PATTERN_ALL_BLUE	= 0x02,
	LIGHT_PATTERN_ALL_OFF	= 0x03,
	LIGHT_PATTERN_DRAIN		= 0x04,
	LIGHT_PATTERN_FILL_TOWERS_INCREMENTALLY = 0x05,
	LIGHT_PATTERN_INVALID	= 0xFF
} e_LIGHT_PATTERN;

typedef struct LIGHT_PATTERN_FILL_TOWERS_INCREMENTALLY_STRUCT
{
	
} LIGHT_PATTERN_FILL_TOWERS_INCREMENTALLY_DATA;

/**************************************************
 *		   LED Strip API		  *
 **************************************************/

void init_led_strip();
void led_strip_standby();
void led_strip_fire(uint16_t time);
void led_strip_update();

void led_set_current_pattern(e_LIGHT_PATTERN targetPattern);

void set_led_color(LIGHTSTRIP* strip, size_t index, uint8_t red, uint8_t green, uint8_t blue);

void write_to_led_strip(LIGHTSTRIP* lights);


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

void set_left_led_colors(LIGHTSTRIP* strip, uint8_t red_color_brightness, uint8_t green_color_brightness, uint8_t blue_color_brightness);
void set_front_led_colors(LIGHTSTRIP* strip, uint8_t red_color_brightness, uint8_t green_color_brightness, uint8_t blue_color_brightness);
void set_right_led_colors(LIGHTSTRIP* strip, uint8_t red_color_brightness, uint8_t green_color_brightness, uint8_t blue_color_brightness);
void set_base_led_colors(LIGHTSTRIP* strip, uint8_t red_color_brightness, uint8_t green_color_brightness, uint8_t blue_color_brightness);
void set_top_led_colors(LIGHTSTRIP* strip, uint8_t red_color_brightness, uint8_t green_color_brightness, uint8_t blue_color_brightness);
void set_all_led_colors(LIGHTSTRIP* strip, uint8_t red_color_brightness, uint8_t green_color_brightness, uint8_t blue_color_brightness);
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

