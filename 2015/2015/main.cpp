#include "Day1.h"
#include "Day2.h"
#include <iostream>

void main() {
	int number;
	bool exit=false;

	std::cout << "Advent of Code 2015\n";

	do {
	std::cout << "\n--------------------";
	std::cout << "\nChoose the day\n";
	std::cout << "Press 0 to quit\n";
	std::cin >> number;
	std::cout << "--------------------\n";

	switch (number)
	{
	case 0:
		exit = true;
		break;

	case 1:
		NotQuiteLisp();
		break;
	case 2:
		IWasToldThereWouldBeNoMath();
	}
	} while (exit==false);
}