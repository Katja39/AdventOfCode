#include <iostream>
#include <fstream>
#include <string>

void NotQuiteLisp() {
	std::cout << "Part 1, Final Floor:";

	std::ifstream input("files/fileDay1.txt");

	if (!input)
	{
		std::cerr << "Problem opening the file " << "\n";
	}

	std::string line;
	std::getline(input, line);
	
	int floor = 0;

	for (int i = 0; i < line.size(); i++)
	{
		 if (line[i] == '(') {
			 floor++;
		 }
		 else if (line[i] == ')') {
			 floor--;
		 }
	}

	std::cout <<"\nFloor:" << floor<<"\n\n";

	std::cout << "Part Two, First enter the basement\n";
	
	floor = 0;

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '(') {
			floor++;
		}
		else if (line[i] == ')') {
			floor--;
			if (floor <= -1) {
				std::cout << "In Basement after " << i + 1 << " rounds\n";
				break;
			}
		}
	}
}