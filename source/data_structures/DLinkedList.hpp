#ifndef DLINKED_LIST
#define DLINKED_LIST

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

	DLinkedList() : firstElement(nullptr), currentElement(nullptr), lastElement(nullptr), currentIndex(0), count(0)
	{

	}

	~DLinkedList()
	{

	}

	/// <summary>
	/// Count of the elements in the list
	/// </summary>
	/// <returns>Count of the elements in the list</returns>
	int Count()
	{
		return count;
	}

	/// <summary>
	/// The index of the currently active node
	/// </summary>
	/// <returns>The index of the currently active node</returns>
	int CurrentIndex()
	{
		return currentIndex;
	}

	/// <summary>
	/// Seeks to the specified index in the list, making the nth element active
	/// </summary>
	/// <param name="newIndex">The index to seek to</param>
	void SeekToIndex(unsigned int newIndex)
	{
		if (newIndex >= count)
		{
			return;
		}
		if (currentIndex == newIndex)
		{
			return;
		}
		else
		{
			if (currentIndex > newIndex)
			{
				if (currentIndex - newIndex > newIndex)
				{
					currentElement = firstElement;
					currentIndex = 0;
					for (unsigned int i = 0; i < newIndex; i++)
					{
						StepForward();
					}
				}
				else
				{
					unsigned int steps = currentIndex - newIndex;
					for (unsigned int i = 0; i < steps; i++)
					{
						StepBackward();
					}
				}
			}
			else
			{
				if (newIndex - currentIndex > count - newIndex)
				{
					currentElement = lastElement;
					currentIndex = count - 1;
					for (unsigned int i = 0; i < count - 1 - newIndex; i++)
					{
						StepBackward();
					}
				}
				else
				{
					unsigned int steps = newIndex - currentIndex;
					for (unsigned int i = 0; i < steps; i++)
					{
						StepForward();
					}
				}
			}
		}
		if (currentIndex != newIndex)
		{
			// big trouble now...
			throw std::runtime_error("Internal error: Current index does not match new index in DLinkedList.");
		}
	}

	/// <summary>
	/// Steps to the next element of the list
	/// </summary>
	/// <param name="circleAround">If at the last element, step to the first element (always returns true)</param>
	/// <returns>Whether the step was possible</returns>
	bool StepForward(bool circleAround = false)
	{
		if (circleAround)
		{
			if (currentIndex == count - 1)
			{
				SeekToIndex(0);
			}
			else
			{
				currentIndex++;
				currentElement = currentElement->nextElement;
			}
		}
		else
		{
			if (currentIndex == count - 1)
			{
				return false;
			}
			else
			{
				currentIndex++;
				currentElement = currentElement->nextElement;
			}
		}
		return true;

	}

	/// <summary>
	/// Steps to the previous element of the list
	/// </summary>
	/// <param name="circleAround">If at the first element, step to the last element (always returns true)</param>
	/// <returns>Whether the step was possible</returns>
	bool StepBackward(bool circleAround = false)
	{
		if (circleAround)
		{
			if (currentIndex == 0)
			{
				SeekToIndex(count - 1);
			}
			else
			{
				currentIndex--;
				currentElement = currentElement->previousElement;
			}
		}
		else
		{
			if (currentIndex == 0)
			{
				return false;
			}
			else
			{
				currentIndex--;
				currentElement = currentElement->previousElement;
			}
		}
		return true;

	}

	/// <summary>
	/// Pushes data before the current element
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushBefore(T data)
	{
		if (count == 0)
		{
			return FirstPush(data);
		}
		else
		{
			if (CurrentIndex() == 0)
			{
				return PushFirst(data);
			}
			else
			{
				DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
				if (d != nullptr)
				{
					currentElement->previousElement->nextElement = d;
					d->previousElement = currentElement->previousElement;

					d->nextElement = currentElement;
					currentElement->previousElement = d;
					currentIndex++;
					count++;
					return true;
				}
				else return false;
			}


		}
	}

	/// <summary>
	/// Pushes data after the current element
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushAfter(T data)
	{
		if (count == 0)
		{
			return FirstPush(data);
		}
		else
		{
			if (currentIndex == count - 1)
			{
				return PushLast(data);
			}
			else
			{
				DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
				if (d != nullptr)
				{
					currentElement->nextElement->previousElement = d;
					d->nextElement = currentElement->nextElement;

					d->previousElement = currentElement;
					currentElement->nextElement = d;

					count++;
					return true;
				}
				else return false;
			}
		}
	}

	/// <summary>
	/// Pushes data to the beginning of the list
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushFirst(T data)
	{
		if (count == 0)
		{
			return FirstPush(data);
		}
		else
		{
			DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
			if (d != nullptr)
			{
				firstElement->previousElement = d;
				d->nextElement = firstElement;

				firstElement = d;
				count++;
				currentIndex++;
				return true;
			}
			else return false;
		}
	}

	/// <summary>
	/// Pushes data to the end of the list
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushLast(T data)
	{
		if (count == 0)
		{
			return FirstPush(data);
		}
		else
		{
			DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
			if (d != nullptr)
			{
				lastElement->nextElement = d;
				d->previousElement = lastElement;
				lastElement = d;
				count++;
				return true;
			}
			else return false;
		}
	}

	/// <summary>
	/// Removes the element at the specified index and moves items forward
	/// </summary>
	/// <param name="index">The index of the element</param>
	/// <param name="deleteItem">Whether to delete the stored value or not</param>
	void RemoveAt(int index, bool deleteItem = false)
	{
		int revert = currentIndex;
		SeekToIndex(index);
		RemoveCurrent(deleteItem);
		SeekToIndex(revert);
		return;

	#if false
		if (index == 0) // first element
		{
			currentElement = currentElement->nextElement;
			delete (firstElement);
			firstElement = currentElement;
			currentElement->previousElement = nullptr;
		}
		else if (index == count - 1) // last element
		{
			currentElement = currentElement->previousElement;
			delete lastElement;
			lastElement = currentElement;
			currentElement->nextElement = nullptr;
			currentIndex--;
		}
		else // Any in between
		{
			currentElement = currentElement->previousElement;
			currentElement->nextElement = currentElement->nextElement->nextElement;
			delete (currentElement->nextElement->previousElement);
			currentElement->nextElement->previousElement = currentElement;
		}
		count--;
		SeekToIndex(revert);
	#endif // OBSOLETE
	}

	/// <summary>
	/// Removes current element and moves items forward
	/// </summary>	
	/// <param name="deleteItem">Whether to delete the stored value or not</param>
	void RemoveCurrent(bool deleteItem = false)
	{
		if (count == 1) // One element
		{
			Empty(deleteItem);
		}
		else if (currentIndex == 0) // First element
		{
			currentElement = currentElement->nextElement;
			if (deleteItem)
			{
				firstElement->Delete();
			}
			delete firstElement;
			firstElement = currentElement;
			currentElement->previousElement = nullptr;
			count--;
		}
		else if (currentIndex == count - 1) // Last element
		{
			currentElement = currentElement->previousElement;
			if (deleteItem)
			{
				lastElement->Delete();
			}
			delete lastElement;
			lastElement = currentElement;
			currentElement->nextElement = nullptr;
			count--;
			currentIndex--;
		}
		else // Anywhere in between
		{
			DLinkedListNode<T>* tmp = currentElement;
			currentElement->previousElement->nextElement = currentElement->nextElement;
			currentElement->nextElement->previousElement = currentElement->previousElement;
			currentElement = currentElement->nextElement;
			if (deleteItem)
			{
				tmp->Delete();
			}
			delete tmp;
			count--;
		}
	}

	/// <summary>
	/// Swaps two elements
	/// </summary>
	/// <param name="leftIndex">The first element of swap</param>
	/// <param name="rightIndex">The second element of swap</param>
	void Swap(int leftIndex, int rightIndex)
	{
		int revert = currentIndex;
		SeekToIndex(leftIndex);
		DLinkedListNode<T>* left = currentElement;
		SeekToIndex(rightIndex);
		DLinkedListNode<T>* right = currentElement;
		DLinkedListNode<T>* tmp;

		// Rewire the list
		left->previousElement->nextElement = right;
		left->nextElement->previousElement = right;
		right->previousElement->nextElement = left;
		right->nextElement->previousElement = left;

		// Rewire the elements
		tmp = right->previousElement;
		right->previousElement = left->previousElement;
		left->previousElement = tmp;

		tmp = right->nextElement;
		right->nextElement = left->nextElement;
		left->nextElement = tmp;

		SeekToIndex(revert);
	}

	/// <summary>
	/// Empties the list
	/// </summary>
	/// <param name="deleteItem">Whether to delete the stored value or not</param>
	void Empty(bool deleteItem = false)
	{
		DLinkedListNode<T>* tmp;
		while (firstElement != nullptr)
		{
			tmp = firstElement->nextElement;
			if (deleteItem)
			{
				firstElement->Delete();
			}
			delete(firstElement);
			firstElement = tmp;
		}
		lastElement = nullptr;
		currentElement = nullptr;
		currentIndex = 0;
		count = 0;
	}

	/// <summary>
	/// Finds the specified element in the list
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int IndexOf(T item)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				int ret = currentIndex;
				SeekToIndex(revert);
				return ret;
			}
			StepForward(true);
			++counter;
		} while (counter < this->count);
		if (revert != currentIndex)
		{
			int asd = 3;
			int asd2 = asd + 3;
		}
		return -1;
	}

	/// <summary>
	/// Finds the specified element in the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int NthIndexOf(T item, int skip)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				if (skip <= 0)
				{
					int ret = currentIndex;
					SeekToIndex(revert);
					return ret;
				}
				--skip;
			}
			StepForward(true);
			++counter;
		} while (counter < this->count);
		return -1;
	}

	/// <summary>
	/// Finds the specified element from the back of the list
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int LastIndexOf(T item)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				int ret = currentIndex;
				SeekToIndex(revert);
				return ret;
			}
			StepBackward(true);
			++counter;
		} while (counter < this->count);

		return -1;
	}

	/// <summary>
	/// Finds the specified element from the back of the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>The index of the searched value. -1 if not found</returns>
	int LastNthIndexOf(T item, int skip)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				if (skip <= 0)
				{
					int ret = currentIndex;
					SeekToIndex(revert);
					return ret;
				}
				--skip;
			}
			StepBackward(true);
			++counter;
		} while (counter < this->count);

		SeekToIndex(revert);
		return -1;
	}

	/// <summary>
	/// Seeks to the specified element
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>If the element was found</returns>
	bool SeekToElement(T item)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				return true;
			}
			StepForward(true);
			++counter;
		} while (counter < this->count);
		SeekToIndex(revert);
		return false;
	}

	/// <summary>
	/// Seeks to the specified element, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>If the element was found</returns>
	bool SeekToNthElement(T item, int skip)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				if (skip <= 0)
				{
					return true;
				}
				--skip;
			}
			StepForward(true);
			++counter;
		} while (counter < this->count);
		SeekToIndex(revert);
		return false;
	}

	/// <summary>
	/// Seeks to the specified element from the back of the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <returns>If the element was found</returns>
	bool SeekToLastElement(T item)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				return true;
			}
			StepBackward(true);
			++counter;
		} while (counter < this->count);
		SeekToIndex(revert);
		return false;
	}

	/// <summary>
	/// Seeks to the specified element from the back of the list, skipping N previous matches
	/// </summary>
	/// <param name="item">Value to look for</param>
	/// <param name="skip">How many matches should be skipped</param>
	/// <returns>If the element was found</returns>
	bool SeekToLastNthElement(T item, int skip)
	{
		unsigned int revert = currentIndex;
		int counter = 0;
		do
		{
			if (currentElement->data == item)
			{
				if (skip <= 0)
				{
					return true;
				}
				--skip;
			}
			StepBackward(true);
			++counter;
		} while (counter < this->count);
		SeekToIndex(revert);
		return false;
	}


private:
	unsigned int currentIndex;
	unsigned int count;

	/// <summary>
	/// Initial push of the list
	/// </summary>
	/// <param name="data">Data to store</param>
	/// <returns>If the push was successful or not</returns>
	bool FirstPush(T data)
	{
		DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
		if (d != nullptr)
		{
			firstElement = d;
			lastElement = d;
			currentElement = d;
			currentIndex = 0;
			count = 1;

			return true;
		}
		else return false;
	}

};
// TODO: Testing

////////////////////////////////////////////////////////////////////////////
#if false


template<class T>
DLinkedList<T>::DLinkedList()
{
	firstElement = nullptr;
	currentElement = nullptr;
	lastElement = nullptr;
	currentIndex = 0;
	count = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList()
{

}

template<class T>
int DLinkedList<T>::Count()
{
	return count;
}

template<class T>
int DLinkedList<T>::CurrentIndex()
{
	return currentIndex;
}

template<class T>
void DLinkedList<T>::SeekToIndex(unsigned int newIndex)
{
	if (newIndex >= count)
	{
		return;
	}
	if (currentIndex == newIndex)
	{
		return;
	}
	else
	{
		if (currentIndex > newIndex)
		{
			if (currentIndex - newIndex > newIndex)
			{
				currentElement = firstElement;
				currentIndex = 0;
				for (unsigned int i = 0; i < newIndex; i++)
				{
					StepForward();
				}
			}
			else
			{
				unsigned int steps = currentIndex - newIndex;
				for (unsigned int i = 0; i < steps; i++)
				{
					StepBackward();
				}
			}
		}
		else
		{
			if (newIndex - currentIndex > count - newIndex)
			{
				currentElement = lastElement;
				currentIndex = count - 1;
				for (unsigned int i = 0; i < count - 1 - newIndex; i++)
				{
					StepBackward();
				}
			}
			else
			{
				unsigned int steps = newIndex - currentIndex;
				for (unsigned int i = 0; i < steps; i++)
				{
					StepForward();
				}
			}
		}
	}
	if (currentIndex != newIndex)
	{
		// big trouble now...
		throw std::runtime_error("Internal error: Current index does not match new index in DLinkedList.");
	}
}

template<class T>
bool DLinkedList<T>::StepForward(bool circleAround)
{
	if (circleAround)
	{
		if (currentIndex == count - 1)
		{
			SeekToIndex(0);
		}
		else
		{
			currentIndex++;
			currentElement = currentElement->nextElement;
		}
	}
	else
	{
		if (currentIndex == count - 1)
		{
			return false;
		}
		else
		{
			currentIndex++;
			currentElement = currentElement->nextElement;
		}
	}
	return true;

}

template<class T>
bool DLinkedList<T>::StepBackward(bool circleAround)
{
	if (circleAround)
	{
		if (currentIndex == 0)
		{
			SeekToIndex(count - 1);
		}
		else
		{
			currentIndex--;
			currentElement = currentElement->previousElement;
		}
	}
	else
	{
		if (currentIndex == 0)
		{
			return false;
		}
		else
		{
			currentIndex--;
			currentElement = currentElement->previousElement;
		}
	}
	return true;

}

template<class T>
bool DLinkedList<T>::PushBefore(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		if (CurrentIndex() == 0)
		{
			return PushFirst(data);
		}
		else
		{
			DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
			if (d != nullptr)
			{
				currentElement->previousElement->nextElement = d;
				d->previousElement = currentElement->previousElement;

				d->nextElement = currentElement;
				currentElement->previousElement = d;
				currentIndex++;
				count++;
				return true;
			}
			else return false;
		}


	}
}

template<class T>
bool DLinkedList<T>::PushAfter(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		if (currentIndex == count - 1)
		{
			return PushLast(data);
		}
		else
		{
			DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
			if (d != nullptr)
			{
				currentElement->nextElement->previousElement = d;
				d->nextElement = currentElement->nextElement;

				d->previousElement = currentElement;
				currentElement->nextElement = d;

				count++;
				return true;
			}
			else return false;
		}
	}
}

template<class T>
bool DLinkedList<T>::PushFirst(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
		if (d != nullptr)
		{
			firstElement->previousElement = d;
			d->nextElement = firstElement;

			firstElement = d;
			count++;
			currentIndex++;
			return true;
		}
		else return false;
	}
}

template<class T>
bool DLinkedList<T>::PushLast(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
		if (d != nullptr)
		{
			lastElement->nextElement = d;
			d->previousElement = lastElement;
			lastElement = d;
			count++;
			return true;
		}
		else return false;
	}
}

template<class T>
void DLinkedList<T>::RemoveAt(int index, bool deleteItem)
{
	int revert = currentIndex;
	SeekToIndex(index);
	RemoveCurrent(deleteItem);
	SeekToIndex(revert);
	return;

#if false
	if (index == 0) // first element
	{
		currentElement = currentElement->nextElement;
		delete (firstElement);
		firstElement = currentElement;
		currentElement->previousElement = nullptr;
	}
	else if (index == count - 1) // last element
	{
		currentElement = currentElement->previousElement;
		delete lastElement;
		lastElement = currentElement;
		currentElement->nextElement = nullptr;
		currentIndex--;
	}
	else // Any in between
	{
		currentElement = currentElement->previousElement;
		currentElement->nextElement = currentElement->nextElement->nextElement;
		delete (currentElement->nextElement->previousElement);
		currentElement->nextElement->previousElement = currentElement;
	}
	count--;
	SeekToIndex(revert);
#endif // OBSOLETE
}

template<class T>
void DLinkedList<T>::RemoveCurrent(bool deleteItem)
{
	if (count == 1) // One element
	{
		Empty(deleteItem);
	}
	else if (currentIndex == 0) // First element
	{
		currentElement = currentElement->nextElement;
		if (deleteItem)
		{
			firstElement->Delete();
		}
		delete firstElement;
		firstElement = currentElement;
		currentElement->previousElement = nullptr;
		count--;
	}
	else if (currentIndex == count - 1) // Last element
	{
		currentElement = currentElement->previousElement;
		if (deleteItem)
		{
			lastElement->Delete();
		}
		delete lastElement;
		lastElement = currentElement;
		currentElement->nextElement = nullptr;
		count--;
		currentIndex--;
	}
	else // Anywhere in between
	{
		DLinkedListNode<T>* tmp = currentElement;
		currentElement->previousElement->nextElement = currentElement->nextElement;
		currentElement->nextElement->previousElement = currentElement->previousElement;
		currentElement = currentElement->nextElement;
		if (deleteItem)
		{
			tmp->Delete();
		}
		delete tmp;
		count--;
	}
}

template<class T>
void DLinkedList<T>::Swap(int leftIndex, int rightIndex)
{
	int revert = currentIndex;
	SeekToIndex(leftIndex);
	DLinkedListNode<T>* left = currentElement;
	SeekToIndex(rightIndex);
	DLinkedListNode<T>* right = currentElement;
	DLinkedListNode<T>* tmp;

	// Rewire the list
	left->previousElement->nextElement = right;
	left->nextElement->previousElement = right;
	right->previousElement->nextElement = left;
	right->nextElement->previousElement = left;

	// Rewire the elements
	tmp = right->previousElement;
	right->previousElement = left->previousElement;
	left->previousElement = tmp;

	tmp = right->nextElement;
	right->nextElement = left->nextElement;
	left->nextElement = tmp;

	SeekToIndex(revert);
}

template<class T>
void DLinkedList<T>::Empty(bool deleteItem)
{
	DLinkedListNode<T>* tmp;
	while (firstElement != nullptr)
	{
		tmp = firstElement->nextElement;
		if (deleteItem)
		{
			firstElement->Delete();
		}
		delete(firstElement);
		firstElement = tmp;
	}
	lastElement = nullptr;
	currentElement = nullptr;
	currentIndex = 0;
	count = 0;
}

template<class T>
int DLinkedList<T>::IndexOf(T item)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			int ret = currentIndex;
			SeekToIndex(revert);
			return ret;
		}
		StepForward(true);
		++counter;
	} while (counter < this->count);
	if (revert != currentIndex)
	{
		int asd = 3;
		int asd2 = asd + 3;
	}
	return -1;
}

template<class T>
int DLinkedList<T>::NthIndexOf(T item, int skip)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			if (skip <= 0)
			{
				int ret = currentIndex;
				SeekToIndex(revert);
				return ret;
			}
			--skip;
		}
		StepForward(true);
		++counter;
	} while (counter < this->count);
	return -1;
}

template<class T>
int DLinkedList<T>::LastIndexOf(T item)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			int ret = currentIndex;
			SeekToIndex(revert);
			return ret;
		}
		StepBackward(true);
		++counter;
	} while (counter < this->count);

	return -1;
}

template<class T>
int DLinkedList<T>::LastNthIndexOf(T item, int skip)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			if (skip <= 0)
			{
				int ret = currentIndex;
				SeekToIndex(revert);
				return ret;
			}
			--skip;
		}
		StepBackward(true);
		++counter;
	} while (counter < this->count);

	SeekToIndex(revert);
	return -1;
}

template<class T>
bool DLinkedList<T>::SeekToElement(T item)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			return true;
		}
		StepForward(true);
		++counter;
	} while (counter < this->count);
	SeekToIndex(revert);
	return false;
}

template<class T>
bool DLinkedList<T>::SeekToNthElement(T item, int skip)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			if (skip <= 0)
			{
				return true;
			}
			--skip;
		}
		StepForward(true);
		++counter;
	} while (counter < this->count);
	SeekToIndex(revert);
	return false;
}

template<class T>
bool DLinkedList<T>::SeekToLastElement(T item)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			return true;
		}
		StepBackward(true);
		++counter;
	} while (counter < this->count);
	SeekToIndex(revert);
	return false;
}

template<class T>
bool DLinkedList<T>::SeekToLastNthElement(T item, int skip)
{
	unsigned int revert = currentIndex;
	int counter = 0;
	do
	{
		if (currentElement->data == item)
		{
			if (skip <= 0)
			{
				return true;
			}
			--skip;
		}
		StepBackward(true);
		++counter;
	} while (counter < this->count);
	SeekToIndex(revert);
	return false;
}

template<class T>
bool DLinkedList<T>::FirstPush(T data)
{
	DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
	if (d != nullptr)
	{
		firstElement = d;
		lastElement = d;
		currentElement = d;
		currentIndex = 0;
		count = 1;

		return true;
	}
	else return false;
}
#endif // false



#endif