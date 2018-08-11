/*The game logic (no view code or direct user interaction)
The game is a simple word guessing game based on Mastermind*/

#pragma once
#ifndef BULL_COW_H
#define BULL_COW_H

#include <string>
#include <vector>

using FString = std::string;
using int32 = int;

//all values initialized to zeros
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullAndCow
{
	public:		
		int32 GetMaxTries() const;
		int32 GetCurrentTry()const;
		int32 GetHiddenWordLength()const;
		FString GetHiddenWord()const;
		FString GetWord()const;
		bool IsGameWon() const ;
		EGuessStatus CheckGuessValidity(FString x)const;
		
		void SetDifficulty();

		FBullAndCow();
		void Reset();
		FBullCowCount SubmitValidGuess(FString Guess);

	private:
		std::vector<FString> library;
		bool IsLowercase(FString Guess) const;
		bool IsIsogram(FString Guess)const;
		bool bIsGameWon;
		int32 MyCurrentTry;
		FString MyHiddenWord;
};

#endif