/*
 * Robert Zink
 * 2 September 2017
 * robertzinkfl@gmail.com
 *
 * BoggleCL - dice.cpp
 */

#include "dice.h"
#include <array>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

/*
 * Dice constructor
 * Sets up the Boggle dice and neighbor spots
 */
Dice::Dice() {
	dice = { { { "A", "E", "A", "N", "E", "G" },
			   { "A", "H", "S", "P", "C", "O" },
			   { "A", "S", "P", "F", "F", "K" },
		       { "O", "B", "J", "O", "A", "B" },
			   { "I", "O", "T", "M", "U", "C" },
			   { "R", "Y", "V", "D", "E", "L" },
			   { "L", "R", "E", "I", "X", "D" },
			   { "E", "I", "U", "N", "E", "S" },
			   { "W", "N", "G", "E", "E", "H" },
			   { "L", "N", "H", "N", "R", "Z" },
			   { "T", "S", "T", "I", "Y", "D" },
			   { "O", "W", "T", "O", "A", "T" },
			   { "E", "R", "T", "T", "Y", "L" },
			   { "T", "O", "E", "S", "S", "I" },
			   { "T", "E", "R", "W", "H", "V" },
			   { "N", "U", "I", "H", "M", "Qu" } } };

	neighbors = { { { 1, 4, 5 },
					{ 0, 2, 4, 5, 6 },
					{ 1, 3, 5, 6, 7 },
					{ 2, 6, 7 },
					{ 0, 1, 5, 8, 9 },
					{ 0, 1, 2, 4, 6, 8, 9, 10 },
					{ 1, 2, 3, 5, 7, 9, 10, 11 },
					{ 2, 3, 6, 10, 11 },
					{ 4, 5, 9, 12, 13 },
				    { 4, 5, 6, 8, 10, 12, 13, 14 },
					{ 5, 6, 7, 9, 11, 13, 14, 15 },
					{ 6, 7, 10, 14, 15 },
					{ 8, 9, 13 },
					{ 8, 9, 10, 12, 14 },
					{ 9, 10, 11, 13, 15 },
					{ 10, 11, 14 } } };
}

/*
 * Function: roll_dice
 * Used to pick the selection of dice randomly for the current game
 */
void Dice::roll_dice() {
	std::srand(time(NULL));

	for (int i = 0; i < dice.size(); i++) {
		rolled[i] = dice[i][std::rand() % 6];
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(rolled.begin(), rolled.end(), std::default_random_engine(seed));
}

/*
 * Function: get_rolled_dice
 * Getter function for the dice rolled
 */
const std::array<std::string, 16> Dice::get_rolled_dice() const {
	return rolled;
}

/*
 * Function: print_board
 * Prints out the current dice board to standard output
 */
void Dice::print_board() {
	for (int i = 0; i < rolled.size(); i++) {
		std::cout << "[" + rolled[i] + "] ";
		if ((i + 1) % 4 == 0)
			std::cout << std::endl;
	}
}

/*
 * Function: get_neighbors
 * Returns the neighboring spots to pos
 */
std::vector<int> Dice::get_neighbors(int pos) {
	return neighbors[pos];
}