#include <iostream>
#include <fstream>
#include <string>

void NotQuiteLisp() {
	std::ifstream input("file.txt");

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
	std::cout <<"\nFloor:" << floor<<"\n";
}