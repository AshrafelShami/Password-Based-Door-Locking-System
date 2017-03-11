
#ifndef KEYPAD_COMFIG_H_
#define KEYPAD_COMFIG_H_

#include "../Prototypes/Keypad_Prototypes.h"
#include <avr/io.h>

vu8* ROW_Port;
vu8* LINE_Port;

u8 R0;
u8 R1;
u8 R2;
u8 R3;

u8 L0;
u8 L1;
u8 L2;
u8 L3;

#define Check_ALL_Lines		 (((*LINE_Port & (1U << L0)) >> L0)\
                                 &((*LINE_Port & (1U << L1)) >> L1)\
                                 &((*LINE_Port & (1U << L2)) >> L2)\
                                 &((*LINE_Port & (1U << L3)) >> L3))

#endif /* KEYPAD_COMFIG_H_ */
