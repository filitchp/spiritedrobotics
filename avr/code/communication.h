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

#endif

