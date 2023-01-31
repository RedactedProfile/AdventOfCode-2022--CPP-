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

		std::unordered_map<std::string, Hand> playerInputMap = {
			{ "A", shapes["Rock"] },
			{ "B", shapes["Paper"] },
			{ "C", shapes["Scissors"] },
			{ "X", shapes["Rock"] },
			{ "Y", shapes["Paper"] },
			{ "Z", shapes["Scissors"] },
		};

		std::unordered_map<std::string, Hand> winMap = {
			{ shapes["Rock"].shape, shapes["Scissors"] },
			{ shapes["Paper"].shape, shapes["Rock"] },
			{ shapes["Scissors"].shape, shapes["Paper"] },
		};

		std::unordered_map<std::string, Hand> loseMap = {
			{ shapes["Rock"].shape, shapes["Paper"] },
			{ shapes["Paper"].shape, shapes["Scissors"] },
			{ shapes["Scissors"].shape, shapes["Rock"] },
		};

		std::unordered_map<const char*, uint16_t> scoreMap = {
			{ "w", 6 },
			{ "l", 0 },
			{ "d", 3 },
		};

		uint32_t Evaluate(Hand player1, Hand player2)
		{
			uint32_t score = 0;

			score += player1.score;

			// determine draw 
			if (player1.shape == player2.shape)
			{
				std::cout << player1.shape << " ties " << player2.shape << std::endl;
				score += scoreMap["d"];
			}
			else if(player2.shape == winMap[player1.shape].shape)
			{
				std::cout << player1.shape << " beats " << player2.shape << std::endl;
				score += scoreMap["w"];
			}
			else if (player1.shape == winMap[player2.shape].shape)
			{
				std::cout << player2.shape << " loses to " << player1.shape << std::endl;
				score += scoreMap["l"];
			}

			std::cout << "Earned score: " << score << std::endl;

			return score;
		}

		uint32_t Evaluate(std::string player1, std::string player2)
		{
			return Evaluate(playerInputMap[player1], playerInputMap[player2]);
		}
	};

	



	std::cout << "Advent of Code, Day 2: Rock Paper Scissors." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	Game game = Game();
	Game game2 = Game();

	std::ifstream file("input.txt");

	// Sample Data
	//std::cout << "total score: " << game.gameScore << std::endl;
	//game.gameScore += game.Evaluate("Y", "A");
	//std::cout << "total score: " << game.gameScore << std::endl;
	//game.gameScore += game.Evaluate("X", "B");
	//std::cout << "total score: " << game.gameScore << std::endl;
	//game.gameScore += game.Evaluate("Z", "C");
	//std::cout << "total score: " << game.gameScore << std::endl;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			std::string opponentInput = std::string{ line[0] };
			std::string playerInput = std::string{ line[2] };

			Hand opponentHand = game.playerInputMap[opponentInput];
			Hand playerHand = game.playerInputMap[playerInput];

			// Game 1: Opponent vs Player mapping
			game.gameScore += game.Evaluate(playerHand, opponentHand);

			// Game 2: Opponent vs Instruction mapping
			if (playerInput == "Y") {
				// force draw
				playerHand = opponentHand;
			}
			else if (playerInput == "X") {
				// force loss
				playerHand = game.winMap[opponentHand.shape];
			}
			else if (playerInput == "Z") {
				// force win
				playerHand = game.loseMap[opponentHand.shape];
			}

			game2.gameScore += game2.Evaluate(playerHand, opponentHand);
		}
	}

	file.close();

	std::cout << "Game 1 Total Score: " << game.gameScore << std::endl;
	std::cout << "Game 2 Total Score: " << game2.gameScore << std::endl;
	
	return 0;
}