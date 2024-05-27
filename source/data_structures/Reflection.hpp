#ifndef REFLECTION
#define REFLECTION

#include "DArray.hpp"
#include "ReflectionObject.hpp"
#include <iostream>

#define NAMEOF(variable) #variable
#define ADDBINDING(variable) variable, NAMEOF(variable)

template <class T>
class Reflection
{
public:
	Reflection() : reflectionArray(new DArray<ReflectionObject<T>*>(8))
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
			reflectionArray->Resize(reflectionArray->Capacity() + 8);
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

//template <typename Return, typename Class, typename... Params>
//class Reflection<Return(Class::*)(Params...)>
//{
//public:
//	Reflection(Reflection& other) = delete;
//
//	void operator=(const Reflection& other) = delete;
//
//	~Reflection();
//
//	static Reflection* GetInstance()
//	{
//		if (instancePtr == nullptr)
//		{
//			instancePtr = new Reflection();
//		}
//		return instancePtr;
//	}
//
//private:
//	Reflection();
//	void Init();
//	static Reflection* instancePtr;
//
//};

#endif // !REFLECTION_H

