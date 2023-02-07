#define _CRT_SECURE_NO_WARNINGS

#define MAP_WIDTH 64
#define MAP_HEIGHT 32

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
	const char* map[MAP_WIDTH][MAP_HEIGHT] = {};

	std::unordered_map<std::string, Entity*> entities = {};

	
	Map()
	{
		initialize();
	}

	void initialize()
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

	void Render()
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			std::string line = "";
			for (int x = 0; x < MAP_WIDTH; ++x)
			{
				std::string ch = std::string{ map[y][x] };
				
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

			std::cout << line << std::endl;

		}
	}

	file.close();

	timer.stop();
}