#ifndef DARRAY
#define DARRAY

#include "DArray.hpp"

template<class T>
inline DArray<T>::DArray()
{
	Init(0);
}

template<class T>
DArray<T>::DArray(int capacity)
{
	Init(capacity);
}

template<class T>
DArray<T>::DArray(DArray& other)
{
	Init(other.capacity);
	static_assert(false);
}

template<class T>
DArray<T>::~DArray()
{
	delete[] handleArr;
}

template<class T>
inline void DArray<T>::Init(int size)
{
	
}

#endif // !DARRAY