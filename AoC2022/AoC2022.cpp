// AoC2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

int main()
{
	std::cout << "D1P1 answer is: " << D1P1() << std::endl;
	std::cout << "D1P2 answer is: " << D1P2() << std::endl;
	std::cout << "D2P1 answer is: " << D2P1() << std::endl;
	std::cout << "D2P2 answer is: " << D2P2() << std::endl;
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
