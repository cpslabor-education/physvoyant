#ifndef DARRAY
#define DARRAY

#include <iostream>

template<class T>
class DArray
{
public:
	DArray() : capacity(8)
	{
		Init(capacity);
	}

	DArray(unsigned int capacity) : capacity(capacity)
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

	void operator=(const DArray& other)
	{
		this->capacity = other.capacity;
		Init(capacity);
		for (unsigned int i = 0; i < capacity; i++)
		{
			this->internalArray[i] = other.internalArray[i];
		}
	}

	T& operator[](unsigned int index)
	{
		if (index >= capacity)
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
	void Init(unsigned int size)
	{
		if (size > 0) // Mert 0 méretre is foglal címet >:(
		{
			internalArray = (T*)calloc(size, sizeof(T)); 
		}
		else
		{
			internalArray = nullptr;
		}
	}

	T* internalArray;
	unsigned int capacity;
};

#endif // !DARRAY
