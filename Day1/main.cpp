#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

void cprint(std::string out)
{
	std::cout << out << std::endl;
}

struct Elf
{
	uint32_t id = 0;
	uint64_t calories = 0;
	std::vector<uint32_t> food = {};

	void AddFood(uint32_t item)
	{
		food.push_back(item);
		calories += item;
	}
};

class Party
{
public:
	inline static std::vector<Elf*> Elves = {};

	static Elf* CreateElf() {
		Elf* e = new Elf();
		e->id = Elves.size() + 1;
		Elves.push_back(e);
		return e;
	}

	static bool SortFunction(Elf* a, Elf* b)
	{
		return a->calories > b->calories;
	}

	static void SortPartyByCalories()
	{
		std::sort(Elves.begin(), Elves.end(), SortFunction);
	}

	static uint64_t CountCaloriesRange(uint32_t start, uint32_t end)
	{
		uint64_t totalCalories = 0;

		if (start < Elves.size() && ((start + end) <= Elves.size()))
		{
			for (int32_t i = start; i < start + end; ++i)
			{
				totalCalories += Elves[i]->calories;
			}
		}

		return totalCalories;
	}
};

int main()
{
	cprint("Advent of Code, Day 1: Calorie Counting.");
	cprint("========================================");

	cprint("Loading input..");

	std::ifstream file("input.txt");

	cprint("Starting party.");

	Elf* activeElf = Party::CreateElf();

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			if ("" == line)
			{
				activeElf = Party::CreateElf();
				continue;
			}

			activeElf->AddFood(std::stoi(line));
		}
	}

	file.close();

	std::cout << "Elves in party: " << Party::Elves.size() << std::endl;

	Party::SortPartyByCalories();

	std::cout << "Part 1: Most calories carried by one elf :: " << Party::CountCaloriesRange(0, 1) << std::endl;
	std::cout << "Part 2: Total calories of top 3 elves :: " << Party::CountCaloriesRange(0, 3) << std::endl;

	return 0;
}