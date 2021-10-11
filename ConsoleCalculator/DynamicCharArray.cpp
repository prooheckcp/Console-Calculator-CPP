#include "DynamicCharArray.h"
#include <iostream>

/*
Simple module to replace the vector module since we cannot use it 
*/


/*
	Removes a certain character from the list, it can either be a range
	or just one element
*/

template<typename T>
DynamicCharArray<T>::DynamicCharArray()
{
	this->Size = 0;
}

template<typename T>
void DynamicCharArray<T>::Remove(int index) {
	this->Remove(index, index);
}

template<typename T>
void DynamicCharArray<T>::Remove(int index, int index2) {

	//Block impossible ranges
	if (index2 < index) {
		std::cout << "ERROR: index2 cannot be smaller than index1 in Remove() range" << std::endl;
		return;
	}

	int amountRemoved = index2 - index + 1;
	T* newArray = new T[this->Size - amountRemoved];

	int j = 0;
	for (int i = 0; i < this->Size; i++) {
		if (i < index || i > index2) {
			newArray[j] = this->DynamicList[i];
			j++;
		}
	}

	this->DynamicList = newArray;
	this->Size -= amountRemoved;
}

/*
	Adds a new character to this array
*/
template<typename T>
void DynamicCharArray<T>::Add(T character) {

	if (this->Size <= 0) {
		this->DynamicList = new T[] {character};
	}
	else {
		T* newArray = new T[this->Size + 1];
		for (int i = 0; i < this->Size; i++) {
			newArray[i] = this->DynamicList[i];
		}
		newArray[this->Size] = character;
		this->DynamicList = newArray;
	}
	this->Size += 1;
}

/*
Get value at certain point
*/
template<typename T>
T DynamicCharArray<T>::Get(int index) {
	if (index >= this->Size) {
		std::cout << "Error: index is larger than the function!" << std::endl;
		return '_';
	}
	else {
		return this->DynamicList[index];
	}
}

/*
	Prints the array in a pretty and readable way in the console
*/
template<typename T>
void DynamicCharArray<T>::Print() {
	if (this->Size <= 0) {
		std::cout << "This array is currently empty!" << std::endl;
	}
	else {
		std::cout << "Dynamic Array = {";
		for (int i = 0; i < this->Size; i++) {

			if (i > 0)
				std::cout << ", ";
			std::cout << this->DynamicList[i];
		}
		std::cout << "}" << std::endl;
	}
}
template<typename T>
int DynamicCharArray<T>::GetSize() {
	return this->Size;
}