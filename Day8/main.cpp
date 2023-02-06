#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ExecutionTime.h>

struct Tree
{
	unsigned int x = 0, y = 0, z = 0;
	bool isVisible = false;
	unsigned int scenicScore = 0;
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
			//std::cout << col->z << std::endl;

			int
				l = x - 1,
				u = y - 1,
				d = y + 1,
				r = x + 1;

			//std::cout << "Left=" << l << "; Up=" << u << "; Right=" << r << "; Down=" << d << std::endl;

			// if this tree is an edge, it's visible by default 
			if (l == -1 || u == -1 || r >= forest.grid[y].size() || d >= forest.grid.size()) {
				//std::cout << "Tree is an edge at " << x << "," << y << std::endl;
				col->isVisible = true;
				continue;
			}

			if (col->isVisible == false)
			{
				// I guess my first idea is simply to explode outward from this tree in each direction
				// I'm 100% positive there's a better way than this, as this is super slow and super awkward

				std::unordered_map<std::string, bool> visibleFrom = {
					{"up", true},
					{"right", true},
					{"down", true},
					{"left", true},
				};

				std::unordered_map<std::string, unsigned int> scenicScoreCard = {
					{"up", 0},
					{"right", 0},
					{"down", 0},
					{"left", 0},
				};
				
				
				while (visibleFrom["right"] && r < forest.grid[y].size())
				{
					// check all values to the right of this tree, if any are a bigger number, this tree is not visible
					if (col->z <= forest.grid[y][r]->z)
					{
						visibleFrom["right"] = false;
					}

					++r;
					scenicScoreCard["right"]++;
				}
				

				while (visibleFrom["down"] && d < forest.grid.size())
				{
					if (col->z <= forest.grid[d][x]->z)
					{
						visibleFrom["down"] = false;
					}

					++d;
					scenicScoreCard["down"]++;
				}
				

				while (visibleFrom["left"] && l >= 0)
				{
					if (col->z <= forest.grid[y][l]->z)
					{
						visibleFrom["left"] = false;
					}

					--l;
					scenicScoreCard["left"]++;
				}

				while (visibleFrom["up"] && u >= 0)
				{
					if (col->z <= forest.grid[u][x]->z)
					{
						visibleFrom["up"] = false;
					}

					--u;
					scenicScoreCard["up"]++;
				}

				// is this tree visible from any of the directions?
				if (visibleFrom["right"] || visibleFrom["left"] || visibleFrom["up"] || visibleFrom["down"])
				{
					col->isVisible = true;
				}

				col->scenicScore = scenicScoreCard["up"] * scenicScoreCard["down"] * scenicScoreCard["left"] * scenicScoreCard["right"];
			}
		}
	}

	// Phase 3: for Part 1 answer, we need to know how many trees are visible from the outside
	unsigned int part1Answer = 0;
	std::list<unsigned int> part2Answer = {};
	for (unsigned int y = 0; y < forest.grid.size(); ++y)
	{
		for (unsigned int x = 0; x < forest.grid[y].size(); ++x)
		{
			if (forest.grid[y][x]->isVisible)
			{
				part1Answer++;
			}

			part2Answer.push_back(forest.grid[y][x]->scenicScore);
		}
	}


	file.close();

	part2Answer.sort();

	std::cout << "============================================================================" << std::endl;
	std::cout << "Part 1: How many trees are visible from outside: " << part1Answer << std::endl;
	std::cout << "Part 2: Best Scenic Score: " << part2Answer.back() << std::endl;

	timer.stop();
}
