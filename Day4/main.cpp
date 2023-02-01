#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ExecutionTime.h>

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 4: Camp Cleanup." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			
		}
	}

	file.close();

	timer.stop();
}