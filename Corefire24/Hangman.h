#pragma once
#include "BaseClass.h"
class Hangman : public cfc::CoreComponents
{
public:
	Hangman(); // Constructor
	~Hangman(); // Destructor

	void run(); // public entry point

private:
	std::string word;
	std::string guessed;
	int wrongGuesses;
	const int maxWrongGuesses;
	std::vector<char> guessedLetters;

	void initializeGame();
	void playGame();
};