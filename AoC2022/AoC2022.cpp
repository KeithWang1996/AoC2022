// AoC2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

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

int main()
{
	std::cout << "D1P1 answer is: " << D1P1() << std::endl;
	std::cout << "D1P2 answer is: " << D1P2() << std::endl;
	std::cout << "D2P1 answer is: " << D2P1() << std::endl;
	std::cout << "D2P2 answer is: " << D2P2() << std::endl;
	std::cout << "D3P1 answer is: " << D3P1() << std::endl;
	std::cout << "D3P2 answer is: " << D3P2() << std::endl;
	std::cout << "D4P1 answer is: " << D4P1() << std::endl;
	std::cout << "D4P2 answer is: " << D4P2() << std::endl;
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
