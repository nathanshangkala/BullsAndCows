#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

void PrintIntro(string word);
void PlayGame(std::string &word);
pair <int, int> cows_bulls(string x, string y);
string GetGuess(int counter, string word);
bool EvalueateAnswer(std::string &word, std::string &guess);
string GetWord();
bool AskToPlayAgain();

int main()
{
	cout << "BULLS= correct letter at correct place" << endl;
	cout << "COWS= incorrect letter at incorrect place" << endl;
	cout << endl;
	/*constexpr int WORD_LENGTH = 5;*/
	bool play = 1;
	do
	{
		string word = GetWord();
		PrintIntro(word);
		PlayGame(word);
		play = AskToPlayAgain();
	} while (play);
}

void PlayGame(std::string &word)
{
	int counter = 5;
	string guess="";
	do
	{
		guess = GetGuess(counter, word);
		if(EvalueateAnswer(word,guess))
			return;
		cout << endl;
		counter--;
	} 
	while (counter> 0);
	cout << "You Lose" << endl;
	return;
}

void PrintIntro(string word)
{
	cout << "Welcome to Bulls and Cows, a fun word game" << endl;
	cout << "Can you guess the " << word.length() << " letters isogram word" << endl;
}

string GetWord()
{
	vector<string> library{ "slide","slid", "slurp", "curse", "slope" };
	srand(time(NULL));
	int index = rand() % library.size();
	return library[index];
}

bool AskToPlayAgain()
{
	cout << "Say YES if you want to play again" << endl;
	cout << "NO if you wish to exit" << endl;
	string in = "";
	getline(cin, in);
	if (in == "YES")
		return true;
	else if (in == "NO")
		return false;
	else
	{
		cout << "invalid command" << endl;
		return AskToPlayAgain();
	}
}

pair <int, int> cows_bulls(string x, string y)
{
	pair<int, int> result(0, 0);
	if (x.length() != y.length())
	{
		for (unsigned int i = 0; i < min(x.length(), y.length()); i++)
		{
			if (x[i] == y[i])
				result.first++;
			else
				result.second++;
		}
		if (x.length()> y.length())
			result.second += abs(int(x.length() - y.length()));
	}
	else
	{
		for (unsigned int i = 0; i < x.length(); i++)
		{
			if (x[i] == y[i])
				result.first++;
			else
				result.second++;
		}
	}
	return result;
}

string GetGuess(int counter, string word)
{
	string g;
	cout << endl;
	cout << "show your guess: " << counter << endl;
	cout << "length of word= " << word.length() << endl;
	getline(cin, g);
	cout << "Your Guess was: " << g << endl;
	return g;
}

bool EvalueateAnswer(std::string &word, std::string &guess)
{
	pair<int, int> res = cows_bulls(word, guess);
	cout << "Bulls= " << res.first << ", " << "Cows= " << res.second << endl;
	if (res.second == 0) { cout << "You Win" << endl; return 1; }
	return 0;
}
