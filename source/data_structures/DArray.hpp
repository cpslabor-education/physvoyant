#ifndef DARRAY
#define DARRAY

#include <iostream>

template<class T>
class DArray
{
public:
	DArray() : capacity(2)
	{
		Init(capacity);
	}

	DArray(int capacity) : capacity(capacity)
	{
		Init(capacity);
	}

	DArray(DArray& other);

	~DArray()
	{
		free(internalArray);
	}

	//void Empty();

	void Resize(unsigned int newCapacity)
	{
		capacity = newCapacity;
		realloc(internalArray, newCapacity);
	}

	void ShrinkToFit();

	void operator=(const DArray& other);

	T& operator[](int index)
	{
		if (index < 0 || index >= capacity)
		{
			throw std::out_of_range("Index out of range");
		}
		return internalArray[index];
	}

	unsigned int Capacity()
	{
		return capacity;
	}

private:
	void Init(int size)
	{
		internalArray = (T*)calloc(size, sizeof(T));
	}

	T* internalArray;
	unsigned int capacity;
};

#endif // !DARRAY_H
