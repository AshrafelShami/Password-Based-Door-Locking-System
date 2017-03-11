#include "Password_Config.h"
#include "../Prototypes/Keypad_Prototypes.h"
#include "../Prototypes/LCD_Prototypes.h"

u8 Password_List [9][4] =  {{'1','1','1','1'}, {'2','2','2','2'}, {'3','3','3','3'},
							{'4','4','4','4'}, {'5','5','5','5'}, {'6','6','6','6'},
							{'7','7','7','7'}, {'8','8','8','8'}, {'9','9','9','9'}};

u8 User_Login_Date[16] = {0};
u8 Password  [4] = {0};
extern u8 RTC_Time [];
extern u8 RTC_Date [];

/********************************************************************************************
Name:     Password_Enter.
Purpose:  Function to Allow the user to Enter his password (4 character size).
Entry:    No parameters.
Exit:     No parameters.
********************************************************************************************/
u8* Password_Enter ( void ){
	LCD_MENU_PW();
	u8 Keypad_Read;
	u8 i = 0, j = 0, k = 0;
	LCD_GOTO(1, 0);
	while (i <= 4){
		Keypad_Read = 0;
		while(Keypad_Read == 0)
		Keypad_Read = Keypad_Scan();
		if (i == 4){
			switch (Keypad_Read){
				case 'C' : LCD_MENU_PW(); i = 0; break;
				case 'D' : LCD_Clear_Pixel(1, --i); break;
				case '=' : for(j = 0; j < 9; j++){
					for(k = 0; k < 4; k++){
						if( Password[k]   == Password_List [j][k]   &&
							Password[k+1] == Password_List [j][k+1] &&
							Password[k+2] == Password_List [j][k+2] &&
							Password[k+3] == Password_List [j][k+3] ){
							LED_Green_On;
							LCD_Clear();
							LCD_Print(0, 0, "LOGIN SUCCESS");
							_delay_ms(500);
							LED_Green_OFF;
							return Password;
						}
					}
				}
				LED_Red_On;
				LCD_Clear();
				LCD_Print(0, 0, "LOGIN Failed");
				_delay_ms(500);
				LED_Red_OFF;
				return Password;
			}
		}
		else{
			switch(Keypad_Read){
				case 'C': i = 0; LCD_MENU_PW();	break;
				case 'D': switch(i){
					case 0 : break;
					case 1 : LCD_MENU_PW(); i = 0; break;
					default: LCD_Clear_Pixel(1, --i); break;
				}break;
				default	:{
					Password[i] = Keypad_Read;
					LCD_Char(Keypad_Read);
					LCD_GOTO(1, i++);
					_delay_ms(100);
					LCD_Char('*');
					break;
				}
			}
		}
	}
	return 0;
}

/********************************************************************************************
Name:     User_Login.
Purpose:  Function used to get Users Password, Time and Date to save it in the EEPROM.
Entry:    No parameters.
Exit:     No parameters.
********************************************************************************************/
void User_Login ( void ){
	u8 i = 0;
	for(i = 0; i < 4; i++)
	User_Login_Date[i] = Password[i];
	for(i = 0; i < 6; i++)
	User_Login_Date[i+4] = RTC_Time[i];
	for(i = 0; i < 6; i++)
	User_Login_Date[i+10] = RTC_Date[i];
}