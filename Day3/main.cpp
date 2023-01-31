#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <map>
#include <set>

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
	uint32_t part2_sum = 0;

	if (file.is_open())
	{
		std::vector<std::vector<std::vector<std::string>>> group;

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

			// Phase 3: Determine duplicate.  
			bool doBreak = false;
			for (uint16_t i = 0; i < pouchSize; ++i)
			{
				for (uint16_t o = 0; o < pouchSize; ++o)
				{
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
			// personal note: this is probably the slowest possible way to scan. I'm sure there's a hundred better ways than this. 

			// Phase 4: Add rucksack to group
			if (group.size() < 3) {
				group.push_back(rucksack);
				continue;
			}
			
			// Phase 5: Every group of 3 rucksacks, find their badge
			//          We don't know what item that is, We don't even know what letter corresponds to each groups Badge
			//          All we do know, is that one letter will appear in all three rucksacks, that's the badge
			if (group.size() == 3) {

				std::vector<std::vector<std::string>> groupContents(group.size());

				// first we merge each rucksacks pouches into one array, but keep only the unique letters
				for (uint16_t i = 0; i < group.size(); ++i)
				{
					std::vector<std::string> mergedRucksackPouch = group[i][0];
					// merge the pouches together
					mergedRucksackPouch.insert(mergedRucksackPouch.end(), group[i][1].begin(), group[i][1].end());

					// std::set makes makes the values unique and removes any duplicates
					std::set<std::string> uniqueLetters(mergedRucksackPouch.begin(), mergedRucksackPouch.end());

					// reassign the new set back to the vector
					groupContents[i].assign(uniqueLetters.begin(), uniqueLetters.end());
				}
				
				
				
				std::map<std::string, uint16_t> letterCount = {};
				for (uint16_t g = 0; g < groupContents.size(); ++g)
				{
					for (uint16_t l = 0; l < groupContents[g].size(); ++l)
					{
						std::string letter = std::string{ groupContents[g][l] };

						// Check if this letter exists in our little letter table, if not, create it
						if (!letterCount.contains(letter)) {
							//letterCount.insert(std::make_pair(letter, 0));
							letterCount[letter] = 0;
						}

						// iterate on each encounter of this letter
						letterCount[letter] += 1;
					}
				}

				// In order to sort the map, we must first convert to a vector of pairs (for some reason) and then run the comparitor
				std::vector<std::pair<std::string, uint16_t>> sortableLetterCount{ letterCount.begin(), letterCount.end() };
				std::sort(sortableLetterCount.begin(), sortableLetterCount.end(), [](std::pair<std::string, uint16_t> a, std::pair<std::string, uint16_t> b) { return a.second > b.second; });

				// The top item in the list should be the only letter that appears three times. Check for this. And if so, add it up.
				if (sortableLetterCount[0].second != 3) {
					std::cerr << "Letter " << sortableLetterCount[0].first << " does not appear 3 times for this group.";
				}
				else
				{
					part2_sum += scoreTable[sortableLetterCount[0].first];
				}

				group.clear();
				std::cout << "New Group time" << std::endl;
			}
		}
	}

	file.close();

	std::cout << "Part 1 Total Sum: " << part1_sum << std::endl;
	std::cout << "Part 2 Total Sum: " << part2_sum << std::endl;
	
	return 0;
}