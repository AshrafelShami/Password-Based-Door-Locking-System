#include "Menu_Config.h"
#include "../Prototypes/Keypad_Prototypes.h"
#include "../Prototypes/LCD_Prototypes.h"

u8 Menu ( void ){
	void (* LCD_Menus[4]) ( void );
	LCD_Menus[0] = LCD_MENU_Start;
	LCD_Menus[1] = LCD_MENU_Login;
	LCD_Menus[2] = LCD_MENU_Time;
	LCD_Menus[3] = LCD_MENU_Date;
	
	u8 i = 0;
	LCD_Menus[0]();
	
	while (1)
	{
		u8 Keypad_Read = Keypad_Scan();
		
		if (Keypad_Read != 0){
			if (Keypad_Read == '>')
				i++;
			else if(Keypad_Read == '<')
				i--;
			else if(Keypad_Read == '<' && i == 0)
				i = 0;
			else if (Keypad_Read == '=')
				return i;
			
			if (i > 3)
				i = 3;
			LCD_Menus[i]();
		}
	}
}