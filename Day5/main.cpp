#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ExecutionTime.h>


struct Crate
{
	std::string label = "";
};

struct Stack
{
	uint16_t slot = 0;
	std::vector<Crate> crates = {};
};

struct Bay
{
	std::vector<Stack> stacks = {};
};

struct Instruction {};

struct IMove : Instruction
{
	uint32_t quantity = 0;
	uint32_t from = 0;
	uint32_t to = 0;
};

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 5: Supply Stacks." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");

	std::vector<std::string> head = {};
	std::vector<Instruction> instructions = {};

	// Phase 1: Read the data from file

	enum ReadMode
	{
		HEAD = 0,
		INSTRUCTIONS = 1
	};

	ReadMode readMode = ReadMode::HEAD;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			
			if (line == "") {
				readMode = ReadMode::INSTRUCTIONS;
				continue;
			}

			if (readMode == ReadMode::HEAD)
			{
				// strip special characters
				std::string lineStripped = "";
				for (uint16_t i = 0; i < line.size(); ++i) {
					std::string c = std::string{ line[i] };
					if (c != "" && c != "[" && c != "]") {
						lineStripped.append(c);
					}
				}

				head.push_back(line);
				//head.push_back(lineStripped);
			}
			else if (readMode == ReadMode::INSTRUCTIONS)
			{
				if (line.starts_with("move")) {
					IMove i = IMove();
					auto _ = sscanf(line.c_str(), "move %d from %d to %d", &i.quantity, &i.from, &i.to);
					instructions.push_back(i);
				}
			}
		}
	}

	file.close();

	// Phase 2: Parse the Head data
	
	Bay bay = Bay();

	//  first, reverse the vector so we can read this "bottom to top"
	std::reverse(std::begin(head), std::end(head));
	
	enum HeadParseMode
	{
		BAY,
		STACK
	};

	HeadParseMode headParseMode = HeadParseMode::BAY;

	for (std::string line : head)
	{
		std::cout << line << std::endl;
		
		headParseMode = bay.stacks.size() > 0 ? HeadParseMode::STACK : HeadParseMode::BAY;

		for (auto& ch : line)
		{
			std::string c = std::string{ ch };

			if (c != "" && c != " " && c != "[" && c != "]") { // ignore all characters and whitespace except the letters and numbers
				if (headParseMode == HeadParseMode::BAY) {
					Stack stack = Stack();
					stack.slot = std::stoi(c);
					bay.stacks.push_back(stack);
				}
				else if (headParseMode == HeadParseMode::STACK) {
					Crate crate = Crate();
					crate.label = c;
				}
			}
		}
	}

	std::cout << "Part 1: : " << "" << std::endl;
	std::cout << "Part 2: : " << "" << std::endl;

	timer.stop();
}