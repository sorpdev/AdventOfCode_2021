/*
 * Advent of Code 2021
 * Day 6: Lanternfish
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
 * Puzzle 2:
 *	How many lanternfish would there be after 256 days?
 */
long long Puzzle(bool puzzle2 = false)
{
	const int days = (puzzle2 ? 257 : 81);
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

		for (int i = 1; i < days; i++)
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
	const int puzzle1Result = Puzzle();
	std::cout << "[Puzzle 1] " << puzzle1Result << " lanternfish after 80 days\n";
	const long long puzzle2Result = Puzzle(true);
	std::cout << "[Puzzle 2] " << puzzle2Result << " lanternfish after 256 days\n";
}
