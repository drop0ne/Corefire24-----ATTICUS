// Corefire24.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
C++ 20 
Windows 10/11 minimum OS Version
x64-bit
*/

/////////////////////////////////////////////////////
#include "BaseClass.h"
#include "MyGames.h"
#include "Solitaire.h"
#include "Hangman.h"

int main() {
	/* Main Menu & Program Start*/
	cfc::Startscreen function;

	while (!function.check_if_ExitRequested()) {
		switch (function.mainMenuLogic())
		{
		case 1: {
			auto CannaCalc_OBJ = std::make_unique<CannaCalculator>();
			CannaCalc_OBJ->run();
			break;
		}
		case 2: {
			auto calculatePowerLoss_OBJ = std::make_unique<CalculatePowerLoss_Watts_x_Meters>();
			calculatePowerLoss_OBJ->run();
			break;
		}
		case 3: {
			auto numberGuessingGame_OBJ = std::make_unique<NumberGuessingGame>();
			numberGuessingGame_OBJ->run();
			break;
		}
		case 4: {
			auto quize_OBJ = std::make_unique<Quiz>();
			quize_OBJ->run();
			break;
		}
		case 5: {
			auto hangman_OBJ = std::make_unique<Hangman>();
			hangman_OBJ->run();
			break;
		}
		case 6: function.menuTheme(/*enum*/defaultTheme); break;
		case 7: function.menuTheme(/*enum*/RandomTheme); break;
		case 8: function.menuTheme(/*enum*/RainbowTheme); break;
		case 9: {
			auto solitaire_OBJ = std::make_unique<Solitaire>();
			solitaire_OBJ->run();
			break;
		}
		default: function.pause("\a\nCommand must be intager from 1 - 9\n", function.getMainMenuState().at(/*enum eMainMenu_State_ID*/ErrorMessage));
			break;
		}
	}
	return 0;
}