#define _CRT_SECURE_NO_WARNINGS
#define MAX_DRIVE_SIZE 70000000


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

	void AccumulateDirectorySize(unsigned int _size)
	{
		accumulatedSize += _size;
		if (parent != nullptr) {
			parent->AccumulateDirectorySize(_size);
		}
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

	dirNode* GetRoot()
	{
		return root;
	}

	dirNode* GetCWD()
	{
		return focusedDirectory;
	}

	fileNode* AddFile(std::string name, unsigned int size)
	{
		fileNode* newFile = new fileNode(name);
		newFile->size = size;
		focusedDirectory->nodes.push_back(newFile);
		focusedDirectory->AccumulateDirectorySize(size);

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
			Tree(focusedDirectory, 0);
		}
	}

	void Tree(dirNode* tree, unsigned int step = 0)
	{
		unsigned int substep = step + 4;

		//if (step == 0) {
			std::cout << std::setfill(' ') << std::setw(step) << " - " << tree->name << " (dir, totalsize=" << tree->accumulatedSize << ")" << std::endl;
		//}
		
		for (inode* node : tree->nodes )
		{
			if (dirNode* dir = dynamic_cast<dirNode*>(node))
			{
				if (dir->nodes.size() > 0)
				{
					Tree(dir, substep);
				}
				else
				{
					std::cout << std::setfill(' ') << std::setw(substep) << " - " << dir->name << " (dir, totalsize=" << dir->accumulatedSize << ")" << std::endl;
				}
			}
			else if (fileNode * fil = dynamic_cast<fileNode*>(node))
			{
				std::cout << std::setfill(' ') << std::setw(substep) << " - " << fil->name << " (file, size="<< fil->size <<")" << std::endl;
			}
		}
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
		// we don't really need to do anything here for the input provided already lists the output
	}

	unsigned int CalculateDirectorySize(dirNode* tree, unsigned int max_dir_size)
	{
		unsigned int out = 0;

		for (inode* node : tree->nodes)
		{
			if (dirNode* dir = dynamic_cast<dirNode*>(node))
			{
				if (dir->accumulatedSize <= max_dir_size) {
					out += dir->accumulatedSize;
				}
				
				if (dir->nodes.size() > 0)
				{
					out += CalculateDirectorySize(dir, max_dir_size);
				}
			}
		}

		return out;
	}

	std::vector<dirNode*> ScanDirectoriesLarger(dirNode* tree, unsigned int min_dir_size)
	{
		std::vector<dirNode*> dirs = {};

		for (inode* node : tree->nodes)
		{
			if (dirNode* dir = dynamic_cast<dirNode*>(node))
			{
				if (dir->accumulatedSize >= min_dir_size) {
					dirs.push_back(dir);
				}

				if (dir->nodes.size() > 0)
				{
					std::vector<dirNode*> appendables = ScanDirectoriesLarger(dir, min_dir_size);
					dirs.insert(dirs.begin(), appendables.begin(), appendables.end());
				}
			}
		}

		return dirs;
	}
};

int main()
{
	ExecutionTimer<std::chrono::milliseconds> timer;

	std::cout << "Advent of Code, Day 7: No Space Left on the Device." << std::endl;
	std::cout << "========================================" << std::endl;

	std::cout << "Loading input.." << std::endl;



	FileTree* tree = new FileTree();

	//tree->AddDirectory("a");
	//tree->ChangeDir("a");
	//tree->AddDirectory("e");
	//tree->ChangeDir("e");
	//tree->AddFile("i", 584);
	//tree->ChangeDir("..");
	//tree->AddFile("f", 29116);
	//tree->AddFile("g", 2557);
	//tree->AddFile("h.lst", 62596);
	//tree->ChangeDir("..");
	//tree->AddFile("b.txt", 14848514);
	//tree->AddFile("c.dat", 8504156);
	//tree->AddDirectory("d");
	//tree->ChangeDir("d");
	//tree->AddFile("j", 4060174);
	//tree->AddFile("d.log", 8033020);
	//tree->AddFile("d.ext", 5626152);
	//tree->AddFile("k", 7214296);

	//tree->ChangeDir("/");
	//tree->EvaluateCommand("tree");

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

	tree->EvaluateCommand("cd /");
	tree->EvaluateCommand("tree");

	std::cout << "====================================================" << std::endl;

	// Part 1: Discover the accumulated size of all directories under a max size 
	unsigned int part1Size = tree->CalculateDirectorySize(tree->GetRoot(), 100000);
	std::cout << "(Part 1) The accumulated size of all directories below 100000 is " << part1Size << std::endl;

	// Part 2: Find the smallest directory to delete that would free up enough space required 
	unsigned int minimumToFree = 30000000;
	unsigned int currentUsed = tree->GetRoot()->accumulatedSize;
	unsigned int freeSpace = MAX_DRIVE_SIZE - currentUsed;
	unsigned int minimumDirToDelete = minimumToFree - freeSpace;

	std::vector<dirNode*> directories = tree->ScanDirectoriesLarger(tree->GetRoot(), minimumDirToDelete);
	if (directories.size() > 0) {
		std::sort(directories.begin(), directories.end(), [](dirNode* a, dirNode* b) { return a->accumulatedSize < b->accumulatedSize; });
		
		std::cout << "(Part 2) The directory with the smallest size to free up enough room is " << directories[0]->name << " with a contained size of " << directories[0]->accumulatedSize << std::endl;
	}
	

	std::cout << "Press something" << std::endl;
	std::cin.get();
}