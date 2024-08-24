#ifndef DLINKED_LIST_NODE
#define DLINKED_LIST_NODE

/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T">Any non pointer and non array type</typeparam>
template <class T>
class DLinkedListNode
{
public:

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T>* previousElement;

	/// <summary>
	/// The stored data
	/// </summary>
	T data;

	DLinkedListNode() : data(0), nextElement(nullptr), previousElement(nullptr)
	{
	}

	explicit DLinkedListNode(T data) : data(data), nextElement(nullptr), previousElement(nullptr)
	{
	}

	~DLinkedListNode()
	{
	}

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete()
	{
	}

private:

};


/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T*">Pointer type</typeparam>
template <typename T>
class DLinkedListNode<T*>
{
public:

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T*>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T*>* previousElement;

	/// <summary>
	/// The stored data
	/// </summary>
	T* data;

	DLinkedListNode() : data(nullptr), nextElement(nullptr), previousElement(nullptr)
	{
	}

	DLinkedListNode(T* data) : data(data), nextElement(nullptr), previousElement(nullptr)
	{
	}

	~DLinkedListNode()
	{
	}

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete()
	{
		delete data;
		data = nullptr;
	}

private:

};


#if false


/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T">Array type</typeparam>
/// <typeparam name="N">The length of the array</typeparam>
template<class T, int N>
class DLinkedListNode<T[N]>
{
public:
	T data[N];
	DLinkedListNode<T[N]>* nextElement;
	DLinkedListNode<T[N]>* previousElement;

	DLinkedListNode() : nextElement(nullptr), previousElement(nullptr)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] = 0;
		}
	}

	explicit DLinkedListNode(T data[N]) : nextElement(nullptr), previousElement(nullptr)
	{
		for (int i = 0; i < N; i++)
		{
			this->data[i] = data[i];
		}
	}
	~DLinkedListNode()
	{
		for (int i = 0; i < N; i++)
		{
			data[i] = 0;
		}
	}

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete();


private:

};

#endif // disabled

#endif