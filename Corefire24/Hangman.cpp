#include "Hangman.h"

Hangman::Hangman() : word("hangman"), guessed("_______"), wrongGuesses(0), maxWrongGuesses(6), guessedLetters(26, ' ')
{
}

Hangman::~Hangman()
{
}

void Hangman::run(){
	initializeGame();
	return;
}

void Hangman::initializeGame()
{
	/* Start Game */
	print("Welcome to Hangman!\n");
	print("Try to guess the word letter by letter.\n");
	print("You have " + std::to_string(maxWrongGuesses) + " wrong guesses before you lose.\n");



	return;  // EXIT GAME
}

void Hangman::playGame()
{
}
