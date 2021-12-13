/*
 * Advent of Code 2021
 * Day 5: Hydrothermal Venture
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

/*
 * Puzzle 1:
 *  Find a way to simulate lanternfish.
 *  How many lanternfish would there be after 80 days?
 */
int Puzzle1(bool printValues = false)
{
	std::vector<int> numberList;

	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::string numbers;
		getline(file, numbers);

		int day = 0;
		constexpr int simulationDays = 80;

		std::stringstream stream(numbers);

		for (;;)
		{
			int number;
			stream >> number;
			stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			numberList.push_back(number);
			if (stream.bad() || stream.eof())
			{
				break;
			}
		}

		//Print initial state
		if (printValues)
		{
			std::cout << "Initial state: ";
			for (int j = 0; j < numberList.size(); j++)
			{
				int& fish = numberList[j];
				std::cout << fish << (j < numberList.size() - 1 ? "," : "");
			}
			std::cout << "\n";
		}
		day++;

		//Do simulation
		for (int i = 0; i < simulationDays; i++)
		{
			if (printValues) std::cout << "After  " << day << " day" << (day > 1 ? "s: " : ":  ");

			for (int j = 0; j < numberList.size(); j++)
			{
				if (int& fish = numberList[j]; fish == 0)
				{
					fish = 6;
					numberList.push_back(9);
				}
				else fish--;
			}

			if (printValues)
			{
				std::cout << numberList.size();
				std::cout << "\n";
			}
			day++;
		}

		if (printValues) { std::cout << "Amount of fish: " << numberList.size() << "\n"; }
	}

	return numberList.size();
}

long long Puzzle2()
{
	long long result = 0;

	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::vector<int> numberList;
		std::string numbers;
		getline(file, numbers);

		std::stringstream stream(numbers);

		for (;;)
		{
			int number;
			stream >> number;
			stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			numberList.push_back(number);
			if (stream.bad() || stream.eof())
			{
				break;
			}
		}

		long long fishCounts[9];
		std::fill_n(fishCounts, 9, 0);

		for (const int n : numberList)
		{
			fishCounts[n] += 1;
		}

		for (int i = 1; i < 257; i++)
		{
			const long long preZero = fishCounts[0];
			const long long preSeven = fishCounts[7];
			fishCounts[7] = fishCounts[8];
			fishCounts[8] = fishCounts[0];
			for (int j = 0; j < 7; j++)
			{
				fishCounts[j] = fishCounts[j + 1];
			}
			fishCounts[6] = preSeven;
			fishCounts[6] += preZero;
		}

		for (const long long fishCount : fishCounts)
		{
			result += fishCount;
		}

		file.close();
	}

	return result;
}

int main()
{
	const int puzzle1Result = Puzzle1(false);
	std::cout << "[Puzzle 1] " << puzzle1Result << " lanternfish after 80 days\n";
	const long long puzzle2Result = Puzzle2();
	std::cout << "[Puzzle 2] " << puzzle2Result << " lanternfish after 256 days\n";
}
