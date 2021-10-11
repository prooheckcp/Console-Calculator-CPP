#pragma once
#include "DynamicArray.h"
#include <iostream>

/*
	Remade the Lists from Lua into c++ and added the Replace function just cause it was useful for the calculator
*/

/*
Construnctor just sets the size of the array to 0
*/
template<class T>
DynamicArray<T>::DynamicArray()
{
	this->Size = 0;
}

template<class T>
void DynamicArray<T>::Remove(int index) {
	this->Remove(index, index);
}

template<class T>
void DynamicArray<T>::Remove(int index, int index2) {

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

template<class T>
void DynamicArray<T>::Add(T character) {
	this->Add(character, this->Size);
}

template<class T>
void DynamicArray<T>::Add(T character, int position) {

	if (this->Size <= 0) {
		this->DynamicList = new T[]{ character };
	}
	else {
		T* newArray = new T[this->Size + 1];
		int j = 0;
		for (int i = 0; i < this->Size; i++) {

			if (i == position)
				j++;

			newArray[j] = this->DynamicList[i];
			j++;
		}
		newArray[position] = character;
		this->DynamicList = newArray;
	}
	this->Size += 1;
}

template<class T>
T& DynamicArray<T>::Get(int index) {
	if (this->Size == 0 || index >= this->Size) {
		std::cout << "Error: index is larger than the function!" << std::endl;
		T defaultRes = T();
		return defaultRes;
	}
	else {
		return this->DynamicList[index];
	}
}

template<class T>
void DynamicArray<T>::Replace(T character, int index, int index2) {
	this->Remove(index, index2);
	this->Add(character, index);
}

template<class T>
void DynamicArray<T>::Print() {

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

template<class T>
int DynamicArray<T>::GetSize() {
	return this->Size;
}