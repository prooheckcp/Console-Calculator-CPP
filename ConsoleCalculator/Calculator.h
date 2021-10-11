#pragma once
#include "DynamicArray.h"
#include "DynamicArray.cpp"

class Calculator
{
	public:
		double Calculate(DynamicArray<char> dynamicArray);

	private:

		//Validates weather the equation can be calculated or not
		bool validateEquation(DynamicArray<char> dynamicArray);

		//Validate parentheses existence
		bool ValidateParentheses(DynamicArray<char> string);

		//Seperates the math equation into something readable by the block operation
		DynamicArray<DynamicArray<char>> seperateEquation(DynamicArray<char> dynamicArray);

		//Calculates a block of math equations based on the given operator
		void BlockOperation(DynamicArray<DynamicArray<char>> &dynamicArray, char operatorSign);

		//Calculates a block of code in a more simplified way than blockOperation
		double CalculateBlock(DynamicArray<char> dynamicArray);

		//Converts a string into a number
		double toNumber(DynamicArray<char> num);

		//Converts a number into a string
		template<typename T>
		DynamicArray<char> toArray(T num);
};

