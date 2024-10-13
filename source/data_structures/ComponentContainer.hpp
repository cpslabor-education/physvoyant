#ifndef COMPONENT_CONTAINER
#define COMPONENT_CONTAINER

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_DATA_STRUCTURES
#include <vector>

template
<typename T>
class ComponentContainer
{
	std::vector<T> components;
public:
	ComponentContainer() : components()
	{

	}
	~ComponentContainer()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			delete components[i];
		}
	}

	T operator[](size_t index)
	{
		return components[index];
	}

	void AddComponent(T component, void* params = nullptr)
	{
		components.push_back((component->Clone(params)));
	}

	T GetComponent(componentID_t ID)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i]->GetID() == ID)
			{
				return components[i];
			}
		}
		return nullptr;
	}
	std::vector<T> GetComponents(componentID_t ID);
	
	template
	<typename Type>
	Type GetComponent()
	{
		Type result = nullptr;
		for (size_t i = 0; i < components.size(); i++)
		{
			result = dynamic_cast<Type>(components[i]);
			if (result != nullptr)
			{
				return result;
			}
		}
		return result;
	}

	template
	<typename Type>
	std::vector<Type> GetComponents()
	{
		std::vector<Type> result;
		for (size_t i = 0; i < components.size(); i++)
		{
			Type tmp = dynamic_cast<Type>(components[i]);
			if (tmp != nullptr)
			{
				result.push_back(tmp);
			}
		}
		return result;
	}

	void RemoveComponent(componentID_t ID);
	void RemoveComponent(T component);

	template <typename Parent>
	void UpdateAll(Parent* parent, void* params = nullptr)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Execute(parent, params);
		}
	}

	size_t Count()
	{
		return components.size();
	}
};


#endif
