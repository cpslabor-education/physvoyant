#include "Colliders.hpp"
#include INCL_GAME_OBJECTS

void SphereCollider::Execute(GameObject* caller, void* params)
{
}

IComponent* SphereCollider::Clone(void* params) const
{
	return nullptr;
}

VECTOR3 SphereCollider::CollideWith(GameObject* caller, GameObject* other)
{
	VECTOR3 result (0, 0, 0);
	ICollider* otherCollider = other->GetComponentOfType<ICollider*>();
	if (dynamic_cast<SphereCollider*> (otherCollider))
	{
		SphereCollider* otherSphere = dynamic_cast<SphereCollider*> (otherCollider);
		if (otherSphere->radius + this->radius >= glm::distance(caller->transform.GetPosition(), other->transform.GetPosition()))
		{
			result = glm::normalize(caller->transform.GetPosition() - other->transform.GetPosition());
			return result;
		}
	}
	return VECTOR3();
}
