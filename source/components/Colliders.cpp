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
		if (otherSphere->radius + this->radius >= glm::distance(caller->transform.position, other->transform.position))
		{
			result = glm::normalize(caller->transform.position - other->transform.position);
			return result;
		}
	}
	return result;
}

VECTOR3 SphereCollider::CollideWith(GameObject* caller, VECTOR3* point)
{
	VECTOR3 result(0, 0, 0);
	if (this->radius >= glm::distance(caller->transform.position, *point))
	{
		result = glm::normalize(caller->transform.position - *point);
	}
	return result;
}

void SquareCollider::Execute(GameObject* caller, void* params)
{
}

IComponent* SquareCollider::Clone(void* params) const
{
	return nullptr;
}

VECTOR3 SquareCollider::CollideWith(GameObject* caller, GameObject* other)
{
	return VECTOR3();
}

VECTOR3 SquareCollider::CollideWith(GameObject* caller, VECTOR3* point)
{
	VECTOR3 result(0, 0, 0);
	QUATERNION invOrientation = glm::inverse(orientation);
	VECTOR3 localPoint = invOrientation * (*point - caller->transform.position);
	realStandard_t halfX = sides.x / 2.0;
	realStandard_t halfY = sides.y / 2.0;
	realStandard_t halfZ = sides.z / 2.0;
	bool isInside = (localPoint.x >= -halfX && localPoint.x <= halfX &&
				   localPoint.y >= -halfY && localPoint.y <= halfY &&
				   localPoint.z >= -halfZ && localPoint.z <= halfZ);
	if (isInside)
	{
		float distX = glm::min(halfX - localPoint.x, localPoint.x + halfX);
		float distY = glm::min(halfY - localPoint.y, localPoint.y + halfY);
		float distZ = glm::min(halfZ - localPoint.z, localPoint.z + halfZ);
		if (distX > glm::max(distY, distZ))
		{
			result = VECTOR3((localPoint.x >= 0 ? 1.0 : -1.0), 0.0, 0.0);
		}
		else if (distY > distZ)
		{
			result = VECTOR3(0.0, (localPoint.y >= 0 ? 1.0 : -1.0), 0.0);
		}
		else
		{
			result = VECTOR3(0.0, 0.0, (localPoint.y >= 0 ? 1.0 : -1.0));
		}
		result = result * glm::normalize(orientation);
	}

	return result;
}
