/*
* Robert Zink
* 2 September 2017
* robertzinkfl@gmail.com
*
* BoggleCL - game.cpp
*/

#include "game.h"
#include "dice.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

Game::Game() {
	std::cout << "Dice rolled: " << std::endl;
	dice.roll_dice();
	dice.print_board();
}

void Game::check_words(std::vector<std::string> *words_entered) {
	int points = 0;

	for (std::string word : *words_entered) {
		if (!duplicate(word))
			continue;
		if (!long_enough(word))
			continue;
		if (!dict_word(word))
			continue;
		if (!appears_in_grid(word))
			continue;

		points += score_word(word);
	}

	std::cout << "\nYour total score is " << points << " points!" << std::endl;
}

bool Game::duplicate(std::string word) {
	for (std::string item : scored) {
		if (item == word) {
			std::cout << "The word " << word << " has already been scored." << std::endl;
			return false;
		}
	}

	scored.push_back(word);
	return true;
}

bool Game::long_enough(std::string word) {
	if (word.length() < 3) {
		std::cout << "The word " << word << " is too short." << std::endl;
		return false;
	}

	return true;
}

bool Game::dict_word(std::string word) {
	// Find better solution here if possible...this is slow! But it works!
	std::string line;
	std::ifstream dictionary;
	dictionary.open("dictionary.txt");

	while (dictionary.good()) {
		dictionary >> line;
		if (dictionary.good() && strcmp(line.c_str(), word.c_str()) == 0) {
			return true;
		}
	}
	dictionary.close();
	std::cout << "The word " << word << " is ... not a word." << std::endl;
	return false;
}

bool Game::appears_in_grid(std::string word) {
	std::vector<std::vector<int>> letter_locs;
	std::vector<int> used_locs;

	for (std::string::size_type i = 0; i < word.size(); ++i) {
		std::vector<int> tmp;
		for (int j = 0; j < 16; j++) {
			if (word.at(i) == dice.get_rolled_dice()[j].at(0)) {
				tmp.push_back(j);
			}
		}
		if (tmp.size() < 1) {
			std::cout << "Word " << word << " does not exist in grid!" << std::endl;
			// DEBUG: Reveals grid locations of letters
			/*
			for (std::vector<int> a : letter_locs) {
			for (int b : a) {
			std::cout << b << " ";
			}
			std::cout << std::endl;
			}
			*/
			return false;
		}
		else letter_locs.push_back(tmp);
	}

	if (connects(letter_locs, used_locs, word, 0)) {
		return true;
	}

	std::cout << "The word " << word << " does not appear." << std::endl;
	return false;
}

bool Game::connects(std::vector<std::vector<int>> letter_locs, std::vector<int> used_locs,
	std::string word, int counter) {
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

			std::vector<int> current_neighbors = dice.get_neighbors(loc);
			std::vector<int> next_locations = letter_locs[counter + 1];
			std::vector<int> intersection(10);
			std::vector<int>::iterator it;

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
				return connects(letter_locs, used_locs, word, counter + 1);
			}
		}
	}
	return false;
}

int Game::score_word(std::string word) {
	int length = word.length();

	switch (length) {
	case 3:
	case 4: std::cout << "The word " << word << " is worth 1 point." << std::endl; return 1;
	case 5: std::cout << "The word " << word << " is worth 2 points." << std::endl; return 2;
	case 6: std::cout << "The word " << word << " is worth 3 points." << std::endl; return 3;
	case 7: std::cout << "The word " << word << " is worth 5 points." << std::endl; return 5;
	default: std::cout << "The word " << word << " is worth 7 points." << std::endl; return 7;
	}
}