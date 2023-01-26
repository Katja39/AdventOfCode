#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void PerfectlySphericalHousesInAVacuum() 
{
	///////////////////////////////////
	//Part One: Santa Presents////////
	//////////////////////////////////

	std::cout << "Part 1: Santa\n";

	std::ifstream input("files/fileDay3.txt");

	if (!input)
	{
		std::cerr << "Problem opening the file " << "\n";
	}

	std::string line;
	std::getline(input, line);

	int positionsX[3000] = {0};
	int positionsY[3000] = {0};
	int positionsValue[3000] = {0};

	int currentPositionX = 0;
	int currentPositionY = 0;

	positionsX[0] = currentPositionX;
	positionsY[0] = currentPositionY;
	positionsValue[0]++;

	int isFilled = true;
	int index = 0; 

	for (int i = 0; i < line.size(); i++)
	{
		isFilled = true;
		index = 0;

		while (isFilled)
		{
			if (positionsValue[index] == 0)
			{
				isFilled = false;
			}
			else
			{
				if (positionsX[index] == currentPositionX && positionsY[index] == currentPositionY)
				{
					//already visited house
					positionsValue[index]++;
					break;
				}
			}
			if (index < 3000)
			{
				index++;
			}
			else 
			{
				isFilled = false;
				break;
			}
		}

		if (isFilled == false)
		{
			//new House
			positionsX[index-1] = currentPositionX;
			positionsY[index-1] = currentPositionY;
			positionsValue[index-1]++;
		}

		//newPositions

		if (line[i] == '^') 
		{
			currentPositionY++;
		}
		else if (line[i] == '<') 
		{
			currentPositionX--;

		}
		else if (line[i] == '>') 
		{
			currentPositionX++;
		}
		else if (line[i] == 'v') 
		{
			currentPositionY--;
		}
	}


	int numberOfHousesWithOnePresent = 0;

	for (size_t i = 0; i < 3000; i++)
	{
		if (positionsValue[i] >= 1)
		{
			numberOfHousesWithOnePresent++;
		}
	}

	std::cout << "\nNumber of houses with more than one present (only santa): " << numberOfHousesWithOnePresent<<"\n";


	///////////////////////////////////
	//Part Two: Santa and Robo Santa//
	//////////////////////////////////

	std::cout << "\n\nPart Two: Santa and Robo Santa";

	for (int i = 0; i < 3000; i++)
	{
		positionsX[i] = 0;
		positionsY[i] = 0;
		positionsValue[i] = 0;
	}

	int currentPositionXArray[2] = {0}; //0=Santa, 1=RoboSanta
	int currentPositionYArray[2] = {0};

	//StartPosition
	positionsX[0] = currentPositionX;
	positionsY[0] = currentPositionY;
	positionsValue[0]++;

	for (int i = 0; i < line.size(); i++)
	{

		isFilled = true;
		index = 0;

		while (isFilled)
		{
			if (positionsValue[index] == 0)
			{
				isFilled = false;
			}
			else
			{
				if (positionsX[index] == currentPositionXArray[i%2] && positionsY[index] == currentPositionYArray[i%2])
				{
					//already visited house
					positionsValue[index]++;
					break;
				}
			}
			if (index < 3000)
			{
				index++;
			}
			else
			{
				isFilled = false;
				break;
			}
		}

		if (isFilled == false)
		{
			//new House
			positionsX[index - 1] = currentPositionXArray[i%2];
			positionsY[index - 1] = currentPositionYArray[i%2];
			positionsValue[index - 1]++;
		}

		//newPositions

		if (line[i] == '^')
		{
			currentPositionYArray[i%2]++;
		}
		else if (line[i] == '<')
		{
			currentPositionXArray[i%2]--;

		}
		else if (line[i] == '>')
		{
			currentPositionXArray[i%2]++;
		}
		else if (line[i] == 'v')
		{
			currentPositionYArray[i%2]--;
		}
	}


	numberOfHousesWithOnePresent = 0;

	for (size_t i = 0; i < 3000; i++)
	{
		if (positionsValue[i] >= 1)
		{
			numberOfHousesWithOnePresent++;
		}
	}

	std::cout << "\nNumber of houses with more than one present (santa and robo santa): " << numberOfHousesWithOnePresent << "\n";
}

