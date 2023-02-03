#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <ExecutionTime.h>

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 6: Supply Stacks." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");

	
	// Phase 1: Read the data from file
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {

			//std::cout << line << std::endl;

			for (uint16_t i = 3; i < line.size(); ++i)
			{
				std::string sub = line.substr(i - 3, 4);
				std::map<std::string, bool> storage = {};
				storage[std::string{ sub[0] }] = true;
				storage[std::string{ sub[1] }] = true;
				storage[std::string{ sub[2] }] = true;
				storage[std::string{ sub[3] }] = true;

				if (storage.size() == 4)
				{
					std::cout << "Part 1: Unique 4 found at itr " << i + 1 << ":" << sub << "." << std::endl;
					break;

				}
			}
		}
	}

	file.close();

	//std::cout << "Part 1: : " << std::endl;
	std::cout << "Part 2: : " << std::endl;

	timer.stop();
}