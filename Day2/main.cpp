#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

int main()
{
	struct Hand
	{
		std::string shape = "";
		uint16_t score = 0;
	};

	class Game
	{
	public:
		uint64_t gameScore = 0;

		std::unordered_map<std::string, Hand> shapes = {
			{ "Rock", { "Rock", 1 } },
			{ "Paper", { "Paper", 2 } },
			{ "Scissors", { "Scissors", 3 } },
		};

		std::unordered_map<const char*, Hand> playerInputMap = {
			{ "A", shapes["Rock"] },
			{ "B", shapes["Paper"] },
			{ "C", shapes["Scissors"] },
			{ "X", shapes["Rock"] },
			{ "Y", shapes["Paper"] },
			{ "Z", shapes["Scissors"] },
		};

		std::unordered_map<Hand, Hand> winMap = {
			{ shapes["Rock"], shapes["Scissors"] },
			{ shapes["Paper"], shapes["Rock"] },
			{ shapes["Scissors"], shapes["Paper"] },
		};

		std::unordered_map<std::string, uint16_t> scoreMap = {
			{ "w", 6 },
			{ "d", 0 },
			{ "t", 3 },
		};

		uint32_t Evaluate(Hand player1, Hand player2)
		{
			uint32_t score = 0;

			// determine draw 
			if (player1.shape == player2.shape)
			{
				score += scoreMap["d"];
			}
			else
			{
				
			}

			return score;
		}
	};

	



	std::cout << "Advent of Code, Day 2: Rock Paper Scissors." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	Game game = Game();

	std::ifstream file("input.txt");

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {

		}
	}

	file.close();

	
	return 0;
}