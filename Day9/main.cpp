#define _CRT_SECURE_NO_WARNINGS

#define MAP_WIDTH 64
#define MAP_HEIGHT 32

#include <iostream>
#include <fstream>
#include <string>
#include <ExecutionTime.h>

class Map
{
public:
	const char* map[MAP_WIDTH][MAP_HEIGHT] = {};

	Map()
	{
		initialize();
	}

	void initialize()
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
			for (int x = 0; x < MAP_WIDTH; ++x)
				map[y][x] = ".";
	}

	void Render()
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			std::string line = "";
			for (int x = 0; x < MAP_WIDTH; ++x)
			{
				line.append(std::string{ map[y][x] });
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