#ifndef _CIRC_BUFF_H_
#define _CIRC_BUFF_H_

#include "definitions.h"

#define BUFF_CAPACITY 64

typedef struct
{
	unsigned char buffer[BUFF_CAPACITY];
	unsigned char head;
	unsigned char tail;
	unsigned char count;
} CircBuff;


void Init_Reset_CircBuff(CircBuff* buff);
void Reset_CircBuff(CircBuff* buff);


bool Enqueue_Value(CircBuff* buff, unsigned char value);
bool Dequeue_Value(CircBuff* buff, unsigned char* value);

#endif

