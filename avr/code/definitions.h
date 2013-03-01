#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

/**************************************************
 *			  # Defines (ATMega328p)			  *
 **************************************************/

#define F_CPU 8000000
#define BAUD 9000


#define DDR_SPI DDRB
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK	5

#define DDR_PWM DDRD


#define bool char
#define FALSE 0
#define TRUE 1

#define SUCCESS 0
#define FAILURE 1

#endif
