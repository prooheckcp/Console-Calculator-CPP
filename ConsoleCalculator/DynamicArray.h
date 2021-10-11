#pragma once
template<class T>
class DynamicArray
{
public:
	DynamicArray();
	void Add(T character);
	void Add(T character, int position);

	T& Get(int index);
	
	void Remove(int index);
	void Remove(int index, int index2);
	void Replace(T character, int index, int index2);

	void Print();
	
	int GetSize();

private:
	int Size;
	T* DynamicList;
};

