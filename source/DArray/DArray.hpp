#ifndef DARRAY_H
#define DARRAY_H

template<class T> class DArray;

template<class T>
class DArray
{
public:
	DArray();

	DArray(int capacity);

	DArray(DArray& other);

	~DArray();

	//void Empty();

	bool Resize(int newCapacity);

	void ShrinkToFit();

	void operator=(const DArray& other);
	void operator=(const T other[]);
	void operator=(const T* other);

	T& operator[](int index);
	
private:
	void Init(int size);
	T* handleArr; // An array of pointers (handle) is used instad of normal array 
	unsigned int capacity;
	unsigned int count;
};

template<class T>
class DArray<T*>
{
public:
	DArray();

	DArray(int capacity);

	DArray(DArray& other);

	~DArray();

	void Empty(bool deleteItem = false);

	bool Resize(int newCapacity);

	void ShrinkToFit();

	void operator=(const DArray& other);
	void operator=(const T other[]);
	void operator=(const T* other);

	T& operator[](int index);

private:
	void Init(int size);
	T* handleArr; // An array of pointers (handle) is used instad of normal array 
	unsigned int capacity;
	unsigned int count;
};

#endif // !DARRAY_H
