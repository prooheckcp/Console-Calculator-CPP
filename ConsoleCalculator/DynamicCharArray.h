#pragma once
template<typename T>
class DynamicCharArray
{
	public:
		DynamicCharArray();
		void Add(T character);
		T Get(int index);
		void Remove(int index);
		void Remove(int index, int index2);
		void Print();
		int GetSize();

	private:
		int Size;
		T* DynamicList;

};

