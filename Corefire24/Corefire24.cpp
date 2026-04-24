// Corefire24.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
C++ 20 
Windows 10/11 minimum OS Version
x64-bit
*/

/////////////////////////////////////////////////////
#include "BaseClass.h"

int main() {
	/* Main Menu & Program Start*/
	cfc::Startscreen function;

	while (!function.check_if_ExitRequested()) {
		switch (function.mainMenuLogic())
		{
		case 6: function.menuTheme(/*enum*/defaultTheme); break;
		case 7: function.menuTheme(/*enum*/RandomTheme); break;
		case 8: function.menuTheme(/*enum*/RainbowTheme); break;
		default: function.pause("\a\nInvalid Input\n", function.getMainMenuState().at(/*enum eMainMenu_State_ID*/ErrorMessage));
			break;
		}
	}
	return 0;
}