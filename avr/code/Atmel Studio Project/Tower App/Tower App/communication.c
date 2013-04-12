#include "definitions.h"
#include <util/setbaud.h>
#include "communication.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "circ_buff.h"
#include "motor_driver.h"
#include "led_strip.h"

#warning "TODO: Use circular buffer to store incoming data, and count incoming packets. Move packets from circular buffer to dedicated buffer for processing."

// Constants
#define INCOMING_DATA_BUFFER_LENGTH 128
#define PERSONAL_OUTPUT_BUFFER_LENGTH 16

static const uint8_t MASK_CONTROL_DATA_TYPE = 0x80;
static const uint8_t MASK_FOOTER = 0x40; 
static const uint8_t MASK_ADDRESS = 0x3F;
static const uint8_t MASK_COMMAND_TYPE = 0x40;


// Packet Stuff
static const uint8_t HEADER_ALL = 0x80;
static const uint8_t HEADER_MASTER = 0xBF;
static const uint8_t FOOTER  = 0xCF;

// Error Codes
static const uint8_t RESPONSE_OK  = 0x3F;

// Generic Commands
#define COMMAND_E_STOP 0x01
#define COMMAND_REASSIGN_ADDRESS 0x02

// Tower Commands
#define COMMAND_POUR_DRINK 0x40
#define COMMAND_SET_POUR_PWM 0x41
#define COMMAND_SET_REVERSING_TIME 0x42
#define COMMAND_SET_REVERSING_PWM 0x43
#define COMMAND_RESET_ERROR_LIGHT 0x44
#define COMMAND_SET_LIGHT_PATTERN 0x45

// Responses
#define RESPONSE_SUCCESS 0xFE
#define RESPONSE_FAILURE 0xFF


// Receiving data
static uint8_t my_address = 0;
static uint8_t incoming_data_buffer[INCOMING_DATA_BUFFER_LENGTH];
static bool	receiving_data = false;
static int16_t received_bytes = 0;
volatile bool incomming_data_ready_for_processing = false;

uint8_t get_my_address()
{
	return my_address;
}



// Output buffer
static CircBuff output_buff;
static bool can_load_new_packet_into_output_buffer = true;
//static uint8_t checksum = 0;

// Personal output buffer
static uint8_t personal_output_buffer[PERSONAL_OUTPUT_BUFFER_LENGTH];
static uint8_t personal_output_buffer_bytes = 0;

static bool personal_out_buffer_ready_to_write = false;



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

void set_my_address(uint8_t address)
{
	my_address = address;
	
}

bool ready_to_process_incomming_data()
{
	return incomming_data_ready_for_processing; 
}

bool Process_Incomming_Data_If_Available()
{
	if (!incomming_data_ready_for_processing) //incoming data is not ready for processing
	{ 
		return SUCCESS;
	}
	else // we will now process the incoming data, reset the flag
	{ 
		incomming_data_ready_for_processing = false; 
	} 

	if (received_bytes < 3) // minimum number of bytes of a packet
	{ 
		return FAILURE; 
	} 

	uint8_t		response_data[8];
	uint16_t	num_response_bytes = 0;

	bool addressed_to_all = (incoming_data_buffer[0] == HEADER_ALL);
	bool packet_parse_result = SUCCESS;

	switch(incoming_data_buffer[1])
	{
		case COMMAND_E_STOP:
			if (received_bytes != 3) { packet_parse_result = FAILURE; break; }

			Stop_Pouring();	

			break;

		case COMMAND_SET_POUR_PWM:
			if (received_bytes != 4) { packet_parse_result = FAILURE; break; }

			Set_Pour_Pwm(( int16_t )(incoming_data_buffer[2]));

			break;

		case COMMAND_SET_REVERSING_PWM:
			if (received_bytes != 4) { packet_parse_result = FAILURE; break; }

			Set_Reversing_Pwm(( int16_t )(incoming_data_buffer[2])); // This is made negative in this function

			break;

		case COMMAND_SET_REVERSING_TIME:
			if (received_bytes != 5) { packet_parse_result = FAILURE; break; }

			uint16_t time_to_reverse = Calculate_Time(incoming_data_buffer[2], incoming_data_buffer[3]);
			Set_Reversing_Time(time_to_reverse);

			break;

		case COMMAND_POUR_DRINK: 
			if (received_bytes != 5) { packet_parse_result = FAILURE; break; }

			response_data[0] = incoming_data_buffer[2];
			response_data[1] = incoming_data_buffer[3];
			num_response_bytes = 2;

            uint16_t time = Calculate_Time(incoming_data_buffer[2], incoming_data_buffer[3]);

			led_set_pattern_firing(time);
            Pour_Drink(time);
			#warning "Deprecated Function Call to led_strip_fire"
            //led_strip_fire(time >> 2);

			break;

		case COMMAND_RESET_ERROR_LIGHT:
			if (received_bytes != 3) { packet_parse_result = FAILURE; break; }

			PORTB |= (1<<0);

			break;
		case COMMAND_SET_LIGHT_PATTERN:
			if (received_bytes != 4) { packet_parse_result = FAILURE; break; }
			
			led_set_current_pattern( (e_LIGHT_PATTERN) incoming_data_buffer[2]);
			
			break;
		case COMMAND_REASSIGN_ADDRESS:
			if (received_bytes != 4) { packet_parse_result = FAILURE; break; }

			PORTB &= ~(1<<1);
			set_my_address(incoming_data_buffer[2]);

			// If addressed to command, pass the packet along with address += 1
			incoming_data_buffer[2] += 1;

			break;
		default:

			packet_parse_result = FAILURE;

			// don't pass the bad packet along
			addressed_to_all = false;

			// set error light
			PORTB &= ~(1<<0);
			break;
	}

	// If addressed to all nodes, pass the packet along
	if (addressed_to_all)
	{
		 int16_t  i;
		for (i = 0; i < received_bytes; ++i)
		{ Add_To_Personal_Out_Buffer(incoming_data_buffer[i]); }
		Set_Personal_Out_Buffer_Ready_To_Write();
	}
	else // send a response byte
	{
		Add_To_Personal_Out_Buffer(HEADER_MASTER);

		uint8_t response_status = (packet_parse_result == FAILURE) ? RESPONSE_SUCCESS : RESPONSE_FAILURE;
		Add_To_Personal_Out_Buffer(response_status);
		Add_To_Personal_Out_Buffer(my_address);
		Add_To_Personal_Out_Buffer(incoming_data_buffer[1]); // The command

		 int16_t  i;
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
		uint8_t data = 0;
		if(Dequeue_Value(&output_buff, &data) == FAILURE) { return; }

		// Put data into buffer, this sends the data
		UDR0 = data;
	}
}

void blocking_transmit_byte(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0) ) ) {}

	/* Put data into buffer, this sends the data */
	UDR0 = data;
}

uint8_t blocking_receive_byte()
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
	uint8_t data = UDR0;

	if (data & MASK_CONTROL_DATA_TYPE) // Control Data
	{
		if (data & MASK_FOOTER) // Footer byte
		{
			if (receiving_data)	// This is the end of the nodes packet. Add byte to buffer and set the "ready" flag
			{
				// Add byte to the buffer
				incoming_data_buffer[received_bytes] = data;
				++received_bytes;

				// Reset the receiving data flag
				receiving_data = false;

				// Set the ready flag	
				incomming_data_ready_for_processing = true;
			}
			else // Pass the byte along
			{
				Enqueue_Value(&output_buff, data);
				can_load_new_packet_into_output_buffer = true;
			}
		}
		else // Header byte
		{
			uint8_t address = data & MASK_ADDRESS;
			if ((address == my_address) || (address == 0)) // Node needs to save this data
			{
				// TODO: we need to talk about what happens if we get another packet before we handle the first one. 
				incomming_data_ready_for_processing = false;


				// reset the received byte count and set receiving data flag
				received_bytes = 0;
				receiving_data = true;

				// Add byte to the buffer
				incoming_data_buffer[received_bytes] = data;
				++received_bytes;
			}
			else // pass the header through 
			{
				can_load_new_packet_into_output_buffer = false;
				Enqueue_Value(&output_buff, data);
			}
		}
	}
	else // Payload Data
	{
		if (receiving_data)	// Store the data
		{
			incoming_data_buffer[received_bytes] = data;
			++received_bytes;
		}
		else // Pass the data to the output
		{
			Enqueue_Value(&output_buff, data);
		}
	}
}

void Add_To_Personal_Out_Buffer(uint8_t data)
{
	personal_out_buffer_ready_to_write = false;
	personal_output_buffer[personal_output_buffer_bytes] = data;
	++personal_output_buffer_bytes;
}

void Set_Personal_Out_Buffer_Ready_To_Write()
{
	personal_out_buffer_ready_to_write = true;
}


void Load_Personal_Out_Buffer_Into_Transmit_Buffer_If_Ready()
{
	if(personal_out_buffer_ready_to_write == false) { return; }

	 int16_t  i=0;
	for (i=0; i<personal_output_buffer_bytes; ++i)
	{
		Enqueue_Value(&output_buff, personal_output_buffer[i]);
	}	

	personal_output_buffer_bytes = 0;
	personal_out_buffer_ready_to_write = false;
}


void Send_Response_Byte(uint8_t data)
{
	Add_To_Personal_Out_Buffer(HEADER_MASTER);
	Add_To_Personal_Out_Buffer(data);
	Add_To_Personal_Out_Buffer(my_address);
	Add_To_Personal_Out_Buffer(FOOTER);
	Set_Personal_Out_Buffer_Ready_To_Write();
}

void Send_Response_Bytes2(uint8_t data1, uint8_t data2)
{
	Add_To_Personal_Out_Buffer(HEADER_MASTER);
	Add_To_Personal_Out_Buffer(data1);
	Add_To_Personal_Out_Buffer(data2);
	Add_To_Personal_Out_Buffer(my_address);
	Add_To_Personal_Out_Buffer(FOOTER);
	Set_Personal_Out_Buffer_Ready_To_Write();
}

