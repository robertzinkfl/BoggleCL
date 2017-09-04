/*
* Robert Zink
* 2 September 2017
* robertzinkfl@gmail.com
*
* BoggleCL - game.h
*/

#ifndef GAME_H
#define GAME_H

#include "dice.h"
#include <string>
#include <vector>

class Game {
	
	public:
		Game();
		void check_words(std::vector<std::string> *words_entered);
	
	private:
		bool duplicate(std::string word);
		bool long_enough(std::string word);
		bool dict_word(std::string word);
		bool appears_in_grid(std::string word);
		bool connects(std::vector<std::vector<int>> letter_locs, std::vector<int> used_locs,
					  std::string word, int counter);
		int score_word(std::string word);

		Dice dice;
		std::vector<std::string> scored;
};

#endif // !GAME_H

