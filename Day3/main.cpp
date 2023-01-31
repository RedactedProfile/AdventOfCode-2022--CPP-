#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <map>

int main()
{
	std::cout << "Advent of Code, Day 3: Rucksack Reorganization." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Building score table." << std::endl;
	std::string scoreLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::unordered_map<std::string, uint16_t> scoreTable = {};
	for (uint16_t i = 0; i < scoreLetters.length(); ++i)
	{
		scoreTable[std::string{ scoreLetters[i] }] = i + 1;
	}

	std::cout << "Score table built." << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");


	uint32_t part1_sum = 0;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			// Phase 1: Construct new Rucksack
			
			// Known Fact: Each rucksack only has two compartments 
			size_t pouchSize = line.length() / 2;
			std::vector<std::vector<std::string>> rucksack(2);
			for (auto& pouch : rucksack)
				pouch.resize(pouchSize);
			
			// Phase 2: Fill the rucksacks
			// Known fact: each compartment can hold an equal number of items 
			for (uint16_t i = 0; i < line.length(); ++i)
			{
				// which pouch to put this in
				uint16_t pouch = i == i % pouchSize ? 0 : 1;
				uint16_t slot = i - (pouchSize * pouch);
				std::string item = std::string{ line[i] };

				rucksack[pouch][slot] = item;
			}

			// Phase 3: Determine duplicate
			bool doBreak = false;
			for (uint16_t i = 0; i < pouchSize; ++i)
			{
				for (uint16_t o = 0; o < pouchSize; ++o)
				{
					std::string zzz_left = rucksack[0][i];
					std::string zzz_right = rucksack[1][o];

					if (rucksack[0][i] == rucksack[1][o]) {
						// found the duplicate item
						part1_sum += scoreTable[rucksack[0][i]];
						doBreak = true;
						break;
					}
				}
				if (doBreak)
					break;
			}
		}
	}

	file.close();

	std::cout << "Part 1 Total Sum: " << part1_sum << std::endl;
	
	return 0;
}