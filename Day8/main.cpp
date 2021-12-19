/*
 * Advent of Code 2021
 * Day 8: Seven Segment Search
 */

#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

/*
 * Puzzle 1:
 *  In the output values, how many times do digits 1, 4, 7, or 8 appear?
 */
struct Count
{
	int One = 0;
	int Four = 0;
	int Seven = 0;
	int Eight = 0;
};

int Puzzle1()
{
	int result = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::string line;
		Count count;
		while (getline(file, line))
		{
			std::stringstream stream(line);
			//Only count digits in the output values
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '|');

			for (;;)
			{
				std::string pattern;
				stream >> pattern;

				switch (pattern.length())
				{
				case 2: //Digit 1
					count.One++;
					break;
				case 4: //Digit 4
					count.Four++;
					break;
				case 3: //Digit 7
					count.Seven++;
					break;
				case 7: //Digit 8
					count.Eight++;
					break;
				default:
					break;
				}

				if (stream.bad() || stream.eof())
				{
					break;
				}
			}
		}

		//Calculate instances
		auto cPtr = reinterpret_cast<int*>(&count);
		for (int i = 0; i < 4; i++)
		{
			result += cPtr[i];
		}

		file.close();
	}

	return result;
}

/*
 * Puzzle 2:
 *  For each entry, determine all of the wire/segment connections and decode the four-digit output values.
 *	What do you get if you add up all of the output values?
 */
int Puzzle2()
{
	int result = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::unordered_map<int, int> scoreDigits = {
			{49, 8}, {37, 5}, {34, 2}, {39, 3}, {25, 7}, {45, 9}, {41, 6}, {30, 4}, {42, 0}, {17, 1}
		};

		std::string line;
		while (getline(file, line))
		{
			bool output = false;
			std::stringstream stream(line);

			int outputValue = 0;
			int outputPosition = 3;

			std::unordered_map<std::string, int> digitsMapping;
			std::unordered_map<char, int> characterScores;

			for (;;)
			{
				std::string pattern;
				stream >> pattern;
				//Calculate the character scores based on amount of usages
				for (auto i = pattern.begin(); i < pattern.end(); ++i)
				{
					characterScores.insert({*i, 0});
					if (auto c = characterScores.find(*i); c != characterScores.end())
					{
						c->second++;
					}
				}
				if (pattern == "|" || stream.bad() || stream.eof())
				{
					break;
				}
			}

			stream = std::stringstream(line);

			std::array scores = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

			int index = 0;
			for (;;)
			{
				std::string pattern;
				stream >> pattern;

				if (!output)
				{
					//Calculate digit scores
					for (auto j = pattern.begin(); j < pattern.end(); ++j)
					{
						if (auto c = characterScores.find(*j); c != characterScores.end())
						{
							scores[index] += c->second;
						}
					}
					if (auto digit = scoreDigits.find(scores[index]); digit != scoreDigits.end())
					{
						std::ranges::sort(pattern);
						digitsMapping.insert({pattern, digit->second});
					}
					index++;
				}
				else
				{
					//Decode the four digits of the output
					switch (pattern.length())
					{
					case 1: //Invalid digit; skip
						break;
					case 2: //Digit 1
						outputValue += (1 * static_cast<int>(pow(10, outputPosition)));
						break;
					case 3: //Digit 7
						outputValue += (7 * static_cast<int>(pow(10, outputPosition)));
						break;
					case 4: //Digit 4
						outputValue += (4 * static_cast<int>(pow(10, outputPosition)));
						break;
					case 7: //Digit 8
						outputValue += (8 * static_cast<int>(pow(10, outputPosition)));
						break;
					default:
						{
							std::ranges::sort(pattern);
							if (auto digit = digitsMapping.find(pattern); digit != digitsMapping.end())
							{
								outputValue += (digit->second * static_cast<int>(pow(10, outputPosition)));
							}
							break;
						}
					}
					if (outputPosition == 0)
					{
						result += outputValue;
					}
					outputPosition--;
				}

				if (pattern == "|")
					output = true;

				if (stream.bad() || stream.eof())
				{
					output = false;
					break;
				}
			}
		}

		file.close();
	}

	return result;
}

int main()
{
	const int puzzle1Result = Puzzle1();
	std::cout << "[Puzzle 1] " << puzzle1Result << " instances of digits that use a unique number of segments\n";
	const int puzzle2Result = Puzzle2();
	std::cout << "[Puzzle 2] " << puzzle2Result << " is the sum of all output values\n";
}
