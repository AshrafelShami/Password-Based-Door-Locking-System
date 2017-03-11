#include "LCD_Config.h"
extern u8 RTC_Time[6];
extern u8 RTC_Date[6];

/********************************************************************************************
  Name:     LCD_Init.
  Purpose:  Initialize the LCD Control and Data ports and pins.
  Entry:    LCD_Init (&PIND, &PINC, 0, 1, 2, 3, 4, 5, 6)															
			|      |    |  |  |  |  |  |  |___________ Data_4 Pin.										
			|      |    |  |  |  |  |  |______________ Data_3 Pin.										
			|      |    |  |  |  |  |_________________ Data_2 Pin.										
			|      |    |  |  |  |____________________ Data_1 Pin.										
			|      |    |  |  |_______________________ Register Select Pin.							
			|      |    |  |__________________________ Read/Write Pin.									
			|      |    |_____________________________ Enable Pin.										
			|      |__________________________________ Address of Control Port.						
			|_________________________________________ Address of Data Port.
  Exit:     no parameters
********************************************************************************************/
void LCD_Init ( vu8* D_Port, vu8* C_Port, u8 E_Pin, u8 RW_Pin, u8 RS_Pin, u8 D1_Pin, u8 D2_Pin, u8 D3_Pin, u8 D4_Pin){
	Data = D_Port; Ctrl = C_Port;
	E    = E_Pin ; RW   = RW_Pin; RS   = RS_Pin;
	D1   = D1_Pin; D2   = D2_Pin; D3   = D3_Pin; D4   = D4_Pin;

	(* (Data + 1)) |= (1U << D1)|(1U << D2)|(1U << D3)|(1U << D4);		/*	Set Data pin's direction to output.	*/
	(* (Data + 2)) &=~((1U << D1)|(1U << D2)|(1U << D3)|(1U << D4));	/*	Set Port values of Data pins to Zero.	*/
	(* (Ctrl + 1)) |= (1U << E)|(1U << RS)|(1U << RW);			/*	Set Ctrl pin's direction to output.	*/
	(* (Ctrl + 2)) &=~((1U << E)|(1U << RS)|(1U << RW));			/*	Set Port values of Ctrl pins to Zero.	*/
	
	LCD_Command( 0x33 );		/*	Send 3, 3 (0x33), 3 then 2 (0x32) nibbles.		*/
	LCD_Command( 0x32 );
	LCD_Command( 0x28 );		/*	Configure the LCD 4-bit, 2 Lines and 5x7 Matrix.	*/
	LCD_Command( 0x06 );		/*	Shift cursor to right.					*/
	LCD_Command( 0x0C );		/*	Cursor ON.						*/
	LCD_Command( 0x01 );		/*	Clear Display and DDRAM content.			*/
}

/********************************************************************************************
  Name:     LCD_Command.
  Purpose:  Send a command to the LCD.
  Entry:    (Command) The command number.
  Exit:     no parameters
********************************************************************************************/
void LCD_Command ( u8 Command ){
	LCD_BasyFlag_Check();			/*	Check if the LCD is Busy			*/
	(* (Ctrl + 2)) &=~(1U << RS);		/*	RS = 0 (Write Command).				*/
	(* (Ctrl + 2)) &=~(1U << RW);		/*	RW = 0 (Write on the LCD).			*/
	LCD_Sync_Data_Pins ( Command );
}

/********************************************************************************************
  Name:     LCD_Char.
  Purpose:  Display data(Character) on the LCD.
  Entry:    (Character) The Character in ASCII.
  Exit:     no parameters
********************************************************************************************/
void LCD_Char ( u8 Character ){
	(* (Ctrl + 2)) |= (1U << RS);		/*	RS = 1 (Write Data).				*/
	(* (Ctrl + 2)) &=~(1U << RW);		/*	RW = 0 (Write on the LCD).			*/
	LCD_Sync_Data_Pins ( Character );	/*	Synchronize the Data pins of the LCD.		*/
}

/********************************************************************************************
  Name:     LCD_Print.
  Purpose:  display a string of characters on the LCD.
  Entry:    LCD_Print(0, 0, "Hello World")
		      |  |        |______________________________ Send the String.						
		      |  |_______________________________________ Position of Column on the LCD (0 ~ 15).
		      |__________________________________________ Position of Row    on the LCD (0 or 1).
  Exit:     no parameters
********************************************************************************************/
void LCD_Print (u8 Pos_X, u8 Pos_Y, char * word ){
	LCD_GOTO (Pos_X, Pos_Y);
	u8 i = 0;
	while (word[i] != '\0'){
		LCD_BasyFlag_Check();		/*	Check if the LCD is Busy		*/
		LCD_Char(word[i++]);
	}
}

/********************************************************************************************
  Name:     LCD_GOTO.
  Purpose:  Move the courser to a certain location on the LCD.
  Entry:    (GOTO_X) Position of courser on Row.
			(GOTO_Y) Position of courser on column.
  Exit:     no parameters
********************************************************************************************/
void LCD_GOTO ( u8 GOTO_X, u8 GOTO_Y ){
	if (GOTO_X == 0){
		LCD_Command( 0x80 + GOTO_Y);
	}
	else if (GOTO_X == 1){
		LCD_Command( 0xC0 + GOTO_Y);
	}
}

/********************************************************************************************
  Name:     LCD_Latch_Enable.
  Purpose:  Send a latch signal to the LCD.
  Entry:    no parameters
  Exit:     no parameters
********************************************************************************************/
void LCD_Latch_Enable ( void ){
	(* (Ctrl + 2)) |= (1U << E);		/*	Set Enable Pin to high			*/
	_delay_us(1);				/*	Wait for 1 us to form a Pulse		*/
	(* (Ctrl + 2)) &=~(1U << E);		/*	Set Enable Pin to Low			*/
	_delay_ms(1);
}

/********************************************************************************************
  Name:     LCD_Sync_Data_Pins.
  Purpose:  Synchronize the data pins of the LCD.
  Entry:    (value)
  Exit:     no parameters
********************************************************************************************/
void LCD_Sync_Data_Pins ( u8 value ){
	if (value & (1U << 7)) {(* (Data + 2)) |= (1U << D4);} else {(* (Data + 2)) &=~(1U << D4);}
	if (value & (1U << 6)) {(* (Data + 2)) |= (1U << D3);} else {(* (Data + 2)) &=~(1U << D3);}
	if (value & (1U << 5)) {(* (Data + 2)) |= (1U << D2);} else {(* (Data + 2)) &=~(1U << D2);}
	if (value & (1U << 4)) {(* (Data + 2)) |= (1U << D1);} else {(* (Data + 2)) &=~(1U << D1);}
		
	LCD_Latch_Enable ();			/*	Latch on Enable pin pulse High To Low.	*/
	
	if (value & (1U << 3)) {(* (Data + 2)) |= (1U << D4);} else {(* (Data + 2)) &=~(1U << D4);}
	if (value & (1U << 2)) {(* (Data + 2)) |= (1U << D3);} else {(* (Data + 2)) &=~(1U << D3);}
	if (value & (1U << 1)) {(* (Data + 2)) |= (1U << D2);} else {(* (Data + 2)) &=~(1U << D2);}
	if (value & (1U << 0)) {(* (Data + 2)) |= (1U << D1);} else {(* (Data + 2)) &=~(1U << D1);}
		
	LCD_Latch_Enable ();			/*	Latch on Enable pin pulse High To Low.	*/
}

/********************************************************************************************
  Name:     LCD_BasyFlag_Check.
  Purpose:  Check the status of the LCD if its busy or not.
  Entry:    no parameters.
  Exit:     no parameters.
********************************************************************************************/
void LCD_BasyFlag_Check( void ){
	u8 busy_flag;					/*  Busy flag.					*/
	(* (Data + 1)) &=~(1U << D4);			/*  set D7 data direction to input.		*/
	(* (Ctrl + 2)) &=~(1U << RS);			/*  select the Instruction Register (RS low).	*/
	(* (Ctrl + 2)) |= (1U << RW);			/*	RW = 0 (Read from the LCD).		*/

	do{
		busy_flag = 0;			    /*  initialize busy flag.							*/
		(* (Ctrl + 2)) |= (1U << E);        /*  Enable pin high.							*/
		_delay_us(1);                       /*  implement 'Delay data time' (160 nS) and 'Enable pulse width' (230 nS).	*/

		busy_flag |= (D4 & (1U << D4));	    /*  get actual busy flag status.											*/
		(* (Ctrl + 2)) &=~(1U << E);        /*  Enable pin low.															*/
		_delay_us(1);

		(* (Ctrl + 2)) |= (1U << E);	    /*  Enable pin high.							*/
		_delay_us(1);			    /*  implement 'Delay data time' (160 nS) and 'Enable pulse width' (230 nS).	*/
		(* (Ctrl + 2)) &=~(1U << E);	    /*  Enable pin low.								*/
		_delay_us(1);
	}while (busy_flag);		            /*  check again if busy flag was high.					*/
	(* (Ctrl + 2)) &=~(1U << RW);		    /*  write to LCD module (RW low).						*/
	(* (Data + 1)) |= (1U << D4);		    /*  reset D7 data direction to output.					*/
}

/********************************************************************************************
  Name:     LCD_Clear.
  Purpose:  Clear the LCD.
  Entry:    no parameters.
  Exit:     no parameters.
********************************************************************************************/
void LCD_Clear ( void ){
	LCD_Command( 0x01 );	/*	Clear Display and DDRAM content.		*/
}

/********************************************************************************************
  Name:     LCD_Clear_Pixel.
  Purpose:  Function used to Clear a pixel on the LCD.
  Entry:    (u8 X, u8 Y), The position of the pixel.
  Exit:     no parameters.
********************************************************************************************/
void LCD_Clear_Pixel( u8 X, u8 Y ){
	LCD_GOTO(X, Y);
	LCD_Char(' ');
	LCD_GOTO(X, Y);
}

/********************************************************************************************
  Name:     LCD_MENU_PW.
  Purpose:  Function used to Print password menu on the LCD.
  Entry:    no parameters.
  Exit:     no parameters.
********************************************************************************************/
void LCD_MENU_PW ( void ){
	LCD_Clear();
	LCD_Print(0, 0, "Enter Password");
	LCD_GOTO(1, 0);
}

/********************************************************************************************
  Name:     LCD_MENU_Start.
  Purpose:  Function used to Print Start menu on the LCD.
  Entry:    no parameters.
  Exit:     no parameters.
 ********************************************************************************************/
void LCD_MENU_Start ( void ){
	LCD_Clear();
	LCD_Print(0, 4,  "WELCOME");
	LCD_Print(1, 1,  "TO LOCK SYSTEM");
	LCD_Print(0, 14,  ">>");
}

/********************************************************************************************
  Name:     LCD_MENU_Login.
  Purpose:  Function used to Print Login menu on the LCD.
  Entry:    no parameters.
  Exit:     no parameters.
********************************************************************************************/
void LCD_MENU_Login ( void ){
	LCD_Clear();
	LCD_Print(0,  4, "SIGN IN");
	LCD_Print(1,  2, "PRESS ON '='");
	LCD_Print(0, 14, ">>");
	LCD_Print(0,  0, "<<");
}

/********************************************************************************************
  Name:     LCD_MENU_Time.
  Purpose:  Function used to Print Time menu on the LCD.
  Entry:    no parameters.
  Exit:     no parameters.
********************************************************************************************/
void LCD_MENU_Time ( void ){
	u8 i;
	LCD_Clear();
	LCD_Print(0, 6,  "Time");
	LCD_GOTO(1, 4);
	for(i = 0; i < 6; i++){
		LCD_Char(RTC_Time[i]);
		if(i == 1|| i == 3)
			LCD_Char(':');
	}
	LCD_Print(0, 14, ">>");
	LCD_Print(0, 0, "<<");
}

/********************************************************************************************
  Name:     LCD_MENU_Date.
  Purpose:  Function used to Print Date menu on the LCD.
  Entry:    no parameters.
  Exit:     no parameters.
********************************************************************************************/
void LCD_MENU_Date ( void ){
	u8 i;
	LCD_Clear();
	LCD_Print(0, 6,  "Date");
	LCD_GOTO(1, 4);
	for(i = 0; i < 6; i++){
		LCD_Char(RTC_Date[i]);
		if(i == 1|| i == 3)
			LCD_Char('/');
	}
	LCD_Print(0, 0, "<<");
}
