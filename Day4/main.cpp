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

	uint32_t fullyContainsCount = 0;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			std::vector< std::pair<uint32_t, uint32_t> > group(2);

			uint16_t 
				groupIndex = 0, 
				campIdSlot = 0;

			// Format of each line is like: "24-91,80-92"
			std::string activeStringBuilder = "";

			auto compileStringFunction = [&groupIndex, &campIdSlot, &group](std::string &stringBuilder) {
				uint32_t campId = std::stoi(stringBuilder);

				if (campIdSlot == 0)
					group[groupIndex].first = campId;
				else
					group[groupIndex].second = campId;

				stringBuilder = "";
			};

			for (size_t i = 0; i < line.length(); ++i)
			{
				std::string c = std::string{ line[i] };
				
				if (c == "-") {
					compileStringFunction(activeStringBuilder);

					campIdSlot++;
					continue;
				}
				else if (c == ",") {
					compileStringFunction(activeStringBuilder);

					groupIndex++;
					campIdSlot = 0; // reset id slot, new instance
					continue;
				}

				activeStringBuilder.append(c);

				// one last time for last iteration
				if ((i + 1) == line.length()) {
					compileStringFunction(activeStringBuilder);
				}
			}

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