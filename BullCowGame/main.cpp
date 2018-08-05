#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
#include <stdlib.h>
#include <time.h>
#include "FBullCowGame.h"

/*This is the console executeable that makes use of the BullCowClass 
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

using FText = std::string;
using int32 = int;

void PrintIntro(FText word);
void PlayGame(const FText word);
//std::pair <int32, int32> cows_bulls(FText word, FText guess);
FText GetValidGuess(int32 counter, FText word);
bool EvalueateAnswer(const FText word, FText &guess);
FText GetWord();
bool AskToPlayAgain();

FBullAndCow BCGame;

int main()
{

	std::cout << "BULLS= correct letter at correct place" << std::endl;
	std::cout << "COWS= incorrect letter at incorrect place" << std::endl;
	std::cout << std::endl;
	/*constexpr int WORD_LENGTH = 5;*/
	bool play = 1;
	do
	{
		FText word = GetWord();
		PrintIntro(BCGame.GetHiddenWord());
		//PrintIntro(word);
		PlayGame(BCGame.GetHiddenWord());
		//PlayGame(word);
		play = AskToPlayAgain();
	} while (play);
}

void PlayGame(const FText word)
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText guess="";
	do
	{
		guess = GetValidGuess(MaxTries, word);
		//FBullCowCount BullCowCount = BCGame.
		(guess);

		if(EvalueateAnswer(word,guess))//TODO check valid guesses
			return;
		std::cout << std::endl;
		MaxTries--;
	} 
	while (MaxTries> 0);
	std::cout << "You Lose" << std::endl;
	
	//TODO sumarise game 

	return;

}

void PrintIntro(FText word)
{
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << word.length() << " letters isogram word" << std::endl;
	//std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letters isogram word" << std::endl;
}

FText GetWord()
{
	std::vector<FText> library{ "slide","slid", "slurp", "curse", "slope" };
	srand(time(NULL));
	int32 index = rand() % library.size();
	return library[index];
}

bool AskToPlayAgain()
{
	std::cout << "Say YES if you want to play again" << std::endl;
	std::cout << "NO if you wish to exit" << std::endl;
	FText in = "";
	std::getline(std::cin, in);
	if (in == "YES")
		return true;
	else if (in == "NO")
		return false;
	else
	{
		std::cout << "invalid command" << std::endl;
		return AskToPlayAgain();
	}
}

//std::pair <int32, int32> cows_bulls(FText word, FText guess)
//{
//	std::pair<int32, int32> result(0, 0);
//	if (word.length() != guess.length())
//	{
//		for (int32 i = 0; i < std::max(word.length(), guess.length()); i++)
//		{
//			if (i < word.length() && i < guess.length())
//			{
//				if (word[i] == guess[i])
//					result.first++;
//				else if (word.find(guess[i]) >= 0 && word.find(guess[i])< word.length())
//					result.second++;
//			}
//		}
//	}
//	else
//	{
//		for (int32 i = 0; i < word.length(); i++)
//		{
//			if (word[i] == guess[i])
//				result.first++;
//			else if (word.find(guess[i]) >= 0 && word.find(guess[i])< word.length())
//				result.second++;
//		}
//	}
//	return result;
//}

//loop continiuly until the user gives a valid guess 
FText GetValidGuess(int32 counter, FText word)
{
	FText g;
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		std::cout << std::endl;
		std::cout << "Tries left " << counter << std::endl;
		std::cout << "Try " << counter << ". Enter Your Guess: " << std::endl;
		std::cout << "length of word= " << word.length() << std::endl;
		std::getline(std::cin, g);
		Status = BCGame.CheckGuessValidity(g);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter word without repeating letter" << std::endl;
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter lowercase letters only" << std::endl;
			break;
		default:
			Status = EGuessStatus::OK;
			std::cout << "Your Guess was: " << g << std::endl;
			break;
		}
		std::cout << std::endl;
	}
	while (Status != EGuessStatus::OK);
	return g;
}

bool EvalueateAnswer(const FText word, FText &guess)
{
	FBullCowCount res = BCGame.SubmitValidGuess(guess);
	//std::pair<int32, int32> res = cows_bulls(word, guess);
	std::cout << "Bulls= " << res.Bulls << ", " << "Cows= " << res.Cows << std::endl;
	if (res.Bulls == word.length()) { std::cout << "You Win" << std::endl; return 1; }
	return 0;
}
	