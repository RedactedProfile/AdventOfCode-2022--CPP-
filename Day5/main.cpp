#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ExecutionTime.h>

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 5: Supply Stacks." << std::endl;
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

	std::cout << "Part 1: : " << "" << std::endl;
	std::cout << "Part 2: : " << "" << std::endl;

	timer.stop();
}