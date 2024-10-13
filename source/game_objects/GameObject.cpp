#include "GameObject.hpp"

GameObject::GameObject() : components(ComponentContainer<IComponent*>()), transform()
{

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	components.UpdateAll(this);
}
