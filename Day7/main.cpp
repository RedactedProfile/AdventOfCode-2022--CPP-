#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <ExecutionTime.h>

class inode
{
public:
	std::string name;
	std::vector<inode*> nodes;

	inode() {}

	inode(std::string _name)
	{
		name = _name;
	}

	virtual void fake() {} // required by dynamic_cast to exist. there's gotta be a better way 
};

class dirNode : public inode
{
public:
	dirNode* parent = nullptr;
	unsigned int accumulatedSize = 0;

	dirNode(std::string _name) : inode(_name)
	{
		name = _name;
	}
};

class fileNode : public inode
{
public:
	unsigned int size = 0;

	fileNode(std::string _name) : inode(_name)
	{
		name = _name;
	}
};

class FileTree
{
protected:
	dirNode* root;
	dirNode* focusedDirectory;
public:
	FileTree()
	{
		root = new dirNode("/");
		focusedDirectory = root;
	}

	fileNode* AddFile(std::string name, unsigned int size)
	{
		fileNode* newFile = new fileNode(name);
		newFile->size = size;
		focusedDirectory->nodes.push_back(newFile);

		return newFile;
	}

	dirNode* AddDirectory(std::string name)
	{
		dirNode* newDir = new dirNode(name);
		newDir->parent = focusedDirectory;
		focusedDirectory->nodes.push_back(newDir);

		return newDir;
	}

	void EvaluateCommand(std::string command)
	{
		if (command.starts_with("cd"))
		{
			ChangeDir(command.substr(3, command.size() - 3));
		} 
		else if (command.starts_with("ls"))
		{
			ListDir();
		}
		else if (command.starts_with("tree"))
		{
			Tree();
		}
	}

	void Tree()
	{

	}

	void ChangeDir(std::string arg)
	{
		if (arg == "/")
		{
			focusedDirectory = root;
			return;
		}
		else if (arg == "..")
		{
			focusedDirectory = focusedDirectory->parent;
			return;
		}

		for (inode* node : focusedDirectory->nodes)
		{
			if (node->name == arg)
			{
				if (dirNode* dir = dynamic_cast<dirNode*>(node))
				{
					focusedDirectory = dir;
				}
				else
				{
					std::cerr << arg << " is not a directory.";
				}

				break;
			}
		}
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

	//tree->AddDirectory("A");
	//tree->ChangeDir("A");
	//tree->AddFile("file1.txt", 3424);
	//tree->AddFile("file2.pdf", 545345341234);
	//tree->AddDirectory("SubA");
	//tree->AddDirectory("SubB");
	//tree->AddDirectory("SubC");
	//tree->ChangeDir("SubB");
	//tree->AddFile("file3.psd", 12313122);

	std::ifstream file("input.txt");

	// Phase 1: Read the data from file
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line)) {
			if (line.starts_with("$")) {
				tree->EvaluateCommand(line.substr(2, line.size() - 2));
			}
			else if (line.starts_with("dir"))
			{
				tree->AddDirectory(line.substr(4, line.size() - 4));
			}
			else if (isdigit(line[0]))
			{
				int fileSize = 0;
				char fileName[128] = "";
				auto _ = sscanf(line.c_str(), "%d %s", &fileSize, &fileName);
				tree->AddFile(std::string{ fileName }, fileSize);
			}
		}
	}

	file.close();

	timer.stop();
}