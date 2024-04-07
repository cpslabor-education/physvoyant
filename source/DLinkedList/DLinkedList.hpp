#ifndef DLINKED_LIST_H
#define DLINKED_LIST_H

#include "DLinkedListNode.hpp"

/// <summary>
/// Two way linked list
/// </summary>
/// <typeparam name="T">Any</typeparam>
template<class T>
class DLinkedList
{

public:

	/// <summary>
	/// The first element of the linked list
	/// </summary>
	DLinkedListNode<T>* firstElement;

	/// <summary>
	/// The last element of the list
	/// </summary>
	DLinkedListNode<T>* lastElement;

	/// <summary>
	/// The currently active element of the list
	/// </summary>
	DLinkedListNode<T>* currentElement;

	DLinkedList();
	~DLinkedList();

	/// <summary>
	/// Count of the elements in the list
	/// </summary>
	/// <returns>Count of the elements in the list</returns>
	int Count();

	/// <summary>
	/// The index of the currently active node
	/// </summary>
	/// <returns>The index of the currently active node</returns>
	int CurrentIndex();

	/// <summary>
	/// Seeks to the specified index in the list, making the nth element active
	/// </summary>
	/// <param name="newIndex">The index to seek to</param>
	void SeekToIndex(unsigned int newIndex);

	/// <summary>
	/// Steps to the next element of the list
	/// </summary>
	/// <param name="circleAround">If at the last element, step to the first element (always returns true)</param>
	/// <returns>Whether the step was possible</returns>
	bool StepForward(bool circleAround = false);

	/// <summary>
	/// Steps to the previous element of the list
	/// </summary>
	/// <param name="circleAround">If at the first element, step to the last element (always returns true)</param>
	/// <returns>Whether the step was possible</returns>
	bool StepBackward(bool circleAround = false);

	/// <summary>
	/// Pushes data before the current element
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushBefore(T data);

	/// <summary>
	/// Pushes data after the current element
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushAfter(T data);

	/// <summary>
	/// Pushes data to the beginning of the list
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushFirst(T data);

	/// <summary>
	/// Pushes data to the end of the list
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushLast(T data);

	/// <summary>
	/// Removes the element at the specified index and moves items forward
	/// </summary>
	/// <param name="index">The index of the element</param>
	/// <param name="deleteItem">Whether to delete the stored value or not</param>
	void RemoveAt(int index, bool deleteItem = false);

	/// <summary>
	/// Removes current element and moves items forward
	/// </summary>	
	/// <param name="deleteItem">Whether to delete the stored value or not</param>
	void RemoveCurrent(bool deleteItem = false);

	/// <summary>
	/// Swaps two elements
	/// </summary>
	/// <param name="leftIndex">The first element of swap</param>
	/// <param name="rightIndex">The second element of swap</param>
	void Swap(int leftIndex, int rightIndex);

	/// <summary>
	/// Empties the list
	/// </summary>
	/// <param name="deleteItem">Whether to delete the stored value or not</param>
	void Empty(bool deleteItem = false);

	/// <summary>
	/// Finds the specified element in the list
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int IndexOf(T item);

	/// <summary>
	/// Finds the specified element in the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int NthIndexOf(T item, int skip);

	/// <summary>
	/// Finds the specified element from the back of the list
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int LastIndexOf(T item);

	/// <summary>
	/// Finds the specified element from the back of the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int LastNthIndexOf(T item, int skip);

	/// <summary>
	/// Seeks to the specified element
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>If the element was found</returns>
	bool SeekToElement(T item);

	/// <summary>
	/// Seeks to the specified element, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>If the element was found</returns>
	bool SeekToNthElement(T item, int skip);

	/// <summary>
	/// Seeks to the specified element from the back of the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>If the element was found</returns>
	bool SeekToLastElement(T item);

	/// <summary>
	/// Seeks to the specified element from the back of the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>If the element was found</returns>
	bool SeekToLastNthElement(T item, int skip);



private:
	unsigned int currentIndex;
	unsigned int count;

	/// <summary>
	/// Initial push of the list
	/// </summary>
	/// <param name="data">Data to store</param>
	/// <returns>If the push was successful or not</returns>
	bool FirstPush(T data);

};
// TODO: Testing
#endif