#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**************************************************
 *						API						  *
 **************************************************/
void initialize_communication();
void set_my_address(unsigned char address);

bool Process_Incomming_Data_If_Available();
void Transmit_Data_If_Available();

void blocking_transmit_byte(unsigned char data);
unsigned char blocking_receive_byte();

void Add_To_Personal_Out_Buffer(unsigned char data);
void Set_Personal_Out_Buffer_Ready_To_Write();
void Load_Personal_Out_Buffer_Into_Transmit_Buffer_If_Ready();

void Send_Response_Byte(unsigned char data);

#endif

