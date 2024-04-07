#ifndef DLINKED_LIST_NODE
#define DLINKED_LIST_NODE

#include "DLinkedListNode.hpp"

template <class T>
DLinkedListNode<T>::DLinkedListNode() : data(0), nextElement(nullptr), previousElement(nullptr)
{

}

template <class T>
DLinkedListNode<T>::DLinkedListNode(T data)
{
	this->data = data;
	nextElement = nullptr;
	previousElement = nullptr;
}

template <class T>
DLinkedListNode<T>::~DLinkedListNode()
{

}


template <class T>
void DLinkedListNode<T>::Delete()
{
	// data = NULL;
}




template <class T>
void DLinkedListNode<T*>::Delete()
{
	delete data;
	data = nullptr;
}

template <class T>
DLinkedListNode<T*>::DLinkedListNode() : data(0), nextElement(nullptr), previousElement(nullptr)
{

}


template <class T>
DLinkedListNode<T*>::DLinkedListNode(T* data)
{
	this->data = data;
	nextElement = nullptr;
	previousElement = nullptr;
}

template <class T>
DLinkedListNode<T*>::~DLinkedListNode()
{

}


template<class T, int N>
void DLinkedListNode<T[N]>::Delete()
{
	for (int i = 0; i < N; i++)
	{
		data[i] = 0;
	}
}
template<class T, int N>
DLinkedListNode<T[N]>::DLinkedListNode() : nextElement(nullptr), previousElement(nullptr)
{
	for (int i = 0; i < N; i++)
	{
		data[i] = 0;
	}
}


template<class T, int N>
DLinkedListNode<T[N]>::DLinkedListNode(T data[N]) : nextElement(nullptr), previousElement(nullptr)
{
	for (int i = 0; i < N; i++)
	{
		this->data[i] = data[i];

	}
}

template<class T, int N>
DLinkedListNode<T[N]>::~DLinkedListNode()
{

}


#endif