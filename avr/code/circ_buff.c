#include "circ_buff.h"

void Init_Reset_CircBuff(CircBuff* buff)
{
	buff->head = 0;
	buff->tail = 0;
	buff->count = 0;
}

bool Enqueue_Value(CircBuff* buff, unsigned char value)
{
	if (buff->count >= BUFF_CAPACITY - 1) { return FAILURE; }

	buff->buffer[buff->tail] = value; 
	buff->tail = (buff->tail + 1) % BUFF_CAPACITY;
	++buff->count;

	return SUCCESS;
}
bool Dequeue_Value(CircBuff* buff, unsigned char* value)
{
	if (buff->count == 0) { return FAILURE; }

	*value = buff->buffer[buff->head]; 
	buff->head = (buff->head + 1) % BUFF_CAPACITY;
	--buff->count;

	return SUCCESS;
}


