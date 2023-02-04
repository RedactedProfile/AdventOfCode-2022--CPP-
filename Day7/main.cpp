#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <ExecutionTime.h>

struct inode
{
	std::string name;
	std::vector<inode*> nodes;

	inode()
	{}

	inode(std::string _name)
	{
		name = _name;
	}
};

struct dirNode : public inode
{
	unsigned int accumulatedSize = 0;

};

struct fileNode : public inode
{
	unsigned int size = 0;

	fileNode(std::string _name)
	{

	}
};

class FileTree
{
protected:
	inode* root;
	inode* focusedDirectory;
public:
	FileTree()
	{
		root = new inode("/");
		focusedDirectory = root;
	}

	inode* AddFile(std::string name, unsigned int size)
	{
		inode* newFile = new fileNode();
		newFile->
	}

	inode* AddDirectory(std::string name)
	{

	}

	void EvaluateCommand(std::string command)
	{

	}

	void ChangeDir(std::string arg)
	{

	}

	void ListDir()
	{

	}
};

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 7: No Space Left on the Device." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;


	FileTree* tree = new FileTree();

	std::ifstream file("input.txt");

	// Phase 1: Read the data from file
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {

			std::cout << line << std::endl;

			if (line.starts_with("$")) {

			}
		}
	}

	file.close();

	timer.stop();
}