#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

int position[2];
int direction[2];

void divideString(int state, std::string line) 
{
	std::size_t positionOfSecondNumbers = line.find("through");

	int firstPositions[3] = { 7,8,6 }; //turn on = 7, turn off = 8, toggle = 6

	//positions
	std::size_t posComma = line.find(",");
	
	std::string n = line.substr(firstPositions[state], posComma - firstPositions[state]);
	position[0] = std::stoi(n);

	std::size_t posThrough = line.find("th");
	n = line.substr(firstPositions[state]+(posComma - firstPositions[state])+1, (posThrough - posComma)-1);
	position[1] = std::stoi(n);

	//std::cout <<"\n" << position[0] << ";" << position[1];
	
	//directions
	std::size_t posH = line.find("gh");
	std::string secondSubString = line.substr(posH+2);
	posComma = secondSubString.find(",");

	direction[0] = std::stoi(secondSubString.substr(1, posComma));
	direction[1] = std::stoi(secondSubString.substr(posComma+1));

	//std::cout << " " << direction[0] << ";" << direction[1] << std::endl;
}


void ProbablyAFireHazard()
{
	//one million lights in 1000x1000 grid
	//lights 0->999

	std::cout << "Part 1\n";

	std::ifstream input("files/fileDay6.txt");

	if (!input)
	{
		std::cerr << "Problem opening the file " << "\n";
	}

	bool lights[1000][1000] = { false };

	int** brightness = new int* [1000] {0};
	for (int i = 0; i < 1000; ++i) {
		brightness[i] = new int[1000] {0};
	}


	std::string line;
	std::string firstInstruction;
	std::string secondInstruction;
	

	int state = 0; //1=turn on, 2=turn off, 3=toggle

	double totalBrightness = 0;

	for (size_t i = 0; i < 300; i++)//number of Lines
	{
		std::getline(input, line);
		
		state = 3;

		firstInstruction = line.substr(0, 4);

		//state
		if (firstInstruction == "togg")
		{
			//toggle
			state = 2;
		}
		else
		{
			secondInstruction = line.substr(5, 2);

			if (secondInstruction == "on")
			{
				//on
				state = 0;
			}
			else if (secondInstruction == "of")
			{
				//off
				state = 1;
			}
			else
			{
				std::cout << "Error!";
			}
		}

		divideString(state, line);

		for (int i = position[0]; i <= direction[0]; i++)
		{
			for (int n = position[1]; n <= direction[1]; n++)
			{
				switch (state)
				{
				case 0:
					lights[i][n] = true;

					brightness[i][n]++;
					break;

				case 1:
					lights[i][n] = false;

					if (brightness[i][n] > 0)
					{
						brightness[i][n]--;
					}
					break;

				case 2:
					lights[i][n] = !lights[i][n];

					brightness[i][n] = brightness[i][n]+2;
					break;
				default:
					break;
				}
			}
		}
	}

	int counter = 0; //lit lights


	for (int i = 0; i < 1000; i++)
	{
		for (int n = 0; n < 1000; n++)
		{
			if (lights[i][n] == true)
			{
				counter++;
			}
			totalBrightness += brightness[i][n];
		}
	}

	std::cout << "Lit Lights: " << counter<<std::endl;

	std::cout << "\nPart 2"<<std::endl;

	std::cout << std::setprecision(25);
	std::cout << "Total Brightness:" << totalBrightness;

	for (int i = 0; i < 1000; ++i) {
		delete[] brightness[i];
	}
	delete[] brightness;
}