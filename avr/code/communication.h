#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**************************************************
 *					ISRs						  *
 **************************************************/
void byte_receive_ISR();

/**************************************************
 *						API						  *
 **************************************************/
void initialize_communication();
void set_my_address(char address);
char ready_to_process_incomming_data();

void blocking_transmit_byte(char data);

unsigned char blocking_receive_byte();

#endif

