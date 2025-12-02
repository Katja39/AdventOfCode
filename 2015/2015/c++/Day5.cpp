#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void DoesntHeHaveInternElvesForThis()
{
	//Part1
	
	/*Rules:
	It contains at least three vowels(aeiou only)
	It contains at least one letter that appears twice in a row, like xx, abcdde(dd), or aabbccdd(aa, bb, cc, or dd).
	It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.*/

	std::ifstream input("./files/fileDay5.txt");

	std::string line;
	int counter = 0;
	std::string vowels = "aeiou";
	int numberOfVowels = 0;
	bool ruleTwoIsTrue = false;
	std::string forbiddenStrings[4] = { "ab","cd","pq","xy" };

	if (!input)
	{
		std::cerr << "Problem opening the file " << "\n";
	}
	else 
	{
	for (int i = 0; i < 1000; i++)
	{
		std::getline(input, line);
		ruleTwoIsTrue = false;
		numberOfVowels = 0;

		//Rule1
		for (size_t m = 0; m < line.size(); m++)
		{
			for (size_t n = 0; n < size(vowels); n++)
			{
				if (line[m] == vowels[n])
				{
					numberOfVowels++;
				}

				if (numberOfVowels >= 3)
				{
					break;
				}
			}
		}

		//Rule2
		if (numberOfVowels >= 3)
		{
			for (size_t m = 0; m < line.size()-1; m++)
			{
				if (line[m] == line[m + 1])
				{
					ruleTwoIsTrue = true;
					break;
				}
			}
		}

		//Rule3
		if (ruleTwoIsTrue == true)
		{
			ruleTwoIsTrue = false;
			bool isIncluded = false;

			for (size_t m = 0; m < size(forbiddenStrings); m++)
			{
				if (line.find(forbiddenStrings[m]) != std::string::npos)
				{
					isIncluded = true;
					break;
				}
			}

			if (isIncluded == false)
			{
				counter++;
				//std::cout << line << std::endl;
			}
		}
	}
	}

	std::cout << "\nNumber of right lines in part 1: " << counter<<"\n";

	//Part2

	/*	It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
		It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.*/

	std::ifstream inputPartTwo("fileDay5.txt");
	line = " ";

	char firstPairPartOne;
	char firstPairPartTwo;
	char secondPairPartOne;
	char secondPairPartTwo;

	bool containsPair = false;
	int counterPartTwo = 0;

	bool stop = false;

	for (int i = 0; i < 1000; i++)
	{
		std::getline(inputPartTwo, line);
		containsPair = false;
		stop = false;

		for (size_t m = 0; m < line.size(); m++)
		{
			if (stop == true)
			{
				break;
			}
			else 
			{
				//firstPair
				firstPairPartOne = line[m];
				firstPairPartTwo = line[m + 1];


				for (size_t i = m + 2; i < line.size(); i++)
				{
					if (i < line.size())
					{
						//secondPair
						secondPairPartOne = line[i];
						secondPairPartTwo = line[i + 1];

						if (secondPairPartOne == firstPairPartOne && secondPairPartTwo == firstPairPartTwo)
						{
							containsPair = true;
							stop = true;
							break;
						}
					}
					else {
						stop = true;
						break;
					}
			}

			}
		}

		if (containsPair == true)
		{
			for (size_t i = 0; i < line.size()-2; i++)
			{
				char firstLetter = line[i];
				char thirdLetter = line[i + 2];
				if (firstLetter == thirdLetter)
				{
					counterPartTwo++;
					//std::cout << line << std::endl;
					break;
				}
			}
		}
	}

	std::cout << "Number of right lines in part 2: " << counterPartTwo<<std::endl;
}
