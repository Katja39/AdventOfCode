#include "Day1.h"
#include <iostream>

void main() {
	int number;
	bool exit=false;

	std::cout << "Advent of Code 2015\n";

	do {
	std::cout << "\nChoose the day\n";
	std::cout << "Press 0 to quit\n";
	std::cin >> number;

	switch (number)
	{
	case 0:
		exit = true;
		break;

	case 1:
		NotQuiteLisp();
		break;
	}

	} while (exit==false);
}