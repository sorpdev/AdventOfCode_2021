#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <algorithm>

/*
 * Advent of Code 2021
 * Day 1: Sonar Sweep
 */

/*
 * Puzzle 1:
 *  How many measurements are larger than the previous measurement?
 */
int ReadLargerMeasurements(const bool printValues)
{
	int largerCounter = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::string line;
		std::optional<int> previousValue;
		while (getline(file, line))
		{
			//Check if larger than previous
			if (previousValue.has_value())
			{
				const int currentValue = std::stoi(line);
				const bool increased = (currentValue > previousValue.value());
				if (printValues) std::cout << line << (increased ? "(increased)" : "(decreased)") << std::endl;
				if (increased) largerCounter++;
			}
			else
			{
				if (printValues) std::cout << line << "(N/A - - no previous measurement>" << std::endl;
			}
			previousValue = std::stoi(line);
		}

		file.close();
	}
	return largerCounter;
}

/*
 * Puzzle 2:
 *  Consider sums of a three-measurement sliding window.
 *  How many sums are larger than the previous sum?
 */
int ReadLargerSums(const bool printValues)
{
	int largerCounter = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::string line;
		std::array<int, 3> sumArray = {0, 0, 0};
		std::optional<int> previousSumValue;
		while (getline(file, line))
		{
			bool end = false;
			const int currentValue = std::stoi(line);
			//Check if sumArray is full
			if (sumArray[2] != 0)
			{
			compare:
				int currentSumValue = sumArray[0] + sumArray[1] + sumArray[2];
				//Compare current sum with previous sum
				if (previousSumValue.has_value())
				{
					//Check if there is any change
					if (currentSumValue != previousSumValue)
					{
						const bool increased = (currentSumValue > previousSumValue.value());
						if (printValues)
							std::cout << currentSumValue << (increased ? "(increased)" : "(decreased)") <<
								std::endl;
						if (increased) largerCounter++;
					}
					else
					{
						if (printValues)
							std::cout << currentSumValue << "(no change)" << std::endl;
					}
				}
				else
				{
					if (printValues) std::cout << currentSumValue << "(N/A - - no previous sum>" << std::endl;
				}
				//Set previous and put current value at the end of the sumArray
				previousSumValue = currentSumValue;
				std::shift_left(sumArray.begin(), sumArray.end(), 1);
				sumArray[2] = currentValue;
				//Check if we're currently at the last number
				if (file.tellg() == -1)
				{
					//Do the compare again for the last number so that it is included in the result as well
					if (end == false)
					{
						end = true;
						goto compare;
					}
				}
			}
			else
			{
				//sumArray is not full so put the current value in it
				if (sumArray[0] == 0) sumArray[0] = currentValue;
				else if (sumArray[1] == 0) sumArray[1] = currentValue;
				else if (sumArray[2] == 0) sumArray[2] = currentValue;
			}
		}

		file.close();
	}
	return largerCounter;
}

int main()
{
	const int puzzle1Result = ReadLargerMeasurements(false);
	std::cout << "[Puzzle 1] " << puzzle1Result << " measurements are larger than the previous measurement"
		<< std::endl;
	const int puzzle2Result = ReadLargerSums(false);
	std::cout << "[Puzzle 2] " << puzzle2Result << " sums are larger than the previous sums"
		<< std::endl;
}
