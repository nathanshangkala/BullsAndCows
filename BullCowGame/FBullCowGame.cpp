#include "FBullCowGame.h"
#include<iostream>
#include<string>
#include<map>
#define TMap std::map

using FString = std::string;
using int32 = int;

//Try getter
int32 FBullAndCow::GetMaxTries()const {return MyMaxTries;}
int32 FBullAndCow::GetCurrentTry()const {return MyCurrentTry;}

//Word getter
int32 FBullAndCow::GetHiddenWordLength() const {return int32(MyHiddenWord.length());}
FString FBullAndCow::GetHiddenWord() const { return MyHiddenWord; }

FBullAndCow::FBullAndCow() {Reset();}
bool FBullAndCow::IsGameWon() const { return bIsGameWon; }

void FBullAndCow::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bIsGameWon = false;
	MyMaxTries = MAX_TRIES;
	return;
}

EGuessStatus FBullAndCow::CheckGuessValidity(FString guess) const
{
	//Not Isogram
	if (!IsIsogram(guess))
		return EGuessStatus::Not_Isogram;
	//Not Lowecase
	else if (false)
		return EGuessStatus::Not_LowerCase;
	else if (guess.length()!= GetHiddenWordLength())
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
	if (BullCowCount.Bulls == WordLength)
		bIsGameWon = true;
	else
		bIsGameWon = false;
	return BullCowCount;
}

bool FBullAndCow::IsIsogram(FString Word)const
{
	if (Word.length() <= 1) return true;
	TMap<char, bool> LetterSeen;
	for (char Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
			return false;
		else
			LetterSeen[Letter] = true;
	}
	return true;
}
