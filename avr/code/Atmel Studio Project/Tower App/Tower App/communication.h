#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**************************************************
 *						API						  *
 **************************************************/
void initialize_communication();
void set_my_address(uint8_t address);

bool Process_Incomming_Data_If_Available();
void Transmit_Data_If_Available();

void blocking_transmit_byte(uint8_t data);
uint8_t blocking_receive_byte();

void Add_To_Personal_Out_Buffer(uint8_t data);
void Set_Personal_Out_Buffer_Ready_To_Write();
void Load_Personal_Out_Buffer_Into_Transmit_Buffer_If_Ready();

void Send_Response_Byte(uint8_t data);
void Send_Response_Bytes2(uint8_t data1, uint8_t data2);

#endif

