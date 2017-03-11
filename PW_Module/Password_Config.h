
#ifndef PASSWORD_CONFIG_H_
#define PASSWORD_CONFIG_H_
#include "../Prototypes/Password_Prototypes.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#include <util/delay.h>
#endif

#include <avr/io.h>
#define LED_Green_On	PORTB |= (1U << 2)
#define LED_Green_OFF	PORTB &=~(1U << 2)
#define LED_Red_On		PORTB |= (1U << 5)
#define LED_Red_OFF		PORTB &=~(1U << 5)

#endif /* PASSWORD_CONFIG_H_ */