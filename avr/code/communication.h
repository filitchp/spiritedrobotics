#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**************************************************
 *						API						  *
 **************************************************/
void initialize_communication();
void set_my_address(unsigned char address);
bool ready_to_process_incomming_data();
bool process_incomming_data();

void Transmit_Data_If_Available();

void blocking_transmit_byte(unsigned char data);
unsigned char blocking_receive_byte();

#endif

