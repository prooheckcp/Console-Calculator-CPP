#pragma once
template<class T>
class DynamicArray
{
public:
	
	//Constructor(s)
	DynamicArray();

	//Add an element into the array either at the end or at a pre-defined position
	void Add(T character);
	void Add(T character, int position);

	//Retreive the element of this array at this index
	T& Get(int index);
	
	//Remove all the elements between a range (putting a single index removes a single value)
	void Remove(int index);
	void Remove(int index, int index2);

	//A combination of add with remove
	void Replace(T character, int index, int index2);

	//Prints the contents in a fancy way
	void Print();
	
	//Get the current reserved size of the array
	int GetSize();

private:

	//Store the length of the array
	int Size;
	//Store the array itself
	T* DynamicList;
};

