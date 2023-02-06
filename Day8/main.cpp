#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <ExecutionTime.h>

struct Tree
{
	unsigned int x = 0, y = 0, z = 0;
	bool isVisible = false;
	Tree* up = nullptr;
	Tree* down = nullptr;
	Tree* left = nullptr;
	Tree* right = nullptr;
};

class Forest
{
public:
	std::vector<std::vector<Tree*>> grid = {};
};

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 8: Treetop Tree House." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	Forest forest = Forest();

	std::ifstream file("input.txt");

	// Phase 1: Read the data from file
	if (file.is_open())
	{
		std::string line;
		unsigned int y = 0;
		while (std::getline(file, line)) {

			std::vector<Tree*> row(line.size());
			for (unsigned int x = 0; x < line.size(); ++x)
			{
				Tree* tree = new Tree();
				tree->x = x;
				tree->y = y;
				tree->z = std::stoi(std::string{ line[x] });

				row[x] = tree;
			}

			forest.grid.push_back(row);
			++y;

			//std::cout << line << std::endl;

		}
	}

	// Phase 2: Map built, time to answer some questions about it
	for (unsigned int y = 0; y < forest.grid.size(); ++y)
	{
		for (unsigned int x = 0; x < forest.grid[y].size(); ++x)
		{
			Tree* col = forest.grid[y][x];
			std::cout << col->z << std::endl;

			int
				l = x - 1,
				u = y - 1,
				d = y + 1,
				r = x + 1;

			//std::cout << "Left=" << l << "; Up=" << u << "; Right=" << r << "; Down=" << d << std::endl;

			// if this tree is an edge, it's visible by default 
			if (l == -1 || u == -1 || r >= forest.grid[y].size() || d >= forest.grid.size()) {
				std::cout << "Tree is an edge at " << x << "," << y << std::endl;
				col->isVisible = true;
				continue;
			}

			if (col->isVisible == false)
			{
				// I guess my first idea is simply to explode outward from this tree in each direction
				// I'm 100% positive there's a better way than this, as this is super slow and super awkward

				bool rVisible = true,
					 dVisible = true,
					 lVisible = true,
					 uVisible = true;
				while (rVisible && r < forest.grid[y].size())
				{
					// check all values to the right of this tree, if any are a bigger number, this tree is not visible
					if (col->z <= forest.grid[y][r]->z)
					{
						rVisible = false;
					}

					++r;
				}

				while (dVisible && d < forest.grid.size())
				{
					if (col->z <= forest.grid[d][x]->z)
					{
						dVisible = false;
					}

					++d;
				}

				while (lVisible && l >= 0)
				{
					--l;
				}

				while (uVisible && u >= 0)
				{
					--u;
				}
			}
		}
	}


	file.close();

	timer.stop();
}
