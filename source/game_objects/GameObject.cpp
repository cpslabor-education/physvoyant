#include "GameObject.hpp"

GameObject::GameObject() : components(ComponentContainer<IComponent*>()), transform()
{

}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.Count(); i++)
	{
		delete components[i];
	}
}

void GameObject::Update()
{
	components.UpdateAll(this);
}
