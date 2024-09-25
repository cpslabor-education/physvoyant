#include "GameObject.hpp"

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.Count(); i++)
	{
		delete components[i];
	}
}

void GameObject::Update()
{
	for (size_t i = 0; i < components.Count(); i++)
	{
		if (components[i] != nullptr)
		{
			components[i]->Execute(this);
		}
	}
}
