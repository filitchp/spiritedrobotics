#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**************************************************
 *					ISRs						  *
 **************************************************/
void byte_receive_ISR();

/**************************************************
 *				Administrative Functions		  *
 **************************************************/
void initialize_communication();
void set_my_address(char address);

#endif

