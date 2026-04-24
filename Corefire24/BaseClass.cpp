#include "BaseClass.h"

//************************************************************************************************************************************************************/
// MyConsoleAPI Class
// Constructor
/*************************************************************************************************************************************************************/
cfc::CoreComponents::CoreComponents() : console_HWND(), topLeft({ 0, 0 }) {
	console_HWND = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console_HWND == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("Failed to get standard output handle");
	}
}

//************************************************************************************************************************************************************/
// NumberGenerator
/*************************************************************************************************************************************************************/

cfc::NumberGenerator::NumberGenerator()
	: rd(),
	generator(rd())
{
}

cfc::NumberGenerator::~NumberGenerator() = default;

int cfc::NumberGenerator::getRandomNumber(const int min, const int max)
{
	if (min > max)
	{
		throw std::invalid_argument("NumberGenerator::getRandomNumber min cannot be greater than max");
	}

	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}


// Clear the console screen using Windows API for better performance and security
inline void cfc::CoreComponents::clearScreen() {
	COORD topLeft = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	if (!GetConsoleScreenBufferInfo(console_HWND, &screen)) {
		throw std::runtime_error("Failed to get console buffer info");
	}

	DWORD area = screen.dwSize.X * screen.dwSize.Y;
	if (!FillConsoleOutputCharacter(console_HWND, ' ', area, topLeft, &written) ||
		!FillConsoleOutputAttribute(console_HWND, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, area, topLeft, &written)) {
		throw std::runtime_error("Failed to clear console screen");
	}
	SetConsoleCursorPosition(console_HWND, topLeft);
}

inline void cfc::CoreComponents::pause() {
	print("\nPress enter to continue...", Gray, true);
	clearInputStream();
	std::cin.get();
}

inline void cfc::CoreComponents::pause(std::string& pauseMessage) {
	print(pauseMessage, Gray, true);
	clearInputStream();
	std::cin.get();
}

inline void cfc::CoreComponents::pause(const std::string& pauseMessage, const int textColor) {
	print(pauseMessage, textColor, true);
	clearInputStream();
	std::cin.get();
}

inline void cfc::CoreComponents::print(const std::string& data) {
	std::cout << data;
	// Base
}
inline void cfc::CoreComponents::print(const std::string& data, const bool& use_std_endl) {
	switch (use_std_endl)
	{
		case true:	std::cout << data << std::endl;	break;
		case false:	std::cout << data; break;
	}
}
inline void cfc::CoreComponents::print(const std::string& data, const int set_text_color, const bool& use_std_endl) {
	setTextColor(set_text_color);
	switch (use_std_endl)
	{
		case true:	std::cout << data << std::endl;	break;
		case false:	std::cout << data; break;
	}
}
inline void cfc::CoreComponents::print(const std::string& data, const int textColor) {
	setTextColor(textColor);
	std::cout << data;
	// Set text color and print data
}

inline void cfc::CoreComponents::print(const double& data, int numberColor) {
	setTextColor(numberColor);
	std::cout << data;
}

inline void cfc::CoreComponents::print(const std::string& string1, const double& data1, const std::string& string2, int& textColor, int& numberColor) {
	print(string1, textColor);
	print(data1, numberColor);
	print(string2, textColor);
	// Used by CalculatePowerLoss_Watts_x_Meters
}


inline void cfc::CoreComponents::print(const std::string& string1, const int& textColor1, const std::string& string2, const int& textColor2,
	const std::string& string3, const int& textColor3, const std::string& string4, const int& textColor4) {
	// Used to generate Main Menu
	print(string1, textColor1);
	print(string2, textColor2);
	print(string3, textColor3);
	print(string4, textColor4);
}

inline void cfc::CoreComponents::setScreenColor(const char* data) {
	try {
		// Validate the input before executing
		if (!check_IF_validCommand(data)) {
			throw std::invalid_argument("Invalid command for screen color.");
		}
		// Execute the system command
		int result = system(data);
		if (result != 0) { // Check system() return value
			throw std::runtime_error("Failed to execute system command.");
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

inline void cfc::CoreComponents::setTextColor(int data) {
	if (!SetConsoleTextAttribute(console_HWND, data)) {
		throw std::runtime_error("Failed to set text attributes");
	}
}

inline void cfc::CoreComponents::overrideConsoleColors(eConsoleTextColor foreground, eConsoleTextColor background) {
	WORD color = (static_cast<WORD>(background) << 4) | static_cast<WORD>(foreground);
	if (!SetConsoleTextAttribute(console_HWND, color)) {
		throw std::runtime_error("Failed to set text attributes");
	}
}

inline void cfc::CoreComponents::clearInputStream() {
	std::cin.clear();
	if (std::cin.rdbuf()->in_avail() > 0) {
		// If there are characters in the input buffer, discard them up to the next newline
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

inline void cfc::CoreComponents::extractInputStream() {
	std::cout << "Contents of input stream: ";
	char c;
	while (std::cin.peek() != EOF) {
		std::cin.get(c);
		std::cout << c;
	}
}

inline void cfc::CoreComponents::sleepTimer(int time) { std::this_thread::sleep_for(std::chrono::milliseconds(time)); }

// ********** Start Private Functions **********

inline bool cfc::CoreComponents::check_IF_validCommand(const char* command) {
	// List of allowed commands for setting screen colors, now including gray, these strings are known to be safe to pass to system()
	const std::vector<std::string> allowedCommands = {
		"pause",     // Pause the console
		"color 0A", // Light green on black
		"color 0B", // Light aqua on black
		"color 0C", // Light red on black
		"color 0D", // Light purple on black
		"color 0E", // Light yellow on black
		"color 0F", // Bright white on black
		"color 08"  // Gray on black
	};
	// Check if the command is in the list of allowed commands
	for (const auto& cmd : allowedCommands) {
		if (cmd == command) {
			return true;
		}
	}
	return false;
}

//********************************************************************************************************************************************  < MyConsoleAPI_extended >   05/12/24

/*************************************************************/
/*                   < MyConsoleAPI_extended >               */
/*                         ****$****                         */
/*                      < Constructor >                      */
/*                     < Main Menu API >                     */
/*************************************************************/

cfc::Startscreen::Startscreen() : FLAGS_theme({/*them_default(0)*/true, /*themeRandom(1)*/false, /*themeRainbow(2)*/false }),
mainMenu_totalParameters(8), mainMenu_defaultParameterState({/*options(0)*/Green, /*programID(1)*/Magenta, /*program(2)*/Cyan,
/*exitID(3)*/Red, /*exit(4)*/Gray, /*objects(5)*/DefaultWhite, /*errorMessages(6)*/Green, /*WAIT(7)*/LightBlue })
{
	/* Initializing the main menu's theme state into a vector, set number_of_state_parameters equal to total number of default elements */
	mainMenuParameterCurentState = mainMenu_defaultParameterState;
}
/*************************************************************/
/*      END OF CONSTRUCTOR FOR MyConsolAPI_Enstension        */
/*                         ****$****                         */
/*************************************************************/


void cfc::Startscreen::errorMessage() {
	clearInputStream();
	print("\nERROR: INVALID INPUT\n", getMainMenuState().at(/*enum eMainMenu_State_ID*/ErrorMessage));
}

void cfc::Startscreen::setMainMenuState(const std::vector<int> newState) {
	print("Setting new state\n");
	for (size_t i = 0; i < mainMenuParameterCurentState.size(); i++)
	{
		mainMenuParameterCurentState[i] = newState[i];
	}
	pause();
}

void cfc::Startscreen::generateMainMenu(const std::vector<int>& stateData) {
	/* StateDate.at( recieves and int ) to identify group to apply color state change to */
	/* Using enum eMainMenu_State_ID Options(0), ProgramID1), Program(2), ExitProgramID(3), ExitProgram(4), Symbols(5), ErrorMessage(6) */

	/* cout has three overloads as of 2024/05/12 */
	/* cout(string, int, string, int, string, int, string, int) */
	/* cout(string, int, string, int) */
	/* cout(string, int) */

	print("CoreFireCode 2024 edition\n", Green);
	print("\n\nMain Menu\n\n", DefaultWhite);
	print("Option", stateData.at(Option), " 6 ", stateData.at(ProgramID), "-", stateData.at(Symbols), " Default Menu Theme\n", stateData.at(Program));
	print("Option", stateData.at(Option), " 7 ", stateData.at(ProgramID), "-", stateData.at(Symbols), " Random Menu Theme\n", stateData.at(Program));
	print("Option", stateData.at(Option), " 8 ", stateData.at(ProgramID), "-", stateData.at(Symbols), " Rainbow Effect\n", stateData.at(Program));
	print("\nHold ", Gray, "esc", LightRed, " to exit\n\n", Gray, "", Black);
}

void cfc::Startscreen::setThemeFlag(const int themeFlag_ID) {
	if (!FLAGS_theme.empty())
	{
		for (size_t i = 0; i < FLAGS_theme.size(); i++)
		{
			if (FLAGS_theme.at(themeFlag_ID))
			{
				FLAGS_theme.at(themeFlag_ID) = true; // Set the callers ID theme to true
			}
			else
			{
				FLAGS_theme.at(i) = false; // Set all other themes to false
			}
		}//end of for loop
	}
	else
	{
		std::abort();
	}

}

auto cfc::Startscreen::check_if_ExitRequested() const -> bool
{
	// Check if the exitRequested flag is set
	return exitRequested_var.load();
}

void cfc::Startscreen::menuTheme(int eNUM_theme) {
	switch (eNUM_theme)
	{
	case defaultTheme: {
		for (size_t i = 0; i < mainMenuParameterCurentState.size(); i++)
		{
			mainMenuParameterCurentState[i] = mainMenu_defaultParameterState[i];
		}
		break;
	}
	case RandomTheme: {
		for (size_t i = 0; i < mainMenuParameterCurentState.size(); i++)
		{
			mainMenuParameterCurentState[i] = getRandomNumber(1, 15);
		}
		break;
	}
	case RainbowTheme: {
		using namespace std::chrono_literals;

		for (size_t i = 0; i < 60; i++)
		{
			for (size_t j = 0; j < mainMenuParameterCurentState.size(); j++)
			{
				mainMenuParameterCurentState[j] = getRandomNumber(1, 15);
			}
			clearScreen();
			generateMainMenu(mainMenuParameterCurentState);
			print("\nWAIT!", WAIT_);
			std::this_thread::sleep_for(0.025s);// Sleep for 25 milliseconds
		}
		break;
	}
	default: {
		for (size_t i = 0; i < mainMenuParameterCurentState.size(); i++)
		{
			mainMenuParameterCurentState[i] = mainMenu_defaultParameterState[i];
		}
		break;
	}//default

	}//end of switch
}//end of menuTheme

/*************************************************************/
/*      END OF PUBLIC METHODS FOR ToolSet_MainMenu           */
/*                         ****$****                         */
/*     START OF PRIVATE METHODS FOR ToolSet_MainMenu         */
/*************************************************************/


const std::vector<int>& cfc::Startscreen::getMainMenuState() const {
	return mainMenuParameterCurentState;
}

const std::vector<int>& cfc::Startscreen::getMainMenuDefaultState() const {
	return mainMenu_defaultParameterState;
}

int cfc::Startscreen::mainMenuLogic() {
	int returnValue{ 0 };

	do {
		clearScreen(); generateMainMenu(mainMenuParameterCurentState); print("\nSelect option: ", LightGreen); setTextColor(DefaultWhite);
		
		std::cin >> returnValue;
		if (!std::cin.fail())
		{
			return returnValue;
		}
		else
		{
			errorMessage();
			system("pause");
			continue;
		}
	} while (true);
}

// ESCkeyButton implementation using the Windows API
cfc::ESCkey_ProgramExit::ESCkey_ProgramExit() : exitRequested_var(false)
{
	// Use a lambda wrapper to pass the stop token correctly
	escThread = std::jthread([this](std::stop_token st) { this->isESCkeyPressed(st); });
}

cfc::ESCkey_ProgramExit::~ESCkey_ProgramExit() {
	// std::jthread automatically requests stop and joins on destruction.
}

void cfc::ESCkey_ProgramExit::isESCkeyPressed( std::stop_token stopToken) const {
	// Poll for the ESC key using GetAsyncKeyState from the Windows API
	while (!stopToken.stop_requested() && !exitRequested_var.load()) {
		// GetAsyncKeyState returns a SHORT; the high-order bit is set if the key is down.
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			// Immediately exit the program when ESC is pressed.
			std::exit(0);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}