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
 * Puzzle 2:
 *   Consider all of the lines.
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
    
    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }
};

template<>
struct std::hash<Point>
{
    std::size_t operator()(Point const& p) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(p.x);
            std::size_t h2 = std::hash<int>{}(p.y);
            return h1 ^ (h2 << 1);
        }
};

void AddCovering(std::unordered_map<Point, int>& amountCoveringPoints, const int& x, const int& y)
{
	amountCoveringPoints.try_emplace(Point(x, y), 0);
	for (auto& [point, coveringAmount] : amountCoveringPoints)
	{
		if (point.x == x && point.y == y)
		{
			coveringAmount += 1;
		}
	}
}

int Puzzle1And2(const bool printValues, bool puzzle2 = false)
{
    int result = 0;
	if (std::ifstream file("input.txt"); file.is_open())
	{
        const int lines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') + 1;
        int currentLine = 0;
        file.seekg(0);
        
        std::unordered_map<Point, int> amountCoveringPoints;
		std::string line;
        if(printValues) std::cout << "Calculating...\n";
		while (getline(file, line))
		{
            if(printValues){
                currentLine++;
                std::cout << "Progress: [" << currentLine << "/" << lines << "]\n";
            }
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
            
            //Only consider horizontal and vertical lines for puzzle 1
            if(puzzle2 == false && !(p1.x == p2.x || p1.y == p2.y))
                continue;

			//Get covering points
			int diffX = p2.x - p1.x;
			int diffY = p2.y - p1.y;

            if(diffX != 0 && diffY != 0 && puzzle2){ //Get diagonal covering points for puzzle 2
                
                int positiveDiffX = diffX * (diffX < 0 ? -1 : 1);
                int positiveDiffY = diffY * (diffY < 0 ? -1 : 1);
                
                assert(positiveDiffX == positiveDiffY);
                
                for(int i=0;i<(positiveDiffY+1);i++){
                    int x = i * (diffX < 0 ? -1 : 1);
                    int y = i * (diffY < 0 ? -1 : 1);
                    AddCovering(amountCoveringPoints, p1.x + x, p1.y + y);
                }
                
            } else if (diffX != 0) //Get horizontal covering points
            {
				diffX += (diffX < 0 ? -1 : 1);
				for (int i = diffX; i != 0; i += (diffX > 0 ? -1 : 1))
				{
					AddCovering(amountCoveringPoints, (p1.x + (diffX > 0 ? -1 : 1)) + i, p1.y);
				}
			}
			else if (diffY != 0) //Get vertical covering points
			{
				diffY += (diffY < 0 ? -1 : 1);
                for (int i = diffY; i != 0; i += (diffY > 0 ? -1 : 1))
				{
					AddCovering(amountCoveringPoints, p1.x, (p1.y + (diffY > 0 ? -1 : 1) + i));
				}
			}
		}

        if(printValues) std::cout << "Covering amounts: \n";
		for (auto& [point, coveringAmount] : amountCoveringPoints)
		{
			if(printValues) std::cout << "P(" << point.x << "," << point.y << ") = " << coveringAmount << "\n";
            if(coveringAmount >= 2)
                result += 1;
		}
        if(printValues) std::cout << "Points with >=2 coverings: " << result << "\n";
        
		file.close();
	}
	return result;
}

int main()
{
    std::cout << "[Puzzle 1] ...Loading...\n";
    const int puzzle1Result = 0;//Puzzle1And2(false);
    std::cout << "[Puzzle 1] " << puzzle1Result << " points with >=2 coverage\n";
    std::cout << "[Puzzle 2] ...Loading...\n";
    const int puzzle2Result = Puzzle1And2(true, true);
    std::cout << "[Puzzle 2] " << puzzle2Result << " points with >=2 coverage\n";
}
