#include "Keypad_Comfig.h"

/*...........................................................................
  Name:     Keypad_Init.
  Purpose:  Initialization function for Keypad.
  Entry:    no parameters
  Exit:     no parameters
*/

void Keypad_Init( vu8* R_PORT, vu8* L_PORT,
				   u8 ROW0, u8 ROW1, u8 ROW2, u8 ROW3,
				   u8 LIN0, u8 LIN1, u8 LIN2, u8 LIN3){
	ROW_Port	= R_PORT;	R0 = ROW0;	R1 = ROW1;	R2 = ROW2;	R3 = ROW3;
	LINE_Port	= L_PORT;	L0 = LIN0;	L1 = LIN1;	L2 = LIN2;	L3 = LIN3;

	/*	Set all Row pins to output	*/
	(* (ROW_Port + 1)) |= (1U << R0);
	(* (ROW_Port + 1)) |= (1U << R1);
	(* (ROW_Port + 1)) |= (1U << R2);
	(* (ROW_Port + 1)) |= (1U << R3);
	
	/*	Set all Line pins to input	*/
	(* (LINE_Port + 1)) &=~(1U << L0);
	(* (LINE_Port + 1)) &=~(1U << L1);
	(* (LINE_Port + 1)) &=~(1U << L2);
	(* (LINE_Port + 1)) &=~(1U << L3);
	
	/*	Activate the pull-up resistor of the input to drive them high	*/
	(* (LINE_Port + 2)) |= (1U << L0);
	(* (LINE_Port + 2)) |= (1U << L1);
	(* (LINE_Port + 2)) |= (1U << L2);
	(* (LINE_Port + 2)) |= (1U << L3);
}

/*...........................................................................
  Name:     Keypad_Scan.
  Purpose:  Scan the keypad Pins and determine the output.
  Entry:    no parameters
  Exit:     (u8) The value of pressed key in ascii.
*/
u8 Keypad_Scan ( void ){
	u8 ROW		= 0;
	u8 Input	= 0;
	
	for(ROW = 0; ROW < 4; ROW++){
		/*	Set all Row pins to High	*/
		(* (ROW_Port + 2)) |= (1U << R0);
		(* (ROW_Port + 2)) |= (1U << R1);
		(* (ROW_Port + 2)) |= (1U << R2);
		(* (ROW_Port + 2)) |= (1U << R3);
		
		/*	Switch on Row pins and drive them low one by one	*/
		switch (ROW){
			case 0	: (* (ROW_Port + 2)) &=~(1U << R0); break;
			case 1	: (* (ROW_Port + 2)) &=~(1U << R1); break;
			case 2	: (* (ROW_Port + 2)) &=~(1U << R2); break;
			default	: (* (ROW_Port + 2)) &=~(1U << R3); break;
		}
		
		/*	Read the input	
		 *	input = 0b01110000   0x70
		 *	input = 0b10110000   0xB0
		 *	input = 0b11010000   0xD0
		 *	input = 0b11100000   0xE0
		 */
		Input  = (((*LINE_Port & (1U << L0)) >> L0) << 4);
		Input |= (((*LINE_Port & (1U << L1)) >> L1) << 5);
		Input |= (((*LINE_Port & (1U << L2)) >> L2) << 6);
		Input |= (((*LINE_Port & (1U << L3)) >> L3) << 7);
		
		/*	Check if there is valid input	*/
		if (Check_ALL_Lines != 1){
			/*	Wait until release	*/
			while (Check_ALL_Lines != 1); break;
		}
	}
	
	/*	Return the output based on number of Row and Input's value	*/
	switch (ROW){
		case 0 : switch(Input){
			case 0xE0: return '7';
			case 0xD0: return '8';
			case 0xB0: return '9';
			case 0x70: return '<';
		}
		case 1 : switch(Input){
			case 0xE0: return '4';
			case 0xD0: return '5';
			case 0xB0: return '6';
			case 0x70: return '>';
		}
		case 2 : switch(Input){
			case 0xE0: return '1';
			case 0xD0: return '2';
			case 0xB0: return '3';
			case 0x70: return 'D';
		}
		case 3 : switch(Input){
			case 0xE0: return 'C';
			case 0xD0: return '0';
			case 0xB0: return '=';
			case 0x70: return '+';
		}
	}
	/*	If you didn't press any key it will return Zero	*/
	return 0;
}