#include "communication.h"
#include <avr/io.h>

#define bool char
#define false 0
#define true 1


// Constants
#define RECEIVE_BUFFER_LENGTH 10
static const char DATA_TYPE_MASK = 0x80;
static const char HEADER_FOOTER_MASK = 0x40;
static const char ADDRESS_MASK = 0x40;


// Global Data
static bool	receiving_data = false;
static int  receive_buffer[RECEIVE_BUFFER_LENGTH];
static int received_bytes = 0;
static char checksum;
static char my_address = 0;
volatile bool communication_ready_flag = false;

/**************************************************
 *						API						  *
 **************************************************/

void initialize_communication()
{
	// disable the power saving register for the usart
	PRR &= !(1<<PRUSART0 );

	// Enable the receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// Set the buad rate
	// assuming 8 MHz Fosc, and 9600 baud
	UBRR0H = 0;
	UBRR0L = 51;
}

void set_my_address(char address)
{
	my_address = address;
}

char ready_to_process_incomming_data()
{
	return communication_ready_flag; 
}

/**************************************************
 *					ISRs						  *
 **************************************************/

void byte_receive_ISR()
{
	// store the byte from the receive buffer 
	char data = 0; // = Register where the received byte is

	if (data & DATA_TYPE_MASK) // Control Data
	{
		if (data & HEADER_FOOTER_MASK) // Footer byte
		{
			if (receiving_data)	// This is the end of the nodes packet. Add byte to buffer and set the "ready" flag
			{
				// Add byte to the buffer
				receive_buffer[received_bytes];
				++received_bytes;

				// Reset the recieveing data flag
				receiving_data = false;

				// Set the ready flag	
				communication_ready_flag = true;
			}
			else // Pass the byte along
			{
				// TODO: send the byte to the output buffer
			}
		}
		else // Header byte
		{
			char address = data & ADDRESS_MASK;
			if ((address == my_address) || (address == 0)) // Node needs to save this data
			{
				// TODO: we need to talk about what happens if we get another packet before we handle the first one. 
				communication_ready_flag = false;

				// reset the received byte count and set receiving data flag
				received_bytes = 0;
				receiving_data = true;

				// Add byte to the buffer
				receive_buffer[received_bytes];
				++received_bytes;
			}
			else // pass the header through 
			{
				// TODO: send header to output
			}
		}
	}
	else // Payload Data
	{
		if (receiving_data)	// Store the data
		{
			receive_buffer[received_bytes];
			++received_bytes;
		}
		else //
		{
			// TODO: send header to output
		}
	}
}

void transmit_byte(char data)
{
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0) ) ) {}

	/* Put data into buffer, this sends the data */
	UDR0 = data;
}



