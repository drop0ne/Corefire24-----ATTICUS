#include "MyGames.h"

// QUIZ GAME  //////////
//
void Quiz::run() {
	gameLoop();
}

Quiz::Quiz() : iteration(0) {
} // Constructor

// Start Private Functions
void Quiz::gameLoop() {
	setupEnviorment();
	do {
		iteration++;
		question(iteration);
	} while (iteration < 3);

	CoreComponents::print("\nGAME OVER\n\n", Red);
	CoreComponents::setTextColor(DefaultWhite);
	system("pause"); // Last Instruction before returning to main menu
}

void Quiz::setupEnviorment() {
	CoreComponents::clearScreen();
	CoreComponents::clearInputStream();
	if (iteration != 0) { iteration = 0; }
}

int Quiz::requestInput() {
	std::string guess{};
	int convertedGuess{};
	size_t pos{};
	do {
		CoreComponents::setTextColor(Green);
		std::getline(std::cin, guess);
		try
		{
			convertedGuess = std::stoi(guess, &pos);
			if (pos == guess.length()) {
				if (convertedGuess > 3) { CoreComponents::print("Invalid Number::Out of Range\nTry Again: ", Red); CoreComponents::clearInputStream(); continue; }
				break;
			}
			else { throw std::invalid_argument("Invalid Characters after number\nTry Again: "); CoreComponents::clearInputStream(); }
			break;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Invalid Data::Must Enter an integer\nTry Again: ", e;
			CoreComponents::clearInputStream();
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Out of range\nTry Again: ", e;
			CoreComponents::clearInputStream();
		}
	} while (true);
	return convertedGuess;
}

inline void Quiz::question(int questionNumber) {
	switch (questionNumber)
	{
	case 1: askFirstQuestion(); break;
	case 2: askSecondQuestion(); break;
	case 3: askThirdQuestion(); break;
	}
}

void Quiz::askFirstQuestion() {
	CoreComponents::print("What is the smallest county?\n1. USA\n2. India\n3.Vatican City\nchoose 1-3: ", Cyan);
	if (requestInput() == 3) {
		CoreComponents::setScreenColor("color 08"); // Gray on black
		CoreComponents::print("\nCorrect!\n\n", Magenta);
	}
	else {
		CoreComponents::setScreenColor("color 08"); // Gray on black
		CoreComponents::print("\nIncorrect\n\n", Red);
	}
}

void Quiz::askSecondQuestion() {
	CoreComponents::print("What's the biggest animal in the worl?\n1. Elephant\n2. Bue whale\n3.Great white shark\nchoose 1-3: ", Cyan);
	if (requestInput() == 2) {
		CoreComponents::setScreenColor("color 08"); // Gray on black
		CoreComponents::print("\nCorrect!\n\n", Magenta);
	}
	else {
		CoreComponents::setScreenColor("color 08"); // Gray on black
		CoreComponents::print("\nIncorrect\n\n", Red);
	}
}

void Quiz::askThirdQuestion() {
	CoreComponents::print("How many elements are there in the periodic table?\n1. 118\n2. 115\n3. 120\nchoose 1-3: ", Cyan);
	if (requestInput() == 1) {
		CoreComponents::setScreenColor("color 08"); // Gray on black
		CoreComponents::print("\nCorrect!\n\n", Magenta);
	}
	else {
		CoreComponents::setScreenColor("color 08"); // Gray on black
		CoreComponents::print("\nIncorrect\n\n", Red);
	}
}

// Random Number Generator  //////////   
//  
cfc::NumberGenerator::NumberGenerator() : generator(rd()) {}

cfc::NumberGenerator::~NumberGenerator() {}

int cfc::NumberGenerator::getRandomNumber(const int min, const int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

// Start Number Guessing Game  //////////
//
NumberGuessingGame::NumberGuessingGame() : randomNumber(0), MAX_GUESSES(5), attempt(0), attemptCount(0) {
	rangeLimit.min = 0;
	rangeLimit.max = 20;
}

NumberGuessingGame::~NumberGuessingGame() {}

void NumberGuessingGame::run() {
	CoreComponents::clearScreen();
	CoreComponents::clearInputStream();
	setGameState();
	gameLoop();
}

void NumberGuessingGame::gameLoop() {
	do {
		attemptCount++;
		if (attemptCount >= MAX_GUESSES) {
			std::cout << "\nFAIL: You are out of guesses\n";
			std::cout << "The number was: " << randomNumber << "\n\n";
			system("pause");
			return;
		}

		std::cout << "\nGuess a number between " << rangeLimit.min << " and " << rangeLimit.max << "\n";
		std::cout << "Enter Guess: ";

		if (!(std::cin >> attempt)) {
			std::cout << "Invalid input. Please enter a valid number.\n";
			// Clear the input stream and reset error flags
			CoreComponents::clearInputStream();
			continue;
		}
		if (attempt < rangeLimit.min || attempt > rangeLimit.max) {
			std::cout << "Input out of range. Please enter a number between 0 and 100.\n";
			continue;
		}
		if (attempt == randomNumber) {
			// Winner winner chicken dinner
			std::cout << "Winner!\n";
			system("pause");
			return;
		}
		else {
			if (attempt < randomNumber) {
				std::cout << "Higher\n";
			}
			else {
				std::cout << "Lower\n";
			}
		}
	} while (true);
}

void NumberGuessingGame::setGameState() {
	randomNumber = getRandomNumber(rangeLimit.min, rangeLimit.max);
	attemptCount = 0;
	attempt = 0;
}

// Start CannaCalculator  //////////
//
CannaCalculator::CannaCalculator() {}

CannaCalculator::~CannaCalculator() {}

void CannaCalculator::run() {
	entrypoint();
}

void CannaCalculator::entrypoint() {
	std::vector<double> userDATA(5);

	clearScreen();
	print("CannaCalculator\n\n", Green);
	print("First, enter the percentage of THCa in your cannabis flower.\n", LightCyan);
	print("Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n");


	if (yesNOquestion("The default loss is 20%\nWould you like enter a custom loss percentage? (y/n): ", LightCyan) == 'y')
	{
		setScreenColor("color 08");
		print("\n\nYour custom decimal numbr must be between 0 & 1: ", LightCyan);
		print("\nThe default is 0.20");
		if (userDATA.at(THCl) = getDoubleFromUser("\nEnter Number: ", DefaultWhite)) {
		}
		clearInputStream();
	}
	else { userDATA.at(THCl) = 0.20; } //default

	setScreenColor("color 08");
	userDATA.at(THCp) = getDoubleFromUser("\n\nHow strong is your flower?  What is the percent THC listed?\nEnter the percent here: ", LightCyan);
	setScreenColor("color 08");
	userDATA.at(flowerG) = getDoubleFromUser("\n\nHow many grams of flower will you be using?: ", LightCyan);
	setScreenColor("color 08");
	printResults(mathProccessor(userDATA));
}

char CannaCalculator::yesNOquestion(std::string promptMessage, int messageColor) {
	std::string responce = "empty";
	do
	{
		clearInputStream();
		print(promptMessage, messageColor);
		setTextColor(DefaultWhite);

		if (std::getline(std::cin, responce))
		{
			char returnValue = std::tolower(static_cast<unsigned char>(responce[0])); // Convert first char to lowercase
			if (returnValue == 'y' || returnValue == 'n') {
				clearInputStream();
				return returnValue;
			}
		}
	} while (true);
}

double CannaCalculator::getDoubleFromUser(std::string promptMessage, int messageColor) {
	double responce{ 0 };
	do
	{
		clearInputStream();
		print(promptMessage, messageColor);
		setTextColor(DefaultWhite);

		if (std::cin >> responce)
		{
			if (responce > -1 && responce < 101) {
				return responce;
			}
		}
	} while (true);
}

const std::vector<double> CannaCalculator::mathProccessor(std::vector<double> userDATA) {

	userDATA.at(grossMG) = (userDATA.at(THCp) * 10) * userDATA.at(flowerG);
	userDATA.at(netMG) = userDATA.at(grossMG) * (1 - userDATA.at(THCl));

	return userDATA;
}

void CannaCalculator::printResults(std::vector<double> results) {
	clearScreen();
	setTextColor(LightGreen);

	std::cout << "\n" << results.at(THCp) << "% THCa converts to "
		<< static_cast<int>(results.at(grossMG)) << "mg THC per " << static_cast<int>(results.at(flowerG)) << "g of flower before decarboxylation.\n"
		<< "and " << static_cast<float>(results.at(netMG)) << "mg THC after decarboxylation\n\n";

	setTextColor(LightBlue);
	std::cout << "Gross THC\n";
	for (int i = 2; i <= 13; i += 2) {
		std::cout << static_cast<int>(results.at(grossMG)) / i << "mg per " << i << " servings\n";
	}

	setTextColor(Blue);
	std::cout << "\n\nNET THC\n";
	for (int i = 2; i <= 13; i += 2) {
		std::cout << static_cast<int>(results.at(netMG)) / i << "mg per " << i << " servings\n";
	}

	std::cout << std::endl;
	clearInputStream();
	setTextColor(Gray);
	system("pause");

}

// Power Calculator  //////////
//
CalculatePowerLoss_Watts_x_Meters::CalculatePowerLoss_Watts_x_Meters() {}

CalculatePowerLoss_Watts_x_Meters::~CalculatePowerLoss_Watts_x_Meters() {}

void CalculatePowerLoss_Watts_x_Meters::run() {
	menu();
}
/* Start Private */

auto CalculatePowerLoss_Watts_x_Meters::setProperties() -> Properties_m {
	Properties_m properties_m;
	clearScreen();
	print("Set Properties\n\n", Green);
	while (true) {
		// Resistivity input
		while (true) {
			print("Enter the resistivity of the wire in ohm*meter: ", LightBlue);
			std::cin >> properties_m.resistivity;
			if (std::cin.fail() || properties_m.resistivity <= 0) {
				print("Invalid input. Please enter a positive number for resistivity.\n", Red);
				clearInputStream();
			}
			else {
				break;
			}
		}
		// Current input
		while (true) {
			print("Enter the current in amperes: ", LightBlue);
			std::cin >> properties_m.voltage;
			if (std::cin.fail() || properties_m.voltage <= 0) {
				print("Invalid input. Please enter a positive number for current.\n", Red);
				clearInputStream();
			}
			else {
				break;
			}
		}

		// Length input
		while (true) {
			print("Enter the length of the wire in meters: ", LightBlue);
			std::cin >> properties_m.length;
			if (std::cin.fail() || properties_m.length <= 0) {
				print("Invalid input. Please enter a positive number for length.\n", Red);
				clearInputStream();
			}
			else {
				break;
			}
		}

		// Cross-sectional area input
		while (true) {
			print("Enter the cross-sectional area of the wire in square meters: ", LightBlue);
			std::cin >> properties_m.crossSectionArea;
			if (std::cin.fail() || properties_m.crossSectionArea <= 0) {
				print("Invalid input. Please enter a positive number for cross-sectional area.\n", Red);
				clearInputStream();
			}
			else {
				break;
			}
		}
		clearInputStream();
		return properties_m;
	}
}
void CalculatePowerLoss_Watts_x_Meters::performCalculation(Properties_m& properties_m) {
	printResults(calculatePowerLoss(properties_m), properties_m);
	clearInputStream();
}

long double CalculatePowerLoss_Watts_x_Meters::calculatePowerLoss(Properties_m& properties_m) {
	// Calculate resistance
	long double resistance = properties_m.resistivity * properties_m.length / properties_m.crossSectionArea;
	// Calculate power loss
	long double powerLoss = std::powl(properties_m.voltage, 2) * resistance;
	return powerLoss;
}

void CalculatePowerLoss_Watts_x_Meters::printResults(const long double powerLoss, Properties_m& properties_m) {
	clearScreen();
	print("Calculate Power Loss in Watts per Meter\n\n", Green);
	print("Resistivity            ", Gray); print(properties_m.resistivity, Brown); print(" * meter\n", Brown);
	print("Current                ", Gray); print(properties_m.voltage, Brown); print("   amperes\n", LightBlue);
	print("Length                 ", Gray); print(properties_m.length, Brown); print("   meters\n", LightBlue);
	print("Cross-sectional Area   ", Gray); print(properties_m.crossSectionArea, Brown); print("   square meters\n\n", LightBlue);
	print("Power Loss: ", DefaultWhite); print(powerLoss, LightBlue); print(" Watts per meter\n\n", DefaultWhite);
	system("pause");
}

void CalculatePowerLoss_Watts_x_Meters::information() {
	clearScreen();
	print("Calculate Power Loss in a copper wire as heat measured in Watts per Meter\n\n", Green);
	print("This program calculates the power loss in watts per meter of a wire given the resistivity, current, length, and cross-sectional area.\n\n", LightBlue);
	print("The formula used is:\n", LightBlue);
	print("Power Loss = I^2 * R\n\n", Brown);
	print("Where:\n", LightBlue);
	print("I = Current in amperes\n", Brown);
	print("R = Resistance in ohms\n\n", Brown);
	print("The resistance is calculated using the formula:\n", LightBlue);
	print("R = resistivity * length / cross-sectional area\n\n", Brown);
	print("The resistivity of copper is 1.68e-8 ohm*meter.\n\n", Brown);
	setTextColor(DefaultWhite); system("pause");
}

int CalculatePowerLoss_Watts_x_Meters::returnMenuOption() {
	std::string input{};
	int convertedInput{};
	int inputLenghtLimit{ 1 };

	do {
		print("Enter a number: ", DefaultWhite);
		setTextColor(LightBlue);
		if (std::getline(std::cin, input)) {
			if (input.length() > inputLenghtLimit) {
				print("Invalid input. Please enter a number from 1 to 4.\n", LightGreen);
				clearInputStream();
				continue;
			}
			try
			{
				convertedInput = std::stoi(input);
				break;
			}
			catch (const std::invalid_argument& /*e*/)
			{
				std::cerr << "Invalid input. Please enter a number.\n";
				clearInputStream();
			}
			catch (const std::out_of_range& /*e*/) // need to build a logging system
			{
				std::cerr << "Out of range. Please enter a number.\n";
				clearInputStream();
			}
		}
		else {
			std::cerr << "Invalid input. Please enter a number.\n";
			clearInputStream();
		}
	} while (true);

	return convertedInput;
}

void CalculatePowerLoss_Watts_x_Meters::menu() {
	Properties_m properties_m;
	do
	{
		clearInputStream();
		clearScreen();
		print("Calculate Power Loss in a copper wire as heat measured in Watts per Meter\n\n", Green);
		print("1. ", LightBlue); print("Set Properties\n", DefaultWhite);
		print("2. ", LightBlue); print("Calculate Power Loss\n", DefaultWhite);
		print("3. ", LightBlue); print("Information\n", DefaultWhite);
		print("4. ", LightBlue); print("Return to Main Menu\n\n", DefaultWhite);

		switch (returnMenuOption())
		{
		case 1: properties_m = setProperties(); break;
		case 2: performCalculation(properties_m); break;
		case 3: information(); break;
		case 4: clearInputStream(); return;
		default: print("Invalid input. Please enter a number from 1 to 4.\n", LightGreen); system("pause");
			break;
		}
	} while (true);
}