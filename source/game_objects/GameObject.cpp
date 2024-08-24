#include "GameObject.hpp"

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
}

void GameObject::Update()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i] != nullptr)
		{
			components[i]->Execute(this);
		}
	}
}

void GameObject::AddComponent(IComponent* component)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i] == nullptr)
		{
			components[i] = component->Clone();
			return;
		}
	}
	components.push_back(component->Clone());
}

void GameObject::AddComponent(IComponent&& component)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i] == nullptr)
		{
			components[i] = component.Clone();
			return;
		}
	}
	components.push_back(component.Clone());
}

inline void GameObject::RemoveComponents(unsigned long long ID)
{

}
