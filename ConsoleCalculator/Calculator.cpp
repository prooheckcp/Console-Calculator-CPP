#include "Calculator.h"
#include "DynamicArray.h"
#include "DynamicArray.cpp"
#include <iostream>

/*
This calculator module utilizes the DynamicCharArray
*/

//Constants||
const int OPERATOR_LENGTH = 4;
const int IGNORE_LENGTH = 1;
const int PARENTHESES_LENGTH = 2;

const char operators[OPERATOR_LENGTH] {'*', '/', '-', '+'}; //These are ordered by priority
const int ignoreList[IGNORE_LENGTH]{(int)' '}; 
const int PARENTHESES_LIST[PARENTHESES_LENGTH]{ (int)'(', (int)')' }; //Used for nesting equations

const int NUMBER_ASCII_MIN = (int)'0';
const int NUMBER_ASCII_MAX = (int)'9';
//_________||

//Helper methods||
bool isOperator(char character) {
	int characterASCII = (int)character;
	for (int i = 0; i < OPERATOR_LENGTH; i++) {
		if (operators[i] == characterASCII)
			return true;
	}
	return false;
}

bool isSpace(char character) {
	int characterASCII = (int)character;
	for (int i = 0; i < IGNORE_LENGTH; i++) {
		if (ignoreList[i] == characterASCII)
			return true;
	}
	return false;
}

bool isNumber(char character) {
	int characterASCII = (int)character;
	return characterASCII >= NUMBER_ASCII_MIN && characterASCII <= NUMBER_ASCII_MAX;
}

void AddIntToArray(double intNum, DynamicArray<char>& result) {
	if (intNum >= 10)
		AddIntToArray(intNum / 10, result);

	double cleanedInt = floor(fmod(intNum, 10));
	char newChar = (cleanedInt + (int)'0');
	result.Add(newChar);
}
//______________||

double Calculator::Calculate(DynamicArray<char> dynamicArray) {
	double result = 0.0;

	//Checks if it is possible to calculate teh equation
	bool canCalculate = this->validateEquation(dynamicArray) && this->ValidateParentheses(dynamicArray);
	if (!canCalculate) 
		std::cout << "Error: Invalid equation input" << std::endl;
	else {

		bool repeat = true;
		while (repeat) {

			int leftParatheses = -1;
			int rightParantheses = -1;
			for (int i = 0; i < dynamicArray.GetSize(); i++) {
				char character = dynamicArray.Get(i);
				if (character == '(')
					leftParatheses = i;
				else if (character == ')') {
					rightParantheses = i;
					break;
				}
			}

			if (leftParatheses < 0)
				repeat = false;
			else {
				DynamicArray<char> nestedValues;
				for (int i = leftParatheses + 1; i < rightParantheses; i++) {
					nestedValues.Add(dynamicArray.Get(i));
				}
				
				DynamicArray<char> string;
				if (nestedValues.GetSize() >= 1) {
					double nestedResult = this->CalculateBlock(nestedValues);
					string = this->toArray(nestedResult);
				}				

				dynamicArray.Remove(leftParatheses, rightParantheses);
				
				for (int i = string.GetSize() - 1; i >= 0; i--) {
					dynamicArray.Add(string.Get(i) ,leftParatheses);
				}

			}

		}

		result = this->CalculateBlock(dynamicArray);

		std::cout << "The result is: " << result << std::endl;

	}

	return result;
}

double Calculator::toNumber(DynamicArray<char> number) {
	bool isNegative = (number.Get(0) == '-');

	if (isNegative)
		number.Remove(0);

	double result = 0;

	int dotPosition = -1;
	for (int i = 0; i < number.GetSize(); i++) {
		if (number.Get(i) == '.') {
			dotPosition = i;
			break;
		}
	}

	int currentDisplacement = (dotPosition > 0) ? pow(10, dotPosition - 1) : pow(10, number.GetSize() - 1);
	for (int i = 0; i < number.GetSize(); i++) {
		char character = number.Get(i);
		if (i != dotPosition) {
			int absoluteInt = (int)character - (int)'0';
			if (i < dotPosition || dotPosition == -1) {
				result += absoluteInt * currentDisplacement;
				currentDisplacement /= 10;
			}
			else {
				result += (double)absoluteInt / pow(10, (i - dotPosition));
			}
		}
	}

	if (isNegative)
		result *= -1;

	return result;
}

template<typename T>
DynamicArray<char> Calculator::toArray(T num) {

	//Numbers that will be used for calculations
	int wholeInt = floor(abs(num));
	int fractionAsInt = 0;

	double fraction = fmod(abs(num), 1);

	bool hasFraction = (fraction > 0);

	if (hasFraction) {
		double wholeNumClone = num;
		int displacementSize = 0;

		while (fmod(abs(wholeNumClone), 1) != 0) {
			wholeNumClone *= 10;
			displacementSize++;
		}

		fractionAsInt = round(fraction * pow(10, displacementSize));
	}

	DynamicArray<char> result;

	if (num < 0)
		result.Add('-');

	//Add main part of the number
	if (wholeInt == 0) {
		result.Add('0');
	}
	else {
		int intClone = abs(wholeInt);
		AddIntToArray(intClone, result);
	}

	//Add decimal part
	if (hasFraction) {
		result.Add('.');
		int intClone = abs(fractionAsInt);
		AddIntToArray(intClone, result);
	}


	return result;
}

bool Calculator::ValidateParentheses(DynamicArray<char> string) {
	int left = 0;
	int right = 0;
	for (int i = 0; i < string.GetSize(); i++) {
		char character = string.Get(i);
		if (character == '(')
			left++;
		else if (character == ')') {
			if (left <= right)
				return false;
			else
				right++;
		}
	}
	return left == right;
}

double Calculator::CalculateBlock(DynamicArray<char> dynamicArray) {
	DynamicArray<DynamicArray<char>> cleanedArray = this->seperateEquation(dynamicArray);
	do {
		for (int i = 0; i < OPERATOR_LENGTH; i++) {
			this->BlockOperation(cleanedArray, operators[i]);
		}

	} while (cleanedArray.GetSize() > 1);

	return this->toNumber(cleanedArray.Get(0));
}

/*
Calculation operations
*/
void Calculator::BlockOperation(DynamicArray<DynamicArray<char>> &dynamicArray, char operatorSign) {
	bool repeat = false;

	do {
		repeat = false;
		for (int i = 0; i < dynamicArray.GetSize(); i++) {
			DynamicArray<char> string = dynamicArray.Get(i);
			if (string.GetSize() == 1 && (int)string.Get(0) == (int)operatorSign) {
				DynamicArray<char> num1 = dynamicArray.Get(i - 1);
				DynamicArray<char> num2 = dynamicArray.Get(i + 1);
				double num3 = 0;

				switch (operatorSign)
				{
					case '*':
						num3 = toNumber(num1) * toNumber(num2);
						break;
					case '/':
						num3 = toNumber(num1) / toNumber(num2);
						break;
					case '+':
						num3 = toNumber(num1) + toNumber(num2);
						break;
					case '-':
						num3 = toNumber(num1) - toNumber(num2);
						break;
				}

				DynamicArray<char> numString = this->toArray(num3);
				dynamicArray.Replace(numString, i - 1, i + 1);
				repeat = true;
				break;
			}
		}
	} while (repeat);
}

/*
	Seperates the equation into a more readable format
	It seperates into: Number, operator, Number, operator etc
*/
DynamicArray<DynamicArray<char>> Calculator::seperateEquation(DynamicArray<char> dynamicArray) {

	//Account for operation blocks that start with a - as this is possible
	if (dynamicArray.Get(0) == '-') {
		dynamicArray.Add('0', 0);
	}

	DynamicArray<DynamicArray<char>> result;

	int currentIndex = 0;
	for (int i = 0; i < dynamicArray.GetSize(); i++) {
		char character = dynamicArray.Get(i);
		bool isOp = isOperator(character);
		bool isIgnore = isSpace(character);

		if (isIgnore)
			continue;

		if (isOp)
			currentIndex++;

		if (result.GetSize() > currentIndex) {
			DynamicArray<char> string = result.Get(currentIndex);
			string.Add(character);
			result.Get(currentIndex) = string;
		}
		else {
			DynamicArray<char> string;
			string.Add(character);
			result.Add(string);
		}

		if (isOp) 
			currentIndex++;
	}
	return result;
}

bool Calculator::validateEquation(DynamicArray<char> dynamicArray) {
	bool wasOperator = false;
	bool wasNumber = false;
	for (int i = 0; i < dynamicArray.GetSize(); i++) {
		char character = dynamicArray.Get(i);

		if (i == 0 && character == '-')
			continue;

		bool isInt = isNumber(character);
		bool isOp = isOperator(character);
		bool isIgnore = isSpace(character) || character == '(' || character == ')';

		if(isOp) {
			if (!wasNumber)
				return false;
		}
		else if(!isIgnore && !isInt){
			return false;
		}

		//If we are supposed to ignore this character then do not update!
		if (!isIgnore) {
			wasOperator = isOp;
			wasNumber = isInt;
		}
	}
	return !wasOperator;
}