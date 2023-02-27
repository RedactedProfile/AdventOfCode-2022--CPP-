#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

int main() {
	auto party = std::vector<uint32_t>{};
	uint32_t active_elf = 0;

	auto finalize_elf = [&party, &active_elf]() {
		party.push_back(active_elf);
		active_elf = 0;
	};

	std::ifstream file("input.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.empty()) {
				finalize_elf();
				continue;
			}

			active_elf += std::stoi(line);
		}

		finalize_elf();
	}

	file.close();

	std::ranges::sort(party.begin(), party.end(), [](const uint32_t a, const uint32_t b){ return a > b; });  // reverse sort in one step

	const uint32_t part1 = party[0];
	const uint32_t part2 = std::accumulate(party.begin(), party.begin() + 3, 0);									// sum an array

	std::cout << "Part 1: " << part1 << std::endl << "Part 2: " << part2 << std::endl;
}
