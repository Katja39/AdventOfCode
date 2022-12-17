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

	std::ifstream input("fileDay5.txt");

	if (!input)
	{
		std::cerr << "Problem opening the file " << "\n";
	}

	std::string line;
	int counter = 0;
	std::string vowels = "aeiou";
	int numberOfVowels = 0;
	bool ruleTwoIsTrue = false;
	std::string forbiddenStrings[4] = {"ab","cd","pq","xy"};


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
					//falsche kombinationen enthalten
				}
			}

			if (isIncluded == false)
			{
				counter++;
				std::cout << line << std::endl;
			}
		}
	}

	std::cout << "\nNumber of right lines " << counter;

	//Part2

	/*	It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
		It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.*/
}