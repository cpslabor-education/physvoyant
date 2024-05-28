// #ifndef DDELEGATE
#define DDELEGATE

#include "DDelegateAction.hpp"
#include "DArray.hpp"

/// <summary>
/// Delegate event handler
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template <class Return, class... Params>
class DDelegate
{
public:

	DDelegate() : actionArray(new DArray<DDelegateAction<Return, Params...>*>(2))
	{

	}

	~DDelegate()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			delete (*actionArray)[i];
		}
		delete actionArray;
	}


	/// <summary>
	/// Fires all function and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <returns>The reurned value of each function</returns>
	DArray<Return>* FireAll(Params... p)
	{
		DArray<Return>* results = new DArray<Return>(actionArray->Capacity());
		unsigned int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr)
			{
				(*results)[i] = (*actionArray)[i]->Fire(p...);
			}
		}
		return results;
	}

	/// <summary>
	/// Fires all function with specified ID and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <param name="ID">ID filter</param>
	/// <returns>The reurned value of each function</returns>
	DArray<Return>* FireAll(int ID, Params... p)
	{
		DArray<Return>* results = new DArray<Return>(actionArray->Capacity());
		int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr && (*actionArray)[i]->ID() == ID)
			{
				(*results)[i] = (*actionArray)[i]->Fire(p...);
			}
		}
		return results;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...))
	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<Return, Params...>(function);
		return true;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...), int id)

	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<Return, Params...>(function, id);
		return true;
	}

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubscribe(Return(*functionPointer)(Params...))
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->functionPointer == functionPointer)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubscribe(int ID)
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->ID() == ID)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsibscribes every function
	/// </summary>
	void UnsubscribeAll()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			delete (*actionArray)[i];
			(*actionArray)[i] = nullptr;
		}
	}


	DArray<DDelegateAction<Return, Params...>*>* actionArray;
};

template <class ...Params>
class DDelegate<void, Params...>
{
public:

	DDelegate() : actionArray(new DArray<DDelegateAction<void, Params...>*>(2))
	{

	}

	~DDelegate()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			delete (*actionArray)[i];
		}
		delete actionArray;
	}


	/// <summary>
	/// Fires all function and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <returns>The reurned value of each function</returns>
	void FireAll(Params... p)
	{
		unsigned int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr)
			{
				(*actionArray)[i]->Fire(p...);
			}
		}

	}

	/// <summary>
	/// Fires all function with specified ID and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <param name="ID">ID filter</param>
	/// <returns>The reurned value of each function</returns>
	void FireAll(int ID, Params... p)
	{
		unsigned int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr && (*actionArray)[i].ID() == ID)
			{
				(*actionArray)[i]->Fire(p...);
			}
		}
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(void(*function)(Params...))
	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<void, Params...>(function);
		return true;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(void(*function)(Params...), int id)

	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<void, Params...>(function, id);
		return true;
	}

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubscribe(void(*functionPointer)(Params...))
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray[i]) == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->functionPointer == functionPointer)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubscribe(int ID)
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->ID() == ID)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsibscribes every function
	/// </summary>
	void UnsubscribeAll()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				delete (*actionArray)[i];
				(*actionArray)[i] = nullptr;
			}
		}
	}


	DArray<DDelegateAction<void, Params...>*>* actionArray;
};

template <class Return, typename Class, class... Params>
class DDelegate<Return, Class, Params...>
{
public:

	DDelegate() : actionArray(new DArray<DDelegateAction<Return(Class::*)(Params...)>*>(2))
	{

	}

	~DDelegate()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			delete (*actionArray)[i];
		}
		delete actionArray;
	}


	/// <summary>
	/// Fires all function and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <returns>The reurned value of each function</returns>
	DArray<Return>* FireAll(Class* caller, Params... p)
	{
		DArray<Return>* results = new DArray<Return>(actionArray->Capacity());
		unsigned int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr)
			{
				(*results)[i] = (*actionArray)[i]->Fire(caller, p...);
			}
		}
		return results;
	}

	/// <summary>
	/// Fires all function with specified ID and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <param name="ID">ID filter</param>
	/// <returns>The reurned value of each function</returns>
	DArray<Return>* FireAll(Class* caller, int ID, Params... p)
	{
		DArray<Return>* results = new DArray<Return>(actionArray->Capacity());
		int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr && (*actionArray)[i]->ID() == ID)
			{
				(*results)[i] = (*actionArray)[i]->Fire(p...);
			}
		}
		return results;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(Class::* function)(Params...))
	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<Return(Class::*)(Params...)>(function);
		return true;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(Class::* function)(Params...), int id)

	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<Return, Params...>(function, id);
		return true;
	}

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubscribe(Return(Class::* functionPointer)(Params...))
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->functionPointer == functionPointer)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubscribe(int ID)
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->ID() == ID)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsibscribes every function
	/// </summary>
	void UnsubscribeAll()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			delete (*actionArray)[i];
			(*actionArray)[i] = nullptr;
		}
	}


	DArray<DDelegateAction<Return(Class::*)(Params...)>*>* actionArray;
};

template <typename Class, typename ...Params>
class DDelegate<void, Class, Params...>
{
public:

	DDelegate() : actionArray(new DArray<DDelegateAction<void (Class::*)(Params...)>*>(2))
	{

	}

	~DDelegate()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			delete (*actionArray)[i];
		}
		delete actionArray;
	}


	/// <summary>
	/// Fires all function and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <returns>The reurned value of each function</returns>
	void FireAll(Class* caller, Params... p)
	{
		unsigned int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr)
			{
				(*actionArray)[i]->Fire(caller, p...);
			}
		}

	}

	/// <summary>
	/// Fires all function with specified ID and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <param name="ID">ID filter</param>
	/// <returns>The reurned value of each function</returns>
	void FireAll(Class* caller, int ID, Params... p)
	{
		unsigned int length = actionArray->Capacity();
		for (unsigned int i = 0; i < length; i++)
		{
			if ((*actionArray)[i] != nullptr && (*actionArray)[i].ID() == ID)
			{
				(*actionArray)[i]->Fire(caller, p...);
			}
		}
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(void(Class::* function)(Params...))
	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<void (Class::*) (Params...)>(function);
		return true;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(void(Class::* function)(Params...), int id)

	{
		int insertionIndex = -1;
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
			else if ((*actionArray)[i]->functionPointer == function)
			{
				break;
			}
		}

		if (insertionIndex == -1)
		{
			return false;
		}

		if (insertionIndex == actionArray->Capacity() - 1)
		{
			actionArray->Resize(actionArray->Capacity() + 8);
		}

		(*actionArray)[insertionIndex] = new DDelegateAction<void, Params...>(function, id);
		return true;
	}

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubscribe(void(*functionPointer)(Params...))
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray[i]) == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->functionPointer == functionPointer)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubscribe(int ID)
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				if ((*actionArray)[i]->ID() == ID)
				{
					delete (*actionArray)[i];
					(*actionArray)[i] = nullptr;
				}
			}
		}
	}

	/// <summary>
	/// Unsibscribes every function
	/// </summary>
	void UnsubscribeAll()
	{
		for (unsigned int i = 0; i < actionArray->Capacity(); i++)
		{
			if ((*actionArray)[i] == nullptr)
			{
				continue;
			}
			else
			{
				delete (*actionArray)[i];
				(*actionArray)[i] = nullptr;
			}
		}
	}


	DArray<DDelegateAction<void(Class::*)(Params...)>*>* actionArray;
};

#endif