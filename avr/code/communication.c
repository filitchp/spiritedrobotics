#include "definitions.h"
#include <util/setbaud.h>
#include "communication.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "circ_buff.h"
#include "motor_driver.h"
#include "led_strip.h"



// Constants
#define RECEIVE_BUFFER_LENGTH 16
#define PERSONAL_OUTPUT_BUFFER_LENGTH 16

static const unsigned char MASK_DATA_TYPE = 0x80;
static const unsigned char MASK_HEADER_FOOTER = 0x40;
static const unsigned char MASK_ADDRESS = 0x3F;
static const unsigned char MASK_COMMAND_TYPE = 0x40;


// Packet Stuff
static const unsigned char HEADER_ALL = 0x80;
static const unsigned char HEADER_MASTER = 0xBF;
static const unsigned char FOOTER  = 0xCF;

// Error Codes
static const unsigned char RESPONSE_OK  = 0x3F;

// Generic Commands
#define COMMAND_E_STOP 0x01
#define COMMAND_REASSIGN_ADDRESS 0x02

// Tower Commands
#define COMMAND_POUR_DRINK 0x40
#define COMMAND_SET_POUR_PWM 0x41
#define COMMAND_SET_REVERSING_TIME 0x42
#define COMMAND_SET_REVERSING_PWM 0x43
#define COMMAND_RESET_ERROR_LIGHT 0x44

// Responses
#define RESPONSE_SUCCESS 0xFE
#define RESPONSE_FAILURE 0xFF



// Receiveing data
static unsigned char my_address = 0;
static unsigned char receive_buffer[RECEIVE_BUFFER_LENGTH];
static bool	receiving_data = FALSE;
static int received_bytes = 0;
volatile bool incomming_data_ready_for_processing = FALSE;

// Output buffer
static CircBuff output_buff;
static bool can_load_new_packet_into_output_buffer = TRUE;
static unsigned char checksum = 0;

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

	UCSR0B &= ~(1<<UCSZ02);
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);


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

char Process_Incomming_Data_If_Available()
{
	if (!incomming_data_ready_for_processing) { return SUCCESS; }
	else { incomming_data_ready_for_processing = FALSE; } // reset flag

	if (received_bytes < 3) { return FAILURE; } // minimum number of bytes of a packet

	unsigned char	response_data[8];
	unsigned int	num_response_bytes = 0;

	bool addressed_to_all = (receive_buffer[0] == HEADER_ALL);
	bool success = SUCCESS;

	switch(receive_buffer[1])
	{
		case COMMAND_E_STOP:
			if (received_bytes != 3) { success = FAILURE; break; }

			Stop_Pouring();	

			break;

		case COMMAND_SET_POUR_PWM:
			if (received_bytes != 4) { success = FAILURE; break; }

			Set_Pour_Pwm(receive_buffer[2]);

			break;

		case COMMAND_SET_REVERSING_PWM:
			if (received_bytes != 4) { success = FAILURE; break; }

			Set_Reversing_Pwm(receive_buffer[2]);

			break;

		case COMMAND_SET_REVERSING_TIME:
			if (received_bytes != 4) { success = FAILURE; break; }

			unsigned int time_to_reverse = Calculate_Time(receive_buffer[2], receive_buffer[3]);
			Set_Reversing_Time(time_to_reverse);

			break;

		case COMMAND_POUR_DRINK: 
			if (received_bytes != 5) { success = FAILURE; break; }

			response_data[0] = receive_buffer[2];
			response_data[1] = receive_buffer[3];
			num_response_bytes = 2;

            unsigned int time = Calculate_Time(receive_buffer[2], receive_buffer[3]);

            Pour_Drink(time);
            led_strip_fire(time >> 2);

			break;

		case COMMAND_RESET_ERROR_LIGHT:
			if (received_bytes != 3) { success = FAILURE; break; }

			PORTB |= (1<<0);

			break;

		case COMMAND_REASSIGN_ADDRESS:
			if (received_bytes != 4) { success = FAILURE; break; }

			PORTB &= ~(1<<1);
			set_my_address(receive_buffer[2]);

			// If addressed to command, pass the packet along with address += 1
			receive_buffer[2] += 1;

			break;

		default:

			success = FAILURE;

			// don't pass the bad packet along
			addressed_to_all = FALSE;

			// set error light
			PORTB &= ~(1<<0);
			break;
	}

	// If addressed to all nodes, pass the packet along
	if (addressed_to_all)
	{
		int i;
		for (i = 0; i < received_bytes; ++i)
		{ Add_To_Personal_Out_Buffer(receive_buffer[i]); }
		Set_Personal_Out_Buffer_Ready_To_Write();
	}
	else // send a response byte
	{
		Add_To_Personal_Out_Buffer(HEADER_MASTER);

		unsigned char response_status = (success) ? RESPONSE_SUCCESS : RESPONSE_FAILURE;
		Add_To_Personal_Out_Buffer(response_status);
		Add_To_Personal_Out_Buffer(my_address);
		Add_To_Personal_Out_Buffer(receive_buffer[1]); // The command

		int i;
		for (i = 0; i < num_response_bytes; ++i)
		{ Add_To_Personal_Out_Buffer(response_data[i]); }

		Add_To_Personal_Out_Buffer(FOOTER);
		Set_Personal_Out_Buffer_Ready_To_Write();
	}

	return SUCCESS;
}



void Transmit_Data_If_Available()
{
	if (can_load_new_packet_into_output_buffer)
	{
		Load_Personal_Out_Buffer_Into_Transmit_Buffer_If_Ready();
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

	if (data & MASK_DATA_TYPE) // Control Data
	{
		if (data & MASK_HEADER_FOOTER) // Footer byte
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
			char address = data & MASK_ADDRESS;
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


void Add_To_Personal_Out_Buffer(unsigned char data)
{
	personal_out_buffer_ready_to_write = FALSE;
	personal_output_buffer[personal_output_buffer_bytes] = data;
	++personal_output_buffer_bytes;
}
void Set_Personal_Out_Buffer_Ready_To_Write()
{
	personal_out_buffer_ready_to_write = TRUE;
}


void Load_Personal_Out_Buffer_Into_Transmit_Buffer_If_Ready()
{
	if(personal_out_buffer_ready_to_write == FALSE) { return; }

	int i=0;
	for (i=0; i<personal_output_buffer_bytes; ++i)
	{
		Enqueue_Value(&output_buff, personal_output_buffer[i]);
	}	

	personal_output_buffer_bytes = 0;
	personal_out_buffer_ready_to_write = FALSE;
}


void Send_Response_Byte(unsigned char data)
{
	Add_To_Personal_Out_Buffer(HEADER_MASTER);
	Add_To_Personal_Out_Buffer(data);
	Add_To_Personal_Out_Buffer(my_address);
	Add_To_Personal_Out_Buffer(FOOTER);
	Set_Personal_Out_Buffer_Ready_To_Write();
}

void Send_Response_Bytes2(unsigned char data1, unsigned char data2)
{
	Add_To_Personal_Out_Buffer(HEADER_MASTER);
	Add_To_Personal_Out_Buffer(data1);
	Add_To_Personal_Out_Buffer(data2);
	Add_To_Personal_Out_Buffer(my_address);
	Add_To_Personal_Out_Buffer(FOOTER);
	Set_Personal_Out_Buffer_Ready_To_Write();
}

