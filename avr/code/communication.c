#include "definitions.h"
#include <util/setbaud.h>
#include "communication.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "circ_buff.h"




// Constants
#define RECEIVE_BUFFER_LENGTH 16
#define PERSONAL_OUTPUT_BUFFER_LENGTH 16

static const char DATA_TYPE_MASK = 0x80;
static const char HEADER_FOOTER_MASK = 0x40;
static const char ADDRESS_MASK = 0x3F;
static const char COMMAND_TYPE_MASK = 0x40;
static const char COMMAND_MASK = 0x3F;


// Global Data
static unsigned char my_address = 0;
	// Receiveing data
static unsigned char receive_buffer[RECEIVE_BUFFER_LENGTH];
static bool	receiving_data = FALSE;
static int received_bytes = 0;
volatile bool incomming_data_ready_for_processing = FALSE;

	// Output buffer
static CircBuff output_buff;
static bool can_load_new_packet_into_output_buffer = TRUE;
static char checksum = 0;

	// Personal output buffer
static unsigned char personal_output_buffer[PERSONAL_OUTPUT_BUFFER_LENGTH];
static unsigned char personal_output_buffer_bytes = 0;
static bool personal_out_buffer_ready_to_write = FALSE;



/**************************************************
 *						API						  *
 **************************************************/

void initialize_communication()
{
	// disable the power saving register for the usart
	PRR &= !(1<<PRUSART0);

	// Enable the receiver and transmitter
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	
	// Enable the receiver interrupt 
	UCSR0B |= (1<<RXCIE0);

	// Set the buad rate (defined in definitions.h)

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~(1 << U2X0);
#endif

	Init_Reset_CircBuff(&output_buff);
}

void set_my_address(unsigned char address)
{
	my_address = address;
}

bool ready_to_process_incomming_data()
{
	return incomming_data_ready_for_processing; 
}

char process_incomming_data()
{

	if (!incomming_data_ready_for_processing) { return 1; }
	else { incomming_data_ready_for_processing = FALSE; }

	if (received_bytes < 3) { return 1; }

	// TODO: REmove this. it's for testing only
	PORTB |= (1<<2);
	
	if (receive_buffer[1] & COMMAND_TYPE_MASK) // Node specific commands
	{
		blocking_transmit_byte(receive_buffer[1]);

		// TODO: REmove this. it's for testing only
		PORTB |= (1<<1);

		if (receive_buffer[1] == 0x40)
		{
			// TODO: REmove this. it's for testing only
			PORTB |= (1<<0);
		}
		switch((receive_buffer[1] & COMMAND_MASK))
		{
			case 0: // Pour drink
				if (received_bytes != 4)
					return 1;

				// TODO: REmove this. it's for testing only
				PORTB |= (1<<0);


				break;
		}
	}
	else // Generic Commands
	{
	}

	return 0;
}



void Transmit_Data_If_Available()
{
	if (personal_out_buffer_ready_to_write && can_load_new_packet_into_output_buffer)
	{
		// enqueue personal buffer onto output buffer
	}

	// Check for data in buffer AND empty transmit buffer	
	if ( (output_buff.count != 0) && (UCSR0A & (1<<UDRE0) ) )
	{
		unsigned char data = 0;
		if(Dequeue_Value(&output_buff, &data) == FAILURE) { return; }

		// Put data into buffer, this sends the data
		UDR0 = data;
	}
}


void blocking_transmit_byte(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0) ) ) {}

	/* Put data into buffer, this sends the data */
	UDR0 = data;
}

unsigned char blocking_receive_byte()
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) ) {}

	/* Get and return received data from buffer */
	return UDR0;
}

/**************************************************
 *					ISRs						  *
 **************************************************/

ISR(USART_RX_vect)
{

	// store the byte from the receive buffer 
	unsigned char data = UDR0;

	if (data & DATA_TYPE_MASK) // Control Data
	{
		if (data & HEADER_FOOTER_MASK) // Footer byte
		{
			if (receiving_data)	// This is the end of the nodes packet. Add byte to buffer and set the "ready" flag
			{
				// Add byte to the buffer
				receive_buffer[received_bytes] = data;
				++received_bytes;

				// Reset the recieveing data flag
				receiving_data = FALSE;

				// Set the ready flag	
				incomming_data_ready_for_processing = TRUE;


			}
			else // Pass the byte along
			{
				Enqueue_Value(&output_buff, data);
				can_load_new_packet_into_output_buffer = TRUE;
			}
		}
		else // Header byte
		{
			char address = data & ADDRESS_MASK;
			if ((address == my_address) || (address == 0)) // Node needs to save this data
			{
				// TODO: we need to talk about what happens if we get another packet before we handle the first one. 
				incomming_data_ready_for_processing = FALSE;


				// reset the received byte count and set receiving data flag
				received_bytes = 0;
				receiving_data = TRUE;

				// Add byte to the buffer
				receive_buffer[received_bytes] = data;
				++received_bytes;
			}
			else // pass the header through 
			{
				can_load_new_packet_into_output_buffer = FALSE;
				Enqueue_Value(&output_buff, data);
			}
		}
	}
	else // Payload Data
	{
		if (receiving_data)	// Store the data
		{
			receive_buffer[received_bytes] = data;
			++received_bytes;
		}
		else // Pass the data to the output
		{
			Enqueue_Value(&output_buff, data);
		}
	}
}


