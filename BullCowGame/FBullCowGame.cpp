#include "FBullCowGame.h"
#include<iostream>
#include<string>
#include<map>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <time.h>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullAndCow::FBullAndCow() { Reset();} //Default Constructor

//Try getter
int32 FBullAndCow::GetCurrentTry()const {return MyCurrentTry;}

//Word getter
int32 FBullAndCow::GetHiddenWordLength() const {return int32(MyHiddenWord.length());}
FString FBullAndCow::GetHiddenWord() const { return MyHiddenWord; }

int32 FBullAndCow::GetMaxTries()const 
{
	TMap<int32, int32> WordLengthToMaxTries{{3,4},{4,7}, {5,10}, {6,16}, {7,20}};
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}



FString FBullAndCow::GetWord() const
{
	srand(time(NULL));
	int32 index = rand() % library.size();
	return library[index];
}

bool FBullAndCow::IsGameWon() const { return bIsGameWon; }

void FBullAndCow::Reset()
{
	//constexpr int32 MAX_TRIES = 3;
	//library.push_back("planet");
	//const FString HIDDEN_WORD = GetWord();
	//MyHiddenWord = HIDDEN_WORD;
	//MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullAndCow::CheckGuessValidity(FString guess) const
{
	//Not Isogram
	if (!IsIsogram(guess))
		return EGuessStatus::Not_Isogram;
	//Not Lowecase
	else if (!IsLowercase(guess))
		return EGuessStatus::Not_LowerCase;
	else if (guess.length()!= GetHiddenWordLength())
		return EGuessStatus::Wrong_Length;
	else
		return EGuessStatus::OK;
}

void FBullAndCow::SetDifficulty() 
{
	std::cout << "Choose a difficulty: easy / medium / hard" << std::endl;
	FString filename = "";
	FString difficulty = "";
	std::getline(std::cin, difficulty);
	if (difficulty == "easy")
		filename = "easy.txt";
	else if (difficulty == "medium")
		filename = "medium.txt";
	else if (difficulty == "hard")
		filename = "hard.txt";
	
	std::ifstream input(filename);

	FString line;
	while (std::getline(input, line))
	{
		std::stringstream ss;
		ss << line;
		while (ss)
		{
			FString temp;
			ss >> temp;
			if (temp.length() > 0)
				library.push_back(temp);
		}
	}
	MyHiddenWord = GetWord();
	std::cout << "Can you guess the " << MyHiddenWord.length() << " letters isogram word" << std::endl;
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

bool FBullAndCow::IsLowercase(FString Guess) const
{
	bool lowercase = true;
	for (auto Letter : Guess)
	{
		//if (Letter == '\0' || Letter == ' ')
		//	lowercase = true;
		if (!islower(Letter))
			return false;
	}
	return true;
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
