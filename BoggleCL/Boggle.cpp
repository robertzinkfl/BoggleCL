#include <iostream>
#include <ctime>
#include <array>
#include <string>
#include <vector>
#include <locale>
#include <fstream>
#include <algorithm>
#include "dice.h"
using namespace std;

vector<string> words_entered;
vector<string> scored;
void prompt_for_input();
void check_words(Dice dice);
bool duplicate(string word);
bool long_enough(string word);
bool dict_word(string word);
bool appears_in_grid(string word, Dice dice);
bool connects(Dice dice, vector<vector<int>> letter_locs, vector<int> used_locs,
			  string word, int counter);
int score_word(string word);

int main() {
	Dice dice;

	cout << "Dice rolled: " << endl;

	dice.roll_dice();
	dice.print_board();

	prompt_for_input();

	cout << endl;

	check_words(dice);

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

}

void check_words(Dice dice) {
	int points = 0;
	
	for (string word : words_entered) {
		if (!duplicate(word))
			continue;
		if (!long_enough(word))
			continue;
		if (!dict_word(word))
			continue;
		if (!appears_in_grid(word, dice))
			continue;

		points += score_word(word);
	}

	cout << "\nYour total score is " << points << " points!" << endl;
}

bool duplicate(string word) {
	for (string item : scored) {
		if (item == word) {
			cout << "The word " << word << " has already been scored." << endl;
			return false;
		}
	}

	scored.push_back(word);
	return true;
}

bool long_enough(string word) {
	if (word.length() < 3) {
		cout << "The word " << word << " is too short." << endl;
		return false;
	}

	return true;
}

bool dict_word(string word) {
	// Find better solution here if possible...this is slow! But it works!
	string line;
	ifstream dictionary;
	dictionary.open("dictionary.txt");

	while (dictionary.good()) {
		dictionary >> line;
		if (dictionary.good() && strcmp(line.c_str(), word.c_str()) == 0) {
			return true;
		}
	}
	dictionary.close();
	cout << "The word " << word << " is ... not a word." << endl;
	return false;
}

bool appears_in_grid(string word, Dice dice) {
	vector<vector<int>> letter_locs;
	vector<int> used_locs;

	for (string::size_type i = 0; i < word.size(); ++i) {
		vector<int> tmp;
		for (int j = 0; j < 16; j++) {
			if (word.at(i) == dice.get_rolled_dice()[j].at(0)) {
				tmp.push_back(j);
			}
		}
		if (tmp.size() < 1) {
			cout << "Word " << word << " does not exist in grid!" << endl;
			// DEBUG: Reveals grid locations of letters
			/*
			for (vector<int> a : letter_locs) {
				for (int b : a) {
					cout << b << " ";
				}
				cout << endl;
			}
			*/
			return false;
		}
		else letter_locs.push_back(tmp);
	}

	if (connects(dice, letter_locs, used_locs, word, 0)) {
		return true;
	}

	cout << "The word " << word << " does not appear." << endl;
	return false;
}

bool connects(Dice dice, vector<vector<int>> letter_locs, vector<int> used_locs, 
			  string word, int counter) {
	if (counter == word.length() - 1) {
		return true;
	}
	else {
		for (int loc : letter_locs[counter]) {
			bool used = false;
			for (int i = 0; !used && i < used_locs.size(); i++) {
				if (used_locs[i] == loc)
					used = true;
			}
			if (used) continue;
			
			vector<int> current_neighbors = dice.get_neighbors(loc);
			vector<int> next_locations = letter_locs[counter + 1];
			vector<int> intersection(10);
			vector<int>::iterator it;

			it = set_intersection(current_neighbors.begin(), current_neighbors.end(),
								  next_locations.begin(), next_locations.end(),
								  intersection.begin());
			intersection.resize(it - intersection.begin());

			// DEBUG: To see if path is created correctly
			/*
			for (int a : intersection) {
				cout << a << " ";
			}
			cout << endl;
			*/

			if (intersection.size() < 1) {
				continue;
			}
			else {
				used_locs.push_back(loc);
				return connects(dice, letter_locs, used_locs, word, counter + 1);
			}
		}
	}
	return false;
}

int score_word(string word) {
	int length = word.length();

	switch (length) {
		case 3:
		case 4: cout << "The word " << word << " is worth 1 point." << endl; return 1;
		case 5: cout << "The word " << word << " is worth 2 points." << endl; return 2;
		case 6: cout << "The word " << word << " is worth 3 points." << endl; return 3;
		case 7: cout << "The word " << word << " is worth 5 points." << endl; return 5;
		default: cout << "The word " << word << " is worth 7 points." << endl; return 7;
	}
}