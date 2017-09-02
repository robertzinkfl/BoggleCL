/*
* Robert Zink
* 2 September 2017
* robertzinkfl@gmail.com
*
* BoggleCL - dice.h
*/

#ifndef DICE_H
#define DICE_H

#include <array>
#include <vector>
#include <string>

class Dice {

public:
	Dice();
	void roll_dice();
	const std::array<std::string, 16> get_rolled_dice() const;
	void print_board();
	std::vector<int> get_neighbors(int pos);
private:
	std::array<std::array<std::string, 6>, 16> dice;
	std::array<std::string, 16> rolled;
	std::array<std::vector<int>, 16> neighbors;
};

#endif // !DICE_H