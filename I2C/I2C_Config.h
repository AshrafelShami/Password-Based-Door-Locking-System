
#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include "../Prototypes/I2C_Prototypes.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>

typedef enum{
	SCL_10K		=	100000,
	SCL_100K	=	1000000,
	SCL_400K	=	4000000
	}SCL;
	
typedef enum{
	Enable,
	Disable
	}Interrupt;

typedef struct{
	SCL			SCL_Freq;
	Interrupt	Interrupt_Sel;
	}Struct_I2C;

void I2C_Init( Struct_I2C );

#endif /* I2C_CONFIG_H_ */