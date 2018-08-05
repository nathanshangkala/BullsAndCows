#include "FBullCowGame.h"
#include<iostream>
#include<string>

using FString = std::string;
using int32 = int;

int32 FBullAndCow::GetMaxTries()const {return MyMaxTries;}
int32 FBullAndCow::GetCurrentTry()const {return MyCurrentTry;}
int32 FBullAndCow::GetHiddenWordLength() const {return int32(MyHiddenWord.length());}

FString FBullAndCow::GetHiddenWord() const
{
	return MyHiddenWord;
}

FBullAndCow::FBullAndCow() {Reset();}

void FBullAndCow::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = 8;
	return;
}

bool FBullAndCow::IsGameWon() const
{
	return false;
}

EGuessStatus FBullAndCow::CheckGuessValidity(FString x) const
{
	//Not Isogram
	if (false)
		return EGuessStatus::Not_Isogram;
	//Not Lowecase
	else if (false)
		return EGuessStatus::Not_LowerCase;
	else if (x.length()!= GetHiddenWordLength())
		return EGuessStatus::Wrong_Length;
	else
		return EGuessStatus::OK;
}

FBullCowCount FBullAndCow::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();
	for (int32 i = 0; i < WordLength; i++)
	{
		if (MyHiddenWord[i] == Guess[i])
			BullCowCount.Bulls++;
		else if (MyHiddenWord.find(Guess[i]) >= 0 && MyHiddenWord.find(Guess[i])< WordLength)
			BullCowCount.Cows++;
	}
	//for (int32 MHWChar = 0; MHWChar< WordLength; MHWChar++)
	//{
	//	for (int32 GChar= 0; GChar< WordLength; GChar++)
	//	{
	//		if (MyHiddenWord[MHWChar] == Guess[GChar])
	//		{
	//			if (MHWChar == GChar)
	//				BullCowCount.Bulls++;
	//			else
	//				BullCowCount.Cows++;
	//		}
	//	}
	//}
	return BullCowCount;
}