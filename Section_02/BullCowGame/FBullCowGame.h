/* The game logic (no view code or direct user interaction)*/



#pragma once
#include <string>
/*函数声明在.h里*/
using FString = std::string;
using int32 = int;

struct FBullCowCount//struct 和 class比较相似，但是struct用于简单结构，比如没有函数只有变量
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};



class FBullCowGame
{  

public:
	FBullCowGame();//构造函数constructor ，和结构体名字一样
	//函数后面加const用于class function,且不能改变class memeber的值
	//结构体里的函数可以直接return底下的private变量

	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;// provide a method for counting bulls & cows, and increasing turn number


	void Reset();//TODO make a more rich reeturn value.
	FBullCowCount SubmitValidGuess(FString);



private:
	//See constructor for initialisation
	int32 MyCurrentTry =1;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};