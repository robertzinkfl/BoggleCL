/*
* Robert Zink
* 2 September 2017
* robertzinkfl@gmail.com
*
* BoggleCL - Boggle.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include "dice.h"
#include "game.h"
using namespace std;

void prompt_for_input();
vector<string> words_entered;

int main() {
	Game game;

	prompt_for_input();
	game.check_words(&words_entered);

	system("pause");
	return 0;
}

void prompt_for_input() {
	string word;
	locale loc;
	
	cout << "\nStart typing your words! " 
		 << "(press Enter after each word and enter 'X' when done): " 
		 << endl;

	while (true) {
		cin >> word;
		
		if (word == "X" || word == "x")
			break;

		for (string::size_type i = 0; i < word.length(); ++i)
			word[i] = toupper(word[i], loc);

		words_entered.push_back(word);
	}

	cout << endl;

}