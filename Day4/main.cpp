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

	std::cout << "Advent of Code, Day 4: Camp Cleanup." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");

	uint32_t fullyContainsCount = 0;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			std::vector< std::pair<uint32_t, uint32_t> > group(2);

			//// approach 1: stream extractor. This is slower than the sscanf approach
			//std::istringstream stream(line);
			//char del, sep;

			//// parse the string using the stream extractor
			//stream >> group[0].first >> del >> group[0].second >> sep >> group[1].first >> del >> group[1].second;

			// approach 2: sscanf. This is much faster
			sscanf(line.c_str(), "%d-%d,%d-%d", &group[0].first, &group[0].second, &group[1].first, &group[1].second);
			
			// for part 1 we want to collect all instances of where one elf's range entirely engulfs the other elfs duties
			if ( group[0].first <= group[1].first && group[0].second >= group[1].second ||
				 group[1].first <= group[0].first && group[1].second >= group[0].second )
			{
				fullyContainsCount++;
			}
		}
	}

	file.close();

	std::cout << "Part 1: Fully Contained Pairs: " << fullyContainsCount << std::endl;

	timer.stop();
}