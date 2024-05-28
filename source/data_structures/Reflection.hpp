#ifndef REFLECTION
#define REFLECTION

#include "../defines.hpp"
#include "DArray.hpp"
#include "ReflectionObject.hpp"
#include <iostream>

#define NAMEOF(variable) #variable
#define ADDBINDING(variable) variable, NAMEOF(variable)


template <class T>
class Reflection
{
public:
	Reflection() : reflectionArray(new DArray<ReflectionObject<T>*>(ARRAY_DEFAULT_SIZE))
	{
		Init();
	}

	~Reflection()
	{
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			delete (*reflectionArray)[i];
		}
		delete reflectionArray;
	}

	Reflection(Reflection<T>& other);

	void operator=(const Reflection<T>& other);

	T& operator[](char* name)
	{
		return GetReference((const char*)name);
	}
	T& operator[](const char* name)
	{
		return GetReference(name);
	}

	void AddBinding(T& variable, char* name)
	{
		AddBinding(variable, (const char*)name);
	}

	void AddBinding(T& variable, const char* name)
	{
		if (!IsBinded(name))
		{
			AddToArray(new ReflectionObject<T>(variable, name));
		}
	}

	void RemoveBinding(const char* name)
	{
		RemoveFromArray(name);
	}

	bool IsBinded(const char* name)
	{
		for (int i = 0; i < reflectionArray->Capacity() && (*reflectionArray)[i] != nullptr; i++)
		{
			if ((*reflectionArray)[i] != nullptr && (*reflectionArray)[i]->GetName() == name)
			{
				return true;
			}
		}
		return false;
	}

private:
	T& GetReference(const char* name)
	{
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] != nullptr && !strcmp((*reflectionArray)[i]->GetName(), name))
			{
				return (*reflectionArray)[i]->GetReference();
			}
		}

		throw std::out_of_range("Variable is not binded to the reflection: " + *name);
	}

	void AddToArray(ReflectionObject<T>* obj)
	{
		int insertionIndex = -1;
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
		}
		if (insertionIndex == reflectionArray->Capacity() - 1)
		{
			reflectionArray->Resize(reflectionArray->Capacity() + ARRAY_DEFAULT_SIZE);
		}
		if (insertionIndex == -1)
		{
			insertionIndex = reflectionArray->Capacity();
			reflectionArray->Resize(insertionIndex * 2);
		}
		(*reflectionArray)[insertionIndex] = obj;
	}

	void Init()
	{

	}

	void RemoveFromArray(char* name)
	{
		RemoveFromArray((const char*)name);
	}
	void RemoveFromArray(const char* name)
	{
		int removeIndex = -1;
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] != nullptr && (*reflectionArray)[i]->GetName() == name)
			{
				removeIndex = i;
				break;
			}
		}
		if (removeIndex == -1)
		{
			return;
		}
		else
		{
			delete (*reflectionArray)[removeIndex];
		}
	}

	DArray<ReflectionObject<T>*>* reflectionArray;
};

template <typename Return, typename... Params>
class Reflection<Return(*)(Params...)>
{
public:
	Reflection() : reflectionArray(new DArray<ReflectionObject<Return(*)(Params...)>*>(ARRAY_DEFAULT_SIZE))
	{
		Init();
	}

	~Reflection()
	{
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			delete (*reflectionArray)[i];
		}
		delete reflectionArray;
	}

	Reflection(Reflection<Return(*)(Params...)>& other);

	void operator=(const Reflection<Return(*)(Params...)>& other);

	Return(*operator[](char* name))(Params...)
	{
		return GetReference((const char*)name);
	}
	Return(*operator[](const char* name))(Params...)
	{
		return GetReference(name);
	}

	void AddBinding(Return(*variable)(Params...), char* name)
	{
		AddBinding(variable, (const char*)name);
	}

	void AddBinding(Return(*variable)(Params...), const char* name)
	{
		if (!IsBinded(name))
		{
			AddToArray(new ReflectionObject<Return(*)(Params...)>(variable, name));
		}
	}

	void RemoveBinding(const char* name)
	{
		RemoveFromArray(name);
	}

	bool IsBinded(const char* name)
	{
		for (int i = 0; i < reflectionArray->Capacity() && (*reflectionArray)[i] != nullptr; i++)
		{
			if ((*reflectionArray)[i] != nullptr && (*reflectionArray)[i]->GetName() == name)
			{
				return true;
			}
		}
		return false;
	}

private:
	Return(*GetReference(const char* name))(Params...)
	{
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] != nullptr && !strcmp((*reflectionArray)[i]->GetName(), name))
			{
				return (*reflectionArray)[i]->GetReference();
			}
		}

		throw std::out_of_range("Variable is not binded to the reflection: " + *name);
	}

	void AddToArray(ReflectionObject<Return(*)(Params...)>* obj)
	{
		int insertionIndex = -1;
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
		}
		if (insertionIndex == reflectionArray->Capacity() - 1)
		{
			reflectionArray->Resize(reflectionArray->Capacity() + ARRAY_DEFAULT_SIZE);
		}
		if (insertionIndex == -1)
		{
			insertionIndex = reflectionArray->Capacity();
			reflectionArray->Resize(insertionIndex * 2);
		}
		(*reflectionArray)[insertionIndex] = obj;
	}

	void Init()
	{

	}

	void RemoveFromArray(char* name)
	{
		RemoveFromArray((const char*)name);
	}
	void RemoveFromArray(const char* name)
	{
		int removeIndex = -1;
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] != nullptr && (*reflectionArray)[i]->GetName() == name)
			{
				removeIndex = i;
				break;
			}
		}
		if (removeIndex == -1)
		{
			return;
		}
		else
		{
			delete (*reflectionArray)[removeIndex];
		}
	}

	DArray<ReflectionObject<Return(*)(Params...)>*>* reflectionArray;
};

template <typename Return, typename Class, typename... Params>
class Reflection<Return(Class::*)(Params...)>
{
public:
	Reflection(Reflection& other) = delete;

	void operator=(const Reflection& other) = delete;

	~Reflection();

	static Reflection* GetInstance()
	{
		if (instancePtr == nullptr)
		{
			instancePtr = new Reflection<Return(Class::*)(Params...)>();
		}
		return instancePtr;
	}

	Return(Class::* operator[](char* name))(Params...)
	{
		return GetReference((const char*)name);
	}
	Return(Class::* operator[](const char* name))(Params...)
	{
		return GetReference(name);
	}

	void AddBinding(Return(Class::* variable)(Params...), char* name)
	{
		AddBinding(variable, (const char*)name);
	}

	void AddBinding(Return(Class::* variable)(Params...), const char* name)
	{
		if (!IsBinded(name))
		{
			AddToArray(new ReflectionObject<Return(Class::*)(Params...)>(variable, name));
		}
	}

	bool IsBinded(const char* name)
	{
		for (int i = 0; i < reflectionArray->Capacity() && (*reflectionArray)[i] != nullptr; i++)
		{
			if ((*reflectionArray)[i] != nullptr && (*reflectionArray)[i]->GetName() == name)
			{
				return true;
			}
		}
		return false;
	}

private:
	Reflection() : reflectionArray(new DArray<ReflectionObject<Return(Class::*)(Params...)>*>(ARRAY_DEFAULT_SIZE))
	{

	}

	Return(Class::* GetReference(const char* name))(Params...)
	{
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] != nullptr && !strcmp((*reflectionArray)[i]->GetName(), name))
			{
				return (*reflectionArray)[i]->GetReference();
			}
		}

		throw std::out_of_range("Variable is not binded to the reflection: " + *name);
	}

	void AddToArray(ReflectionObject<Return(Class::*)(Params...)>* obj)
	{
		int insertionIndex = -1;
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] == nullptr)
			{
				insertionIndex = i;
				break;
			}
		}
		if (insertionIndex == reflectionArray->Capacity() - 1)
		{
			reflectionArray->Resize(reflectionArray->Capacity() + ARRAY_DEFAULT_SIZE);
		}
		if (insertionIndex == -1)
		{
			insertionIndex = reflectionArray->Capacity();
			reflectionArray->Resize(insertionIndex * 2);
		}
		(*reflectionArray)[insertionIndex] = obj;
	}

	void Init()
	{

	}

	void RemoveFromArray(char* name)
	{
		RemoveFromArray((const char*)name);
	}
	void RemoveFromArray(const char* name)
	{
		int removeIndex = -1;
		for (int i = 0; i < reflectionArray->Capacity(); i++)
		{
			if ((*reflectionArray)[i] != nullptr && (*reflectionArray)[i]->GetName() == name)
			{
				removeIndex = i;
				break;
			}
		}
		if (removeIndex == -1)
		{
			return;
		}
		else
		{
			delete (*reflectionArray)[removeIndex];
		}
	}
	static Reflection<Return(Class::*)(Params...)>* instancePtr;
	DArray<ReflectionObject<Return(Class::*)(Params...)>*>* reflectionArray;

};

template <typename Return, typename Class, typename... Params>
Reflection<Return(Class::*)(Params...)>* Reflection<Return(Class::*)(Params...)>::instancePtr = nullptr;

#endif // !REFLECTION_H

