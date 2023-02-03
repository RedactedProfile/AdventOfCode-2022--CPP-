#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <variant>
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

	/*
	* Shift one box at a time
	*/
	void Move(uint8_t from, uint8_t to)
	{
		Crate originalCrate = stacks[from].crates.back();
		stacks[from].crates.pop_back();
		stacks[to].crates.push_back(originalCrate);
	}

	/* 
	* Shift a stack of boxes all at once
	*/
	void MoveStack(uint8_t quantity, uint8_t from, uint8_t to)
	{
		std::vector<Crate> crates(quantity);
		for (unsigned int i = 0; i < quantity; ++i)
		{
			Crate originalCrate = stacks[from].crates.back();
			stacks[from].crates.pop_back();
			crates[i] = originalCrate;
		}
		std::reverse(crates.begin(), crates.end());
		stacks[to].crates.insert(stacks[to].crates.end(), std::begin(crates), std::end(crates));
	}

	/*
	* Display stack output
	*/
	void Render()
	{
		std::vector<std::string> map = {};

		unsigned int maxStack = 0;
		for (int i = 0; i < stacks.size(); ++i)
		{
			if (stacks[i].crates.size() > maxStack)
			{
				maxStack = stacks[i].crates.size();
			}
		}

		for (unsigned int c = 0; c < maxStack; ++c)
		{
			std::string line = "";
			for (unsigned int s = 0; s < stacks.size(); ++s)
			{
				Stack stack = stacks[s];
				line.append( stack.crates.size() > c ? "[" + stack.crates[c].label + "] " : "    ");
			}
			map.push_back(line);
		}
		std::reverse(map.begin(), map.end());

		for (unsigned int i = 0; i < map.size(); ++i)
		{
			std::cout << map[i] << std::endl;
		}

		// Stack labels
		for (int s = 0; s < stacks.size(); ++s)
		{
			std::cout << " " << s+1 << "  ";
		}
		std::cout << std::endl;
	}
};

class Instruction 
{
public:
	virtual void test() {}
};

class IMove : public Instruction
{
public:
	uint32_t quantity = 0;
	uint32_t from = 0;
	uint32_t to = 0;
};

class IDelete : public Instruction
{
public:
	std::string nah = "";
};

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 5: Supply Stacks." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");

	std::vector<std::string> head = {};
	std::vector<Instruction*> instructions = {};

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
				std::string lineStripped = "";
				uint8_t stride = 4;
				for (uint16_t i = 0; i < line.size(); i += stride) {
					std::string chunk = line.substr(i, stride);
					lineStripped.append(std::string{ chunk[1] });
				}

				//std::cout << lineStripped << std::endl;
				head.push_back(lineStripped);
			}
			else if (readMode == ReadMode::INSTRUCTIONS)
			{
				if (line.starts_with("move")) {
					IMove* i = new IMove();
					auto _ = sscanf(line.c_str(), "move %d from %d to %d", &i->quantity, &i->from, &i->to);
					instructions.push_back(i);
				}
			}
		}
	}

	file.close();

	// Phase 2: Parse the Head data
	
	Bay bay = Bay();
	Bay bay2;

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
		//std::cout << line << std::endl;
		
		headParseMode = bay.stacks.size() > 0 ? HeadParseMode::STACK : HeadParseMode::BAY;

		for(uint8_t i = 0; i < line.size(); ++i)
		{
			std::string c = std::string{ line[i] };

			if (headParseMode == HeadParseMode::BAY) {
				Stack stack = Stack();
				stack.slot = std::stoi(c);
				bay.stacks.push_back(stack);
			}
			else if (headParseMode == HeadParseMode::STACK && c != " ") {
				Crate crate = Crate();
				crate.label = c;
				bay.stacks[i].crates.push_back(crate);
			}
		}
	}

	bay2 = bay;

	std::cout << "Original: " << std::endl;
	bay.Render();

	// Phase 3: Run instruction set

	for (Instruction* inst : instructions)
	{
		if (IDelete* i = dynamic_cast<IDelete*>(inst))
		{
			std::cout << "_i: : " << i->nah << std::endl;
		}
		else if (IMove* i = dynamic_cast<IMove*>(inst))
		{
			//std::cout << "_i: Move " << i->quantity << " from " << i->from << " to " << i->to << std::endl;

			// Part 1
			for (uint8_t m = 0; m < i->quantity; ++m) 
			{
				bay.Move(i->from - 1, i->to - 1);
			}

			// Part 2
			bay2.MoveStack(i->quantity, i->from - 1, i->to - 1);
		}
	}

	std::cout << "Part 1 Render: " << std::endl;
	bay.Render();

	std::cout << "Part 2 Render: " << std::endl;
	bay2.Render();
	
	std::string part1Answer = "";
	std::string part2Answer = "";

	for(unsigned int s = 0; s < bay.stacks.size(); ++s)
	{
		part1Answer.append(bay.stacks[s].crates.back().label);
		part2Answer.append(bay2.stacks[s].crates.back().label);
	}


	std::cout << "What crates are on top of each stack?" << std::endl;
	std::cout << "Part 1: : " << part1Answer << std::endl;
	std::cout << "Part 2: : " << part2Answer << std::endl;

	timer.stop();
}