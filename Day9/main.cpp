#define _CRT_SECURE_NO_WARNINGS

#define MAP_WIDTH 32
#define MAP_HEIGHT 16

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ExecutionTime.h>

struct Vector2i
{
	int x = 0;
	int y = 0;
};

class Entity
{
public:
	const char* label = "-";
	Vector2i coordinates = { 0, 0 };
	int priority = 0;

	virtual void stub() {}
};

class eInfoStart : public Entity
{
public:
	eInfoStart() : Entity()
	{
		label = "s";
	}
};

class eHead : public Entity
{
public:
	eHead() : Entity()
	{
		label = "H";
		priority = 2;
	}
};

class eTail : public Entity
{
public:
	eTail() : Entity()
	{
		label = "T";
		priority = 1;
	}
};

class Map
{
public:
	const char* map[MAP_HEIGHT][MAP_WIDTH] = {};

	// Do not know if Part 2 would favor having the trail separated or not, so opting too out of abundance of caution instead of overriding characters in the map
	unsigned int trail[MAP_HEIGHT][MAP_WIDTH] = {};

	std::unordered_map<std::string, Entity*> entities = {};

	
	Map()
	{
		Initialize();
	}

	void Initialize()
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
			for (int x = 0; x < MAP_WIDTH; ++x)
				map[y][x] = ".";

		entities["info_start"] = new eInfoStart();
		entities["head"] = new eHead();
		entities["tail"] = new eTail();

		Vector2i center = { MAP_WIDTH / 2, MAP_HEIGHT / 2 };
		entities["info_start"]->coordinates = center;
		entities["head"]->coordinates = center;
		entities["tail"]->coordinates = center;
	}

	void Step(std::string direction)
	{
		eHead* head = dynamic_cast<eHead*>(entities["head"]);

		Vector2i before = head->coordinates,
				 after = Vector2i();

			 if (direction == "U") head->coordinates.y--;
		else if (direction == "D") head->coordinates.y++;
		else if (direction == "L") head->coordinates.x--;
		else if (direction == "R") head->coordinates.x++;

		after = head->coordinates;

		UpdateTail(before, after);

	}

	void UpdateTail(Vector2i before, Vector2i after)
	{
		eTail* tail = dynamic_cast<eTail*>(entities["tail"]);
		// we COULD brute force this based on the directional diff
		trail[after.y][after.x] = 1;
	}

	unsigned int CountVisited()
	{
		unsigned int count = 0;

		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			for (int x = 0; x < MAP_WIDTH; ++x)
			{
				if (trail[y][x] > 0)
					++count;
			}
		}

		return count;
	}

	void Render()
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			std::string line = "";
			for (int x = 0; x < MAP_WIDTH; ++x)
			{
				std::string ch = std::string{ map[y][x] };
			
				// Override with trail tile here
				if (trail[y][x] > 0) {
					ch = "#";
				}

				// Check if any Entities to override the tile here
				std::vector<Entity*> entitiesHere = {};

				for (auto& it : entities)
				{
					Vector2i eCoord = it.second->coordinates;
					if (eCoord.x == x && eCoord.y == y)
					{
						//ch = it.second->label;
						entitiesHere.push_back(it.second);
					}
				}

				if (entitiesHere.size() == 1)
				{
					ch = entitiesHere[0]->label;
				}
				else if (entitiesHere.size() > 0)
				{
					std::sort(entitiesHere.begin(), entitiesHere.end(), [](Entity* a, Entity* b) { return a->priority > b->priority; });
					ch = entitiesHere[0]->label;
				}

				line.append(ch);
			}
			std::cout << line << std::endl;
		}			
	}
};

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 9: Rope Bridge." << std::endl;
	std::cout << "========================================" << std::endl;

	Map map = Map();
	map.Render();

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input_example.txt");

	// Phase 1: Read the data from file
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {

			char dir[2] = "";
			int steps = 0;
			auto _ = sscanf(line.c_str(), "%s %d", &dir, &steps);

			for (int i = 0; i < steps; ++i)
			{
				map.Step(std::string{ dir });
				std::cout << "=================================" << std::endl;;
				map.Render();
			}
		}
	}


	file.close();


	unsigned int tailVisitedCount = map.CountVisited();
	std::cout << "Part 1 Answer: Tail visited this many different places: " << tailVisitedCount << std::endl;

	timer.stop();
}