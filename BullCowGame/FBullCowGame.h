#pragma once
#ifndef BULL_COW_H
#define BULL_COW_H

#include <string>

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
		bool IsGameWon() const ;
		EGuessStatus CheckGuessValidity(FString x)const;
		
		FBullAndCow();
		void Reset();
		FBullCowCount SubmitValidGuess(FString Guess);

	private:
		bool bIsGameWon;
		int32 MyCurrentTry;
		int32 MyMaxTries;
		FString MyHiddenWord;
};

#endif