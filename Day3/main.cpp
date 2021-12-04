/*
 * Advent of Code 2021
 * Day 3: Binary Diagnostic
 */

#include <bitset>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <vector>

constexpr int BIT_LENGTH = 12;

/*
 * Puzzle 1:
 *  Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together.
 *  What is the power consumption of the submarine?
 *	(Be sure to represent your answer in decimal, not binary.)
 */
int Puzzle1(bool printValues)
{
	int result = 0;

	if (std::ifstream file("input.txt"); file.is_open())
	{
		//Array for each bit position
		int x[BIT_LENGTH] = {};
		std::fill_n(x, BIT_LENGTH, 0); //Fill array with zeros

		int position = 0; //Current bit position
		int valueAmount = 1; //How many values we have

		char _char;
		while (file.get(_char))
		{
			if (_char == '1')
			{
				x[position] += 1;
			}
			position++;
			if (_char == '\n')
			{
				position = 0;
				valueAmount++;
			}
		}

		//Calculate gamma rate
		std::bitset<BIT_LENGTH> gammaRate;

		for (int i = 0; i < BIT_LENGTH; i++)
		{
			const int zeros = x[i];
			const int ones = valueAmount - zeros;
			if (ones > zeros)
			{
				//Most common is one
				gammaRate.set(((BIT_LENGTH - 1) - i), true);
			}
			else
			{
				//Most common is zero
				gammaRate.set(((BIT_LENGTH - 1) - i), false);
			}
		}

		//Invert to get epsilonRate
		const std::bitset<BIT_LENGTH> epsilonRate = ~gammaRate;

		result = gammaRate.to_ulong() * epsilonRate.to_ulong();

		if (printValues)
		{
			std::cout << "Gamma rate: " << gammaRate << " (" << gammaRate.to_ulong() << ")" << "\n";
			std::cout << "Epsilon rate: " << epsilonRate << " (" << epsilonRate.to_ulong() << ")" << "\n";
			std::cout << gammaRate.to_ulong() << " * " << epsilonRate.to_ulong() << " = " << result << "\n";
		}
		file.close();
	}

	return result;
}

/*
 * Puzzle 2:
 *  Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together.
 *  What is the life support rating of the submarine?
 *	(Be sure to represent your answer in decimal, not binary.)
 */
bool GetCommon(int position, const std::vector<std::bitset<BIT_LENGTH>>& vector)
{
	int counter = 0;
	for (auto& i : vector)
	{
		if (i[position] == true)
		{
			counter++;
		}
	}
	return (counter >= (vector.size() - counter));
}

std::vector<std::bitset<BIT_LENGTH>> GetNumbers(bool get, int position, std::vector<std::bitset<BIT_LENGTH>>& vector)
{
	std::vector<std::bitset<BIT_LENGTH>> newVector;
	newVector.reserve(vector.size());
	for (auto& i : vector)
	{
		if (i[position] == get)
		{
			newVector.push_back(i);
		}
	}
	vector.clear();
	vector.shrink_to_fit();
	return newVector;
}

int Puzzle2(bool printValues)
{
	int result = 0;

	if (std::ifstream file("input.txt"); file.is_open())
	{
		const int lines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') + 1;
		std::vector<std::bitset<BIT_LENGTH>> numbers;
		numbers.reserve(lines);

		/* 1. Get most common of bit position 1 for the entire file */

		file.seekg(0, std::ifstream::beg);

		int counter = 0;

		std::string line;
		while (getline(file, line))
		{
			std::stringstream stream(line);
			std::bitset<BIT_LENGTH> bitSet;
			stream >> bitSet;

			if (bitSet[(BIT_LENGTH - 1)] == true) counter ++;
			numbers.push_back(bitSet);
		}

		bool common = false;
		if (counter > (lines - counter)) common = true;

		/* 2. Get most common for each position and find oxygen rating */

		std::vector<std::bitset<BIT_LENGTH>> oldNumbers = numbers;
		bool _common = common;

		for (int i = (BIT_LENGTH - 1); i >= 0; i--)
		{
			if (oldNumbers.size() == 1) break;
			_common = GetCommon(i, oldNumbers);
			std::vector<std::bitset<BIT_LENGTH>> newNumbers = GetNumbers(_common, i, oldNumbers);
			oldNumbers = newNumbers;
		}

		std::bitset<BIT_LENGTH> oxygen = oldNumbers[0];

		/* 2. Get least common for each position and find oxygen rating */

		oldNumbers = numbers;
		_common = !common;

		for (int i = (BIT_LENGTH - 1); i >= 0; i--)
		{
			if (oldNumbers.size() == 1) break;
			_common = !GetCommon(i, oldNumbers);
			std::vector<std::bitset<BIT_LENGTH>> newNumbers = GetNumbers(_common, i, oldNumbers);
			oldNumbers = newNumbers;
		}

		std::bitset<BIT_LENGTH> co2 = oldNumbers[0];
		result = oxygen.to_ulong() * co2.to_ulong();

		if (printValues)
		{
			std::cout << "Oxygen generator rating: " << oxygen << " (" << oxygen.to_ulong() << ")" << "\n";
			std::cout << "CO2 scrubber rating: " << co2 << " (" << co2.to_ulong() << ")" << "\n";
			std::cout << oxygen.to_ulong() << " * " << co2.to_ulong() << " = " << result << "\n";
		}

		file.close();
	}
	return result;
}

int main()
{
	const int puzzle1Result = Puzzle1(false);
	std::cout << "[Puzzle 1] " << puzzle1Result << " is the power comsumption of the submarine\n";
	const int puzzle2Result = Puzzle2(false);
	std::cout << "[Puzzle 2] " << puzzle2Result << " is the life support rating of the submarine\n";
}
