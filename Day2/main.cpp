/*
 * Advent of Code 2021
 * Day 2: Dive!
 */

#include <iostream>
#include <fstream>
#include <string>

/*
 * Puzzle 1:
 *  Calculate the horizontal position and depth you would have after following the planned course.
 *  What do you get if you multiply your final horizontal position by your final depth?
 */
enum class Action_P1
{
	UNKNOWN,
	XPLUS,
	YPLUS,
	YMINUS
};

int Puzzle1(const bool printValues)
{
	if (std::ifstream file("input.txt"); file.is_open())
	{
		//[0]=horizontal position [1]=depth
		int pos[2] = {0, 0};

		std::string line;
		while (getline(file, line))
		{
			//Get action
			auto action = Action_P1::UNKNOWN;
			if (line.find("forward") != std::string::npos) action = Action_P1::XPLUS;
			else if (line.find("down") != std::string::npos) action = Action_P1::YPLUS;
			else if (line.find("up") != std::string::npos) action = Action_P1::YMINUS;

			if (action != Action_P1::UNKNOWN)
			{
				//Get value
				const int value = std::stoi(line.substr(line.size() - 1, 1));
				switch (action)
				{
				case Action_P1::XPLUS:
					pos[0] += value;
					break;
				case Action_P1::YPLUS:
					pos[1] += value;
					break;
				case Action_P1::YMINUS:
					pos[1] -= value;
					break;
				}
			}

			if (printValues) std::cout << line << " (" << pos[0] << ", " << pos[1] << ")" << "\n";
		}

		const int result = pos[0] * pos[1];
		file.close();
		return result;
	}
	return -1;
}

/*
 * Puzzle 2:
 *  Using this new interpretation of the commands, calculate the horizontal position and depth you would have after following the planned course.
 *	What do you get if you multiply your final horizontal position by your final depth?
 */
enum class Action_P2
{
	UNKNOWN,
	ZPLUS,
	ZMINUS,
	INCREASE_X_INCREASE_Y
};

int Puzzle2(bool printValues)
{
	if (std::ifstream file("input.txt"); file.is_open())
	{
		//[0]=horizontal position [1]=depth [2]=aim
		int pos[3] = {0, 0, 0};

		std::string line;
		while (getline(file, line))
		{
			//Get action
			auto action = Action_P2::UNKNOWN;
			if (line.find("forward") != std::string::npos) action = Action_P2::INCREASE_X_INCREASE_Y;
			else if (line.find("down") != std::string::npos) action = Action_P2::ZPLUS;
			else if (line.find("up") != std::string::npos) action = Action_P2::ZMINUS;

			if (action != Action_P2::UNKNOWN)
			{
				//Get value
				const int value = std::stoi(line.substr(line.size() - 1, 1));
				switch (action)
				{
				case Action_P2::ZPLUS:
					pos[2] += value;
					break;
				case Action_P2::ZMINUS:
					pos[2] -= value;
					break;
				case Action_P2::INCREASE_X_INCREASE_Y:
					pos[0] += value;
					if (pos[2] != 0) pos[1] += (pos[2] * value);
					break;
				}
			}

			if (printValues) std::cout << line << " (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << "\n";
		}

		const int result = pos[0] * pos[1];
		file.close();
		return result;
	}
	return -1;
}

int main()
{
	const int puzzle1Result = Puzzle1(false);
	std::cout << "[Puzzle 1] " << puzzle1Result <<
		" is the result of multiplying the final horizontal position by the final depth" << "\n";
	const int puzzle2Result = Puzzle2(false);
	std::cout << "[Puzzle 2] " << puzzle2Result <<
		" is the result of multiplying the final horizontal position by the final depth" << "\n";
}
