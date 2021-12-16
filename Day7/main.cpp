/*
 * Advent of Code 2021
 * Day 7: The Treachery of Whales
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

/*
 * Puzzle 1:
 *  Determine the horizontal position that the crabs can align to using the least fuel possible.
 *  How much fuel must they spend to align to that position?
 */
int Puzzle1()
{
	int result = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::list<int> numberList;

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
				break;
		}

		numberList.sort();

		//Calculate the median
		const int mp = (numberList.size() + (numberList.size() % 2 != 0 * 1)) / 2;
		auto beg = numberList.begin();
		std::advance(beg, mp - 1);
		int med = *beg;
		if (numberList.size() % 2 == 0)
		{
			std::advance(beg, 1);
			med += *beg;
			med /= 2;
		}

		//Calculate the total fuel cost to move each crab to that position
		for (auto&& list : numberList)
		{
			const int fuel = (med > list ? med - list : list - med);
			result += fuel;
		}

		file.close();
	}
	return result;
}

/*
 * Puzzle 2:
 * Determine the horizontal position that the crabs can align to using the least fuel possible so they can make you an escape route!
 * How much fuel must they spend to align to that position?
 */
int Puzzle2()
{
	int result = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::list<int> numberList;
		int sum = 0;

		std::string numbers;
		getline(file, numbers);

		std::stringstream stream(numbers);

		for (;;)
		{
			int number;
			stream >> number;
			stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			numberList.push_back(number);
			sum += number;

			if (stream.bad() || stream.eof())
				break;
		}

		numberList.sort();

		//Calculate the mean and get the rounded up and rounded down values
		const int meanUp = ceil(static_cast<double>(sum) / numberList.size());
		const int meanDown = floor(static_cast<double>(sum) / numberList.size());

		//Calculate the total fuel cost to move each crab to both positions
		int totalFuelCostUp = 0, totalFuelCostDown = 0;
		for (auto&& list : numberList)
		{
			const int stepsUp = (meanUp > list ? meanUp - list : list - meanUp);
			const int stepsDown = (meanDown > list ? meanDown - list : list - meanDown);
			const int fuelUp = (stepsUp * (stepsUp + 1)) / 2;
			const int fuelDown = (stepsDown * (stepsDown + 1)) / 2;
			totalFuelCostUp += fuelUp;
			totalFuelCostDown += fuelDown;
		}

		//Take the one with the lowest total cost of fuel
		result = (totalFuelCostUp < totalFuelCostDown) ? totalFuelCostUp : totalFuelCostDown;

		file.close();
	}
	return result;
}

int main()
{
	const int puzzle1Result = Puzzle1();
	std::cout << "[Puzzle 1] " << puzzle1Result << " total fuel cost\n";
	const int puzzle2Result = Puzzle2();
	std::cout << "[Puzzle 2] " << puzzle2Result << " total fuel cost\n";
}
