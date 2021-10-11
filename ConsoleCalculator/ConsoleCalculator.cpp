//Includes||
#include <iostream>
#include <string>

#include "DynamicArray.h"
#include "DynamicArray.cpp"

#include "Calculator.h"
//________||

//Constants||

//_________||

//Variables||
DynamicArray<char> userInput;
Calculator calculator;
//_________||

//Declare method||
DynamicArray<char> getInput();
//______________||

int main()
{
	while (true) {
		DynamicArray<char> response = getInput();
		double result = calculator.Calculate(response);
	}	
}


DynamicArray<char> getInput() {

	//Get user input
	std::string userInputRaw;
	std::cout << "Insert math equation: ";
	std::getline(std::cin, userInputRaw);
	const char* localUserInput = userInputRaw.c_str();
	DynamicArray<char> newDynamicArray;

	for (int i = 0; i < userInputRaw.size(); i++) {
		newDynamicArray.Add(localUserInput[i]);
	}

	return newDynamicArray;
}
