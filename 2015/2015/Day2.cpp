#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void IWasToldThereWouldBeNoMath() {

	std::cout << "Part 1, Sum of square feet:";

	std::ifstream input("fileDay2.txt");

	if (!input)
	{
		std::cerr << "Problem opening the file " << "\n";
	}

	std::string line;
	std::string delimiter = "x";
	std::string token;

	//number of lines in file

	std::ifstream inFile("fileDay2.txt");
	int counter = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');

	int length = 0;
	int width = 0;
	int height = 0;

	int sumOfSquareFeet = 0;
	int sumFeetOfRibbon = 0;

	std::cout <<"Number of presents " << counter << "\n";

	for (size_t i = 0; i < 1000; i++)
	{
		std::getline(input, line);
		token = line.substr(0,line.find(delimiter));

		//debug
		std::istringstream(token) >> length;
		std::cout <<"\nlength:" << length << "\n";

		line = line.substr(0 + delimiter.length());
		line.erase(0, line.find(delimiter) + delimiter.length());

		token = line.substr(0, line.find(delimiter));
		
		//debug
		std::istringstream(token) >> width;
		std::cout << "\nwidth:" << width << "\n";

		line = line.substr(0 + delimiter.length());
		line.erase(0, line.find(delimiter) + delimiter.length());

		token = line.substr(0, line.find(delimiter));

		//debug
		std::istringstream(token) >> height;
		std::cout <<"\nheight:" << height << "\n\n";

		//Calculate surface area

		int areas[3] = {0,0,0};
		int smallestSideValue = 1000;

		areas[0] = length * width;
		areas[1] = width * height;
		areas[2] = height * length;

		for (size_t n = 0; n < 3; n++)
		{
			if (smallestSideValue > areas[n])
			{
				smallestSideValue = areas[n];
			}	
		}
		for (size_t m = 0; m < 3; m++)
		{
			sumOfSquareFeet += areas[m]*2;
		}
		std::cout << "Smallest Side: " << smallestSideValue<<"\n";

		sumOfSquareFeet += smallestSideValue;

		std::cout <<"Square Feet Round "<<i <<": " << sumOfSquareFeet<<"\n";
	
	//Part 2, Ribbon

	int shortestDistance = 1000000;
	
	
	shortestDistance = 2 * length + 2 * width;

	if (shortestDistance > 2 * length + 2 * height)
	{
		shortestDistance = 2 * length + 2 * height;
	}
	if (shortestDistance > 2 * width + 2 * height)
	{
		shortestDistance = 2 * width + 2 * height;
	}

	int bow = length * width * height;

	sumFeetOfRibbon += shortestDistance + bow;
	std::cout << "Ribbon: " << sumFeetOfRibbon << "\n";
	std::cout << "---------------------------\n";
	} //lines
}