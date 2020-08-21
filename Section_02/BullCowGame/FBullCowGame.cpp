#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map //用TMap替换std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame(){ Reset(); }


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup out map
	for (auto Letter : Word)// loop through all the letters of the word
	{
		Letter = tolower(Letter);// handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false;// we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	
		
			// we do NOT have an isogram
		//oterwise
			//add the letter to the map as seen 
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}


void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "plane";
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return; 
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess))//if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))//if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a VALID guess, incriments turn, and returns count
//如果猜的词和谜底的字母一样且在相同位置，则Bull加1，如果猜的词和谜底一样，但是位置不一样，则Cow加1
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess


	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
	  // compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
				// if they are in the same place
					// incriment bulls 
				// else
					// incriment cows 
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}

		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = 1;
	}
	else
	{
		bGameIsWon = 0;
	}


	return BullCowCount;
}


