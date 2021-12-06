/*
 * Advent of Code 2021
 * Day 5: Hydrothermal Venture
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

/*
 * Puzzle 1:
 *   Consider only horizontal and vertical lines.
 *   At how many points do at least two lines overlap?
 */
struct Point
{
	Point() = default;

	int x;
	int y;

	Point(int x, int y) : x(x), y(y)
	{
	}
};

void AddCovering(std::unordered_map<Point, int>& amountCoveringPoints, const int& x, const int& y)
{
	std::cout << "Adding covering: " << x << ", " << y << "\n";
	amountCoveringPoints.try_emplace(Point(x, y), 0);
	for (auto& [point, coveringAmount] : amountCoveringPoints)
	{
		if (point.x == x && point.y == y)
		{
			coveringAmount += 1;
		}
	}
}

int Puzzle1()
{
	if (std::ifstream file("input.txt"); file.is_open())
	{
		std::unordered_map<Point, int> amountCoveringPoints;
		std::string line;
		while (getline(file, line))
		{
			std::stringstream stream(line);

			//Read point
			Point p1, p2;
			int &x1 = p1.x, &y1 = p1.y, &x2 = p2.x, &y2 = p2.y;

			stream >> x1;
			stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			stream >> y1;
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '-');
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '>');
			stream >> x2;
			stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			stream >> y2;

			//Get covering points
			int diffX = p2.x - p1.x;
			std::cout << "diffX: " << diffX << "\n";
			int diffY = p2.y - p1.y;
			std::cout << "diffY: " << diffY << "\n";

			if (diffX != 0) //Get horizontal covering points
			{
				diffX += (diffX < 0 ? -1 : 1);
				for (int i = diffX; i != 0; i += (diffX > 0 ? -1 : 1))
				{
					std::cout << line << ": " << ((p1.x + (diffX > 0 ? -1 : 1)) + i) << "|" << (p1.y) << "\n";
					AddCovering(amountCoveringPoints, (p1.x + (diffX > 0 ? -1 : 1)) + i, p1.y);
				}
			}
			else if (diffY != 0) //Get vertical covering points
			{
				diffY += (diffY < 0 ? -1 : 1);
				for (int i = diffY; i != 0; i += (diffY > 0 ? -1 : 1))
				{
					std::cout << line << ": " << (p1.x) << "|" << (p1.y + (diffY > 0 ? -1 : 1) + i) << "\n";
					AddCovering(amountCoveringPoints, p1.x, (p1.y + (diffY > 0 ? -1 : 1) + i));
				}
			}
		}

		for (auto& [point, coveringAmount] : amountCoveringPoints)
		{
			std::cout << "P(" << point.x << "," << point.y << ") = " << coveringAmount << "\n";
		}

		file.close();
	}
	return 0;
}

int main()
{
	Puzzle1();
}
