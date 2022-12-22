// AoC2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <stack>

std::vector<std::string> LineParser(const char* filePath, const char divider)
{
	std::vector<std::string> result;

	std::ifstream inputFile;
	inputFile.open(filePath);

	if (!inputFile.is_open())
	{
		return result;
	}

	while (inputFile.good())
	{
		std::string temp;
		getline(inputFile, temp, divider);
		result.push_back(temp);
	}

	return result;
}

int D1P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input0", '\n');

	int maxSum = 0;
	int currSum = 0;
	for (std::string line : lines)
	{
		if (line.empty())
		{
			if (currSum > maxSum)
			{
				maxSum = currSum;
			}
			currSum = 0;
		}
		else
		{
			currSum += std::atoi(line.c_str());
		}
	}

	return maxSum;
}

int D1P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input0", '\n');

	int maxSum0 = 0;
	int maxSum1 = 0;
	int maxSum2 = 0;

	int currSum = 0;
	for (std::string line : lines)
	{
		if (line.empty())
		{
			if (currSum > maxSum0)
			{
				maxSum2 = maxSum1;
				maxSum1 = maxSum0;
				maxSum0 = currSum;
			}
			else if (currSum > maxSum1)
			{
				maxSum2 = maxSum1;
				maxSum1 = currSum;
			}
			else if (currSum > maxSum2)
			{
				maxSum2 = currSum;
			}
			currSum = 0;
		}
		else
		{
			currSum += std::atoi(line.c_str());
		}
	}

	return maxSum0 + maxSum1 + maxSum2;
}

int GetMyRockPaperScissorResult(char others, char mine)
{
	char othersCompare = others + 23;

	char diff = othersCompare - mine;

	switch (diff)
	{
	case 0:
		return 3;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 6;
		break;
	case -1:
		return 6;
		break;
	case -2:
		return 0;
		break;
	default:
		return 0;
		break;
	}
}


int GetMyRockPaperScissorScore(char others, char mine)
{
	int score = GetMyRockPaperScissorResult(others, mine);
	switch (mine)
	{
	case 'X':
		score += 1;
		break;
	case 'Y':
		score += 2;
		break;
	case 'Z':
		score += 3;
		break;
	default:
		break;
	}

	return score;
}

int D2P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input1", '\n');

	int score = 0;
	for (std::string& line : lines)
	{
		score += GetMyRockPaperScissorScore(line[0], line[2]);
	}

	return score;
}

int GetMyRockPaperScissorScoreNew(char others, char mine)
{
	int score = 0;
	int othersInt = others - 64;

	switch (mine)
	{
	case 'X':
		score += 0;
		if (othersInt > 1)
		{
			score += othersInt - 1;
		}
		else
		{
			score += 3;
		}
		break;
	case 'Y':
		score += 3 + othersInt;
		break;
	case 'Z':
		score += 6;
		if (othersInt >= 3)
		{
			score += 1;
		}
		else
		{
			score += othersInt + 1;
		}
		break;
	default:
		break;
	}

	return score;
}

int D2P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input1", '\n');

	int score = 0;
	for (std::string& line : lines)
	{
		score += GetMyRockPaperScissorScoreNew(line[0], line[2]);
	}

	return score;
}

int GetPriority(const char& c)
{
	// Lower case
	if (c >= 97 && c <= 122)
	{
		return c - 96;
	}
	else if (c >= 65 && c <= 90)
	{
		return c - 38;
	}
	return 0;
}

int GetSharedItemPriority(std::string rucksack)
{
	std::set<char> appearedItems;
	size_t halfLength = rucksack.length() / 2;

	for (size_t i = 0; i < halfLength; ++i)
	{
		appearedItems.insert(rucksack[i]);
	}

	int result = 0;
	for (size_t i = halfLength; i < rucksack.length(); ++i)
	{
		if (appearedItems.find(rucksack[i]) != appearedItems.end())
		{
			result += GetPriority(rucksack[i]);
			appearedItems.erase(rucksack[i]);
		}
	}

	return result;
}

int D3P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input2", '\n');

	int result = 0;
	for (std::string& line : lines)
	{
		result += GetSharedItemPriority(line);
	}

	return result;
}

void GetItemsAsMap(std::string rucksack, std::map<char, int>& appearedItems)
{
	size_t length = rucksack.length();

	for (size_t i = 0; i < length; ++i)
	{
		if (appearedItems.find(rucksack[i]) != appearedItems.end())
		{
			appearedItems[rucksack[i]]++;
		}
		else
		{
			appearedItems[rucksack[i]] = 1;
		}
	}
}

int GetBadgePriority(std::string rucksack0, std::string rucksack1, std::string rucksack2)
{
	std::map<char, int> appearedItems0;
	std::map<char, int> appearedItems1;
	std::map<char, int> appearedItems2;

	GetItemsAsMap(rucksack0, appearedItems0);
	GetItemsAsMap(rucksack1, appearedItems1);
	GetItemsAsMap(rucksack2, appearedItems2);

	int result = 0;

	for (auto itr = appearedItems0.begin(); itr != appearedItems0.end(); ++itr)
	{
		if (
			//itr->second == 1 && 
			appearedItems1.find(itr->first) != appearedItems1.end() && 
			//appearedItems1[itr->first] == 1 && 
			appearedItems2.find(itr->first) != appearedItems2.end()
			//appearedItems2[itr->first] == 1
			)
		{
			return GetPriority(itr->first);
		}
	}

	return 0;
}

int D3P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input2", '\n');

	int result = 0;
	for (size_t i = 0; i < lines.size(); i += 3)
	{
		result += GetBadgePriority(lines[i], lines[i + 1], lines[i + 2]);
	}

	return result;
}

void DivideStringByDelimiter(std::string string, const char delimiter, std::vector<std::string>& strings)
{
	size_t startPos = 0;
	size_t delimiterPos = 0;
	while (1)
	{
		delimiterPos = string.find(delimiter, startPos);

		if (delimiterPos == std::string::npos)
		{
			std::string subString = string.substr(startPos, string.size() - startPos);
			strings.push_back(subString);
			break;
		}

		std::string subString = string.substr(startPos, delimiterPos - startPos);
		strings.push_back(subString);
		startPos = delimiterPos + 1;
	}
}

int D4P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input3", '\n');

	int result = 0;

	for (std::string& line : lines)
	{
		std::vector<std::string> dividedLine;
		DivideStringByDelimiter(line, ',', dividedLine);

		if (dividedLine.size() != 2)
		{
			return dividedLine.size();
		}

		std::vector<std::string> left;
		std::vector<std::string> right;
		DivideStringByDelimiter(dividedLine[0], '-', left);
		DivideStringByDelimiter(dividedLine[1], '-', right);

		if (std::atoi(left[0].c_str()) <= std::atoi(right[0].c_str()) &&
			std::atoi(left[1].c_str()) >= std::atoi(right[1].c_str()))
		{
			result++;
		}
		else if (std::atoi(left[0].c_str()) >= std::atoi(right[0].c_str()) &&
			std::atoi(left[1].c_str()) <= std::atoi(right[1].c_str()))
		{
			result++;
		}
	}

	return result;
}

int D4P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input3", '\n');

	int result = 0;

	for (std::string& line : lines)
	{
		std::vector<std::string> dividedLine;
		DivideStringByDelimiter(line, ',', dividedLine);

		if (dividedLine.size() != 2)
		{
			return dividedLine.size();
		}

		std::vector<std::string> left;
		std::vector<std::string> right;
		DivideStringByDelimiter(dividedLine[0], '-', left);
		DivideStringByDelimiter(dividedLine[1], '-', right);

		if (std::atoi(left[0].c_str()) > std::atoi(right[1].c_str()))
		{
			continue;
		}
		else if (std::atoi(left[1].c_str()) < std::atoi(right[0].c_str()))
		{
			continue;
		}

		result++;
	}

	return result;
}

void LoadCargos(const std::vector<std::string>& lines, std::vector<std::stack<char>>& cargos, size_t spaceIndex)
{
	std::vector<size_t> stackIndices;

	for (size_t i = 0; i < lines[spaceIndex - 1].size(); ++i)
	{
		if (lines[spaceIndex - 1][i] != ' ')
		{
			stackIndices.push_back(i);

			std::stack<char> pile;
			cargos.push_back(pile);
		}
	}

	for (int i = spaceIndex - 2; i >= 0; --i)
	{
		const std::string& currLine = lines[i];
		for (size_t j = 0; j < stackIndices.size(); ++j)
		{
			if (currLine[stackIndices[j]] != ' ')
			{
				cargos[j].push(currLine[stackIndices[j]]);
			}
		}
	}
}

void ProcessMoveCommand(const std::string& command, std::vector<std::stack<char>>& cargos)
{
	std::vector<std::string> dividedCommand;

	DivideStringByDelimiter(command, ' ', dividedCommand);

	int num = std::atoi(dividedCommand[1].c_str());
	int from = std::atoi(dividedCommand[3].c_str()) - 1;
	int to = std::atoi(dividedCommand[5].c_str()) - 1;

	for (int i = 0; i < num; ++i)
	{
		if (cargos[from].empty())
		{
			return;
		}
		char cargo = cargos[from].top();
		cargos[from].pop();
		cargos[to].push(cargo);
	}
}

std::string D5P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input4", '\n');
	std::vector<std::stack<char>> cargos;

	size_t spaceIndex = 0;
	for (size_t i = 0; i < lines.size(); ++i)
	{
		if (lines[i].empty())
		{
			spaceIndex = i;
			break;
		}
	}


	LoadCargos(lines, cargos, spaceIndex);

	for (size_t i = spaceIndex + 1; i < lines.size(); ++i)
	{
		ProcessMoveCommand(lines[i], cargos);
	}

	std::string result = "";

	for (const std::stack<char> pile : cargos)
	{
		result += pile.top();
	}

	return result;
}

void ProcessMoveCommandNew(const std::string& command, std::vector<std::stack<char>>& cargos)
{
	std::vector<std::string> dividedCommand;

	DivideStringByDelimiter(command, ' ', dividedCommand);

	int num = std::atoi(dividedCommand[1].c_str());
	int from = std::atoi(dividedCommand[3].c_str()) - 1;
	int to = std::atoi(dividedCommand[5].c_str()) - 1;

	std::stack<char> temp;

	for (int i = 0; i < num; ++i)
	{
		if (cargos[from].empty())
		{
			return;
		}
		char cargo = cargos[from].top();
		cargos[from].pop();
		temp.push(cargo);
	}

	while (!temp.empty())
	{
		char cargo = temp.top();
		cargos[to].push(cargo);
		temp.pop();
	}
}

std::string D5P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input4", '\n');
	std::vector<std::stack<char>> cargos;

	size_t spaceIndex = 0;
	for (size_t i = 0; i < lines.size(); ++i)
	{
		if (lines[i].empty())
		{
			spaceIndex = i;
			break;
		}
	}


	LoadCargos(lines, cargos, spaceIndex);

	for (size_t i = spaceIndex + 1; i < lines.size(); ++i)
	{
		ProcessMoveCommandNew(lines[i], cargos);
	}

	std::string result = "";

	for (const std::stack<char> pile : cargos)
	{
		result += pile.top();
	}

	return result;
}

int D6P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input5", '\n');
	std::string line = lines[0];

	std::set<char> window;

	for (size_t i = 3; i < line.size(); ++i)
	{
		window.insert(line[i - 3]);
		window.insert(line[i - 2]);
		window.insert(line[i - 1]);
		window.insert(line[i]);
		
		if (window.size() >= 4)
		{
			return i + 1;
		}

		window.clear();
	}
	return 0;
}

int D6P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input5", '\n');
	std::string line = lines[0];

	std::set<char> window;

	for (size_t i = 13; i < line.size(); ++i)
	{
		for (size_t j = i - 13; j <= i; ++j)
		{
			window.insert(line[j]);
		}
		

		if (window.size() >= 14)
		{
			return i + 1;
		}

		window.clear();
	}

	return 0;
}

struct Directory
{
	Directory(std::string name, Directory* parent)
	{
		m_name = name;
		m_parent = parent;
	}

	~Directory()
	{
		for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			delete itr->second;
		}

		m_children.clear();
	}

	int GetTotalSize()
	{
		int totalSize = 0;

		for (auto itr = m_files.begin(); itr != m_files.end(); ++itr)
		{
			totalSize += itr->second;
		}

		for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			totalSize += itr->second->GetTotalSize();
		}

		return totalSize;
	}

	int SumOfDirectoriesBelow(int limit)
	{
		int totalSize = 0;

		if (GetTotalSize() <= limit)
		{
			totalSize += GetTotalSize();
		}

		for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			totalSize += itr->second->SumOfDirectoriesBelow(limit);
		}

		return totalSize;
	}

	int FindSmallestDirAbove(int limit)
	{
		int totalSize = GetTotalSize();

		if (totalSize < limit)
		{
			return 0;
		}

		if (m_children.empty())
		{
			return totalSize;
		}

		int result = totalSize;

		for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			int temp = itr->second->FindSmallestDirAbove(limit);
			if (temp >= limit && temp <= result)
			{
				result = temp;
			}
		}

		return result;
	}

	std::string m_name;
	std::map<std::string, int> m_files;
	std::map<std::string, Directory*> m_children;
	Directory* m_parent = nullptr;
};

Directory* InitializeFileSystem(const char* filePath)
{
	Directory* root = new Directory("", nullptr);
	Directory* currDir = root;
	std::vector<std::string> lines = LineParser(filePath, '\n');

	for (const std::string& line : lines)
	{
		std::vector<std::string> words;
		DivideStringByDelimiter(line, ' ', words);

		if (!currDir)
		{
			return root;
		}

		if (words[0] == "$")
		{
			if (words[1] == "cd")
			{
				if (words[2] == "/")
				{
					currDir = root;
				}
				else if (words[2] == "..")
				{
					currDir = currDir->m_parent;
				}
				else
				{
					currDir = currDir->m_children[words[2]];
				}
			}
			else if (words[1] == "ls")
			{
				// Do nothing for ls now
				continue;
			}
		}
		else if (words[0] == "dir")
		{
			if (currDir->m_children.find(words[1]) == currDir->m_children.end())
			{
				currDir->m_children[words[1]] = new Directory(words[1], currDir);
			}
		}
		else
		{
			if (currDir->m_files.find(words[1]) == currDir->m_files.end())
			{
				currDir->m_files[words[1]] = std::atoi(words[0].c_str());
			}
		}
	}

	return root;
}

int D7P1()
{
	Directory* root = InitializeFileSystem("Inputs/input6");

	int result = root->SumOfDirectoriesBelow(100000);

	delete root;

	return result;
}

int D7P2()
{
	Directory* root = InitializeFileSystem("Inputs/input6");

	int totalSize = root->GetTotalSize();

	int diff = totalSize - 40000000;

	int result = root->FindSmallestDirAbove(diff);

	delete root;

	return result;
}

bool CheckVisibilityUp(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	for (int i = y - 1; i >= 0; --i)
	{
		if (tree <= grid[i][x])
		{
			return false;
		}
	}

	return true;
}

bool CheckVisibilityDown(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	for (size_t i = y + 1; i < grid.size(); ++i)
	{
		if (tree <= grid[i][x])
		{
			return false;
		}
	}

	return true;
}

bool CheckVisibilityLeft(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	for (int i = x - 1; i >= 0; --i)
	{
		if (tree <= grid[y][i])
		{
			return false;
		}
	}

	return true;
}

bool CheckVisibilityRight(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	for (size_t i = x + 1; i < grid[0].size(); ++i)
	{
		if (tree <= grid[y][i])
		{
			return false;
		}
	}

	return true;
}

int D8P1()
{
	std::vector<std::string> grid = LineParser("Inputs/input7", '\n');

	int count = 0;

	for (size_t i = 0; i < grid[0].size(); ++i)
	{
		for (size_t j = 0; j < grid.size(); ++j)
		{
			if (CheckVisibilityUp(grid, i, j) || CheckVisibilityDown(grid, i, j) || CheckVisibilityLeft(grid, i, j) || CheckVisibilityRight(grid, i, j))
			{
				count++;
			}
		}
	}

	return count;
}

int GetViewDistanceUp(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	int count = 0;

	for (int i = y - 1; i >= 0; --i)
	{
		count++;
		if (tree <= grid[i][x])
		{
			return count;
		}
	}

	return count;
}

int GetViewDistanceDown(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	int count = 0;

	for (size_t i = y + 1; i < grid.size(); ++i)
	{
		count++;
		if (tree <= grid[i][x])
		{
			return count;
		}
	}

	return count;
}

int GetViewDistanceLeft(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	int count = 0;

	for (int i = x - 1; i >= 0; --i)
	{
		count++;
		if (tree <= grid[y][i])
		{
			return count;
		}
	}

	return count;
}

int GetViewDistanceRight(const std::vector<std::string>& grid, size_t x, size_t y)
{
	char tree = grid[y][x];

	int count = 0;

	for (size_t i = x + 1; i < grid[0].size(); ++i)
	{
		count++;
		if (tree <= grid[y][i])
		{
			return count;
		}
	}

	return count;
}

int D8P2()
{
	std::vector<std::string> grid = LineParser("Inputs/input7", '\n');

	int highestScore = 0;

	for (size_t i = 0; i < grid[0].size(); ++i)
	{
		for (size_t j = 0; j < grid.size(); ++j)
		{
			int currScore = GetViewDistanceUp(grid, i, j) * GetViewDistanceDown(grid, i, j) * GetViewDistanceLeft(grid, i, j) * GetViewDistanceRight(grid, i, j);
			if (currScore > highestScore)
			{
				highestScore = currScore;
			}
		}
	}

	return highestScore;
}

struct IntVec2
{
	int x = 0;
	int y = 0;

	struct HashFunction
	{
		size_t operator()(const IntVec2& point) const
		{
			size_t xHash = std::hash<int>()(point.x);
			size_t yHash = std::hash<int>()(point.y) << 1;
			return xHash ^ yHash;
		}
	};

	IntVec2() = default;
	IntVec2(int initX, int initY)
	{
		x = initX;
		y = initY;
	}

	bool IsEqual(const IntVec2& other) const
	{
		if (x != other.x)

		{
			return false;
		}

		if (y != other.y)
		{
			return false;
		}

		return true;
	}

	bool operator==(const IntVec2& other) const
	{
		return IsEqual(other);
	}

	bool operator!=(const IntVec2& other) const
	{
		return !IsEqual(other);
	}

	void operator+=(const IntVec2& other)
	{
		x += other.x;
		y += other.y;
	}
};

void UpdateTailByHead(const IntVec2& head, IntVec2& tail)
{
	if (head.x - tail.x >= 2)
	{
		tail.x += 1;
		if (head.y - tail.y > 0)
		{
			tail.y += 1;
		}
		else if (head.y - tail.y < 0)
		{
			tail.y -= 1;
		}
	}

	if (head.y - tail.y >= 2)
	{
		tail.y += 1;
		if (head.x - tail.x > 0)
		{
			tail.x += 1;
		}
		else if (head.x - tail.x < 0)
		{
			tail.x -= 1;
		}
	}

	if (head.x - tail.x <= -2)
	{
		tail.x -= 1;
		if (head.y - tail.y > 0)
		{
			tail.y += 1;
		}
		else if (head.y - tail.y < 0)
		{
			tail.y -= 1;
		}
	}

	if (head.y - tail.y <= -2)
	{
		tail.y -= 1;
		if (head.x - tail.x > 0)
		{
			tail.x += 1;
		}
		else if (head.x - tail.x < 0)
		{
			tail.x -= 1;
		}
	}
}

int D9P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input8", '\n');
	IntVec2 head(0, 0);
	IntVec2 tail(0, 0);

	std::unordered_set<IntVec2, IntVec2::HashFunction> positions;
	positions.insert(tail);

	for (const std::string line : lines)
	{
		std::vector<std::string> words;
		DivideStringByDelimiter(line, ' ', words);
		IntVec2 diff;
		if (words[0] == "U")
		{
			diff = IntVec2(0, 1);
		}
		else if (words[0] == "D")
		{
			diff = IntVec2(0, -1);
		}
		else if (words[0] == "R")
		{
			diff = IntVec2(1, 0);
		}
		else if (words[0] == "L")
		{
			diff = IntVec2(-1, 0);
		}
		int loops = std::atoi(words[1].c_str());
		for (int i = 0; i < loops; ++i)
		{
			head += diff;
			UpdateTailByHead(head, tail);
			positions.insert(tail);
		}
	}

	return positions.size();
}

int D9P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input8", '\n');
	IntVec2 rope[10];

	std::unordered_set<IntVec2, IntVec2::HashFunction> positions;
	positions.insert(rope[1]);

	for (const std::string line : lines)
	{
		std::vector<std::string> words;
		DivideStringByDelimiter(line, ' ', words);
		IntVec2 diff;
		if (words[0] == "U")
		{
			diff = IntVec2(0, 1);
		}
		else if (words[0] == "D")
		{
			diff = IntVec2(0, -1);
		}
		else if (words[0] == "R")
		{
			diff = IntVec2(1, 0);
		}
		else if (words[0] == "L")
		{
			diff = IntVec2(-1, 0);
		}
		int loops = std::atoi(words[1].c_str());
		for (int i = 0; i < loops; ++i)
		{
			rope[0] += diff;
			for(int j = 1; j < 10; ++j)
			{
				UpdateTailByHead(rope[j - 1], rope[j]);
				positions.insert(rope[9]);
			}
		}
	}

	return positions.size();
}

enum class OperationType
{
	ADD_X,
	NOOP
};

struct Operation
{
	OperationType m_type = OperationType::NOOP;
	int m_value = 0;
	int m_loopsRemain = 0;
};

int D10P1()
{
	std::vector<std::string> lines = LineParser("Inputs/input9", '\n');

	int x = 1;

	int result = 0;

	int loopsTaken = 0;
	Operation currOperation;
	int lineIndex = 0;

	for (;lineIndex < lines.size();)
	{
		if (currOperation.m_loopsRemain <= 0)
		{
			// Finish currOperation
			if (currOperation.m_type == OperationType::ADD_X)
			{
				x += currOperation.m_value;
			}

			// Adding new operation
			std::vector<std::string> words;
			DivideStringByDelimiter(lines[lineIndex], ' ', words);

			Operation newOperation;

			if (words[0] == "addx")
			{
				newOperation.m_type = OperationType::ADD_X;
				newOperation.m_value = std::atoi(words[1].c_str());
				newOperation.m_loopsRemain = 2;
			}
			else if (words[0] == "noop")
			{
				newOperation.m_type = OperationType::NOOP;
				newOperation.m_loopsRemain = 1;
			}

			currOperation = newOperation;

			lineIndex++;
		}

		currOperation.m_loopsRemain--;
		loopsTaken++;
		if ((loopsTaken - 20) % 40 == 0)
		{
			result += loopsTaken * x;
		}
	}

	return result;
}

void D10P2()
{
	std::vector<std::string> lines = LineParser("Inputs/input9", '\n');

	int x = 1;

	int loopsTaken = 0;
	Operation currOperation;
	int lineIndex = 0;

	for (; lineIndex < lines.size();)
	{
		if (currOperation.m_loopsRemain <= 0)
		{
			// Finish currOperation
			if (currOperation.m_type == OperationType::ADD_X)
			{
				x += currOperation.m_value;
			}

			// Adding new operation
			std::vector<std::string> words;
			DivideStringByDelimiter(lines[lineIndex], ' ', words);

			Operation newOperation;

			if (words[0] == "addx")
			{
				newOperation.m_type = OperationType::ADD_X;
				newOperation.m_value = std::atoi(words[1].c_str());
				newOperation.m_loopsRemain = 2;
			}
			else if (words[0] == "noop")
			{
				newOperation.m_type = OperationType::NOOP;
				newOperation.m_loopsRemain = 1;
			}

			currOperation = newOperation;

			lineIndex++;
		}

		currOperation.m_loopsRemain--;
		loopsTaken++;

		int rem = loopsTaken % 40 - 1;

		if (abs(rem - x) <= 1)
		{
			std::cout << '#';
		}
		else
		{
			std::cout << '.';
		}
		
		if (rem == -1)
		{
			std::cout << std::endl;
		}
	}
}

int main()
{
	//std::cout << "D1P1 answer is: " << D1P1() << std::endl;
	//std::cout << "D1P2 answer is: " << D1P2() << std::endl;
	//std::cout << "D2P1 answer is: " << D2P1() << std::endl;
	//std::cout << "D2P2 answer is: " << D2P2() << std::endl;
	//std::cout << "D3P1 answer is: " << D3P1() << std::endl;
	//std::cout << "D3P2 answer is: " << D3P2() << std::endl;
	//std::cout << "D4P1 answer is: " << D4P1() << std::endl;
	//std::cout << "D4P2 answer is: " << D4P2() << std::endl;
	//std::cout << "D5P1 answer is: " << D5P1() << std::endl;
	//std::cout << "D5P2 answer is: " << D5P2() << std::endl;
	//std::cout << "D6P1 answer is: " << D6P1() << std::endl;
	//std::cout << "D6P1 answer is: " << D6P2() << std::endl;
	//std::cout << "D7P1 answer is: " << D7P1() << std::endl;
	//std::cout << "D7P2 answer is: " << D7P2() << std::endl;
	//std::cout << "D8P1 answer is: " << D8P1() << std::endl;
	//std::cout << "D8P2 answer is: " << D8P2() << std::endl;
	//std::cout << "D9P1 answer is: " << D9P1() << std::endl;
	//std::cout << "D9P2 answer is: " << D9P2() << std::endl;
	//std::cout << "D10P1 answer is: " << D10P1() << std::endl;
	//D10P2();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
