#ifndef _CIRC_BUFF_H_
#define _CIRC_BUFF_H_

#include "definitions.h"

#define BUFF_CAPACITY 64

typedef struct
{
	uint8_t buffer[BUFF_CAPACITY];
	uint8_t head;
	uint8_t tail;
	uint8_t count;
} CircBuff;


void Init_Reset_CircBuff(CircBuff* buff);
void Reset_CircBuff(CircBuff* buff);


bool Enqueue_Value(CircBuff* buff, uint8_t value);
bool Dequeue_Value(CircBuff* buff, uint8_t* value);

#endif

