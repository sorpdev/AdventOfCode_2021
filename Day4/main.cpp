/*
 * Advent of Code 2021
 * Day 4: Giant Squid
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/*
 * Puzzle 1:
 *  To guarantee victory against the giant squid, figure out which board will win first.
 *	What will your final score be if you choose that board?
 * Puzzle 2:
 *  Figure out which board will win last.
 *	Once it wins, what would its final score be?
 */
constexpr int BOARD_SIZE = 5;

struct BoardField
{
	int number;
	bool marked = false;
	bool causedWin = false;
};

struct Board
{
	int boardStart = -1;
	std::vector<BoardField> boardNumbers;
	int winScore = -1;

	bool checkWin()
	{
		for (int x = 0; x < (BOARD_SIZE); x++)
		{
			bool bCol = true;
			bool bRow = true;

			for (int y = 0; y < (BOARD_SIZE); y++)
			{
				if (!boardNumbers[(x * BOARD_SIZE) + y].marked)
				{
					bRow = false;
				}
				if (!boardNumbers[(y * BOARD_SIZE) + x].marked)
				{
					bCol = false;
				}
				if (bRow == false && bCol == false) break;
			}

			if (bCol == true || bRow == true) return true;
		}

		return false;
	}

	void calculateWin(const std::vector<int>& bingoNumbers)
	{
		for (int i = 0; i < bingoNumbers.size(); i++)
		{
			const int number = bingoNumbers[i];
			for (auto& [fieldNumber, marked, causedWin] : boardNumbers)
			{
				if (fieldNumber == number)
				{
					marked = true;
					if (checkWin())
					{
						winScore = i;
						causedWin = true;
						break;
					}
				}
			}
			if (winScore != -1) break;
		}
	}
};

int Puzzle1And2(bool printValues, bool puzzle2 = false)
{
	int result = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::vector<int> bingoNumbers;
		bool first = true;

		Board bestBoard;
		Board currentBoard;

		std::string line;
		while (getline(file, line))
		{
			if (first)
			{
				//Read the first line and put all numbers in the bingoNumbers vector
				std::stringstream stream(line);

				for (;;)
				{
					int n;
					stream >> n;

					if (stream.good() || stream.eof())
					{
						bingoNumbers.push_back(n);
						if (stream.eof()) break;
					}
					else
					{
						stream.clear();
						stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
					}
				}

				first = false;
			}
			else
			{
				//Play bingo for each board with the bingoNumbers

				if (line.empty()) //New board begins
				{
					if (bestBoard.boardStart != -1) //Check if this board is better than a previous board
					{
						currentBoard.calculateWin(bingoNumbers);
						if (puzzle2 == false && (currentBoard.winScore < bestBoard.winScore || bestBoard.winScore == -
							1))
						{
							bestBoard = currentBoard;
						}
						else if (puzzle2 && (currentBoard.winScore > bestBoard.winScore))
						{
							bestBoard = currentBoard;
						}
						currentBoard = {};
					}
					else
					{
						currentBoard = {static_cast<int>(file.tellg())};
						currentBoard.calculateWin(bingoNumbers);
						bestBoard = currentBoard;
					}

					//Start new board
					currentBoard = {static_cast<int>(file.tellg())};
				}
				else
				{
					std::stringstream stream(line);

					//Add numbers from current line to board
					for (;;)
					{
						int n;
						stream >> n;

						if (stream.good() || stream.eof())
						{
							currentBoard.boardNumbers.push_back({n});
							if (stream.eof()) break;
						}
						else
						{
							stream.clear();
						}
					}

					if (file.tellg() == -1)
					{
						//Include last board in the result
						currentBoard.calculateWin(bingoNumbers);
						if (puzzle2 == false && (currentBoard.winScore < bestBoard.winScore))
						{
							bestBoard = currentBoard;
						}
						else if (puzzle2 && (currentBoard.winScore > bestBoard.winScore))
						{
							bestBoard = currentBoard;
						}
					}
				}
			}
		}

		int sumUnmarkedNumbers = 0;
		int nWinCause = 0;

		if (printValues)
		{
			std::cout << "Best board:\n";
		}

		for (int i = 0; i < bestBoard.boardNumbers.size(); i++)
		{
			int& boardNumber = bestBoard.boardNumbers[i].number;
			bool& marked = bestBoard.boardNumbers[i].marked;
			if (bestBoard.boardNumbers[i].causedWin) nWinCause = boardNumber;
			if (!marked) sumUnmarkedNumbers += boardNumber;
			if (printValues)
			{
				std::cout << (marked ? "[" : " ") << (boardNumber < 10 ? "0" : "") << boardNumber << (
						marked ? "]" : " ") <<
					" ";
				if (((i + 1) % BOARD_SIZE) == 0)
					std::cout << "\n";
			}
		}

		result = sumUnmarkedNumbers * nWinCause;

		if (printValues)
		{
			std::cout << "Sum of unmarked numbers: " << sumUnmarkedNumbers << "\n";
			std::cout << "Number causing win: " << nWinCause << "\n";
			std::cout << sumUnmarkedNumbers << " * " << nWinCause << " = " << result << "\n";
		}

		file.close();
	}

	return result;
}

int main()
{
	const int puzzle1Result = Puzzle1And2(false);
	std::cout << "[Puzzle 1] " << puzzle1Result << " would be the final score of the first winning board\n";
	const int puzzle2Result = Puzzle1And2(false, true);
	std::cout << "[Puzzle 2] " << puzzle2Result << " would be the final score of the last winning board\n";
}
