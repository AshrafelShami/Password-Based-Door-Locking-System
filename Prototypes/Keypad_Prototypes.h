
#ifndef FUNCTIONPROTOTYPES_H_
#define FUNCTIONPROTOTYPES_H_
#include "../Datatypes/DataTypes.h"

void Keypad_Init(vu8* ROW, vu8* LINE,
u8 ROW0, u8 ROW1, u8 ROW2, u8 ROW3,
u8 LIN0, u8 LIN1, u8 LIN2, u8 LIN3);

u8 Keypad_Scan  ( void );

#endif /* FUNCTIONPROTOTYPES_H_ */