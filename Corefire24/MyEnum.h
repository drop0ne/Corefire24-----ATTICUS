#pragma once

enum eConsoleTextColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    DefaultWhite = 7,
    Gray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    BrightWhite = 15,
};

enum eFLAG_ThemeID {
	defaultTheme = 0, RandomTheme = 1, RainbowTheme = 2, betterRandomTheme = 3
};  

enum eMainMenu_State_ID {
	Option = 0, ProgramID = 1, Program = 2, ExitProgramID = 3, ExitProgram = 4, Symbols = 5, ErrorMessage = 6, WAIT_ = 7
};

enum eGameOption {
    quiz = 0, numberGame = 1, hangman = 2, solitaire = 3
};

enum eAppsOption {
    CannaCalc = 0, PowerLossCalc = 1
};
/* 
enum dosINTcolors {
    default_color = 7, black = 0, dark_green = 2, green = 2, bright_green = 10, blue = 1,
    bright_red = 12, red = 4, light_blue = 3, ice_blue = 9, teal_blue = 11,
    white = 7, bright_white = 15, gray = 8, purple = 5, yellow = 6,
    highlight_with_blue_blue = 19, highlight_with_blue_blue2 = 25,
    highlight_blue_white = 23, check = 27
};
*/