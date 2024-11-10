#include "GameObject.hpp"

GameObject::GameObject() : components(ComponentContainer<IComponent*>()), transform()
{

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (transform.positionLock != nullptr)
	{
		transform.position.vector = transform.positionLock->vector + transform.positionOffset.vector;
		transform.position.SetRotation(transform.positionLock->GetRotation() + transform.positionOffset.GetRotation());
	}
	components.UpdateAll(this);
}
