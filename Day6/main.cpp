#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <ExecutionTime.h>

bool checkPacketMatch(std::string chunk)
{
	std::list<char> storage(chunk.begin(), chunk.end());
	storage.sort();
	storage.unique();

	return storage.size() == chunk.size();
}

int scanPackets(std::string line, unsigned int chunkSize)
{
	int charactersProcessed = -1;
	for (uint16_t i = chunkSize; i < line.size(); ++i)
	{
		std::string chunk = line.substr(i - chunkSize, chunkSize);
		if (checkPacketMatch(chunk))
		{
			charactersProcessed = i;
			break;
		}
	}

	return charactersProcessed;
}

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 6: Supply Stacks." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;

	std::ifstream file("input.txt");

	
	// Phase 1: Read the data from file
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {

			int startOfPacketMarker = scanPackets(line, 4);
			if (startOfPacketMarker >= 0) {
				std::cout << "start-of-packet marker at " << startOfPacketMarker  << std::endl;
			}
			
			int startOfMessageMarker = scanPackets(line, 14);
			if (startOfMessageMarker >= 0) {
				std::cout << "start-of-message marker at " << startOfMessageMarker  << std::endl;
			}
		}
	}

	file.close();

	timer.stop();
}