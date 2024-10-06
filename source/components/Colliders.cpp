#include "Colliders.hpp"
#include INCL_GAME_OBJECTS

VECTOR3 SphereCollider::CollideWithSphere(GameObject* caller, GameObject* other, SphereCollider* otherCollider)
{
	VECTOR3 result(0);
	if (this->radius + otherCollider->radius >= glm::distance(caller->transform.position, other->transform.position))
	{
		result = glm::normalize(other->transform.position - caller->transform.position);
	}
	return result;
}

VECTOR3 SphereCollider::CollideWithSquare(GameObject* caller, GameObject* other, SquareCollider* otherCollider)
{
	VECTOR3 closest = otherCollider->GetClosestPoint(other->transform.position, caller->transform.position);
	return CollideWith(caller, closest);
}

SphereCollider::SphereCollider() : ColliderBase(0, 0), radius(0)
{
}

SphereCollider::SphereCollider(const realStandard_t radius) : ColliderBase(0, 0), radius(radius)
{
}

SphereCollider::~SphereCollider()
{
}

void* SphereCollider::Execute(GameObject* caller, void* params)
{
	return nullptr;
}

IComponent* SphereCollider::Clone(void* params) const
{
	return new SphereCollider(*this);
}

VECTOR3 SphereCollider::CollideWith(GameObject* caller, GameObject* other)
{
	ICollider* otherCollider = other->components.GetComponent<ICollider*>();
	if (dynamic_cast<SphereCollider*> (otherCollider))
	{
		return CollideWithSphere(caller, other, dynamic_cast<SphereCollider*>(otherCollider));
	}
	else if (dynamic_cast<SquareCollider*> (otherCollider))
	{
		return CollideWithSquare(caller, other, dynamic_cast<SquareCollider*>(otherCollider));
	}
	return VECTOR3(0);
}

VECTOR3 SphereCollider::CollideWith(GameObject* caller, VECTOR3& point)
{
	if (IsInside(caller->transform.position, point))
	{
		return glm::normalize(point - caller->transform.position);
	}
	return VECTOR3(0);
}

VECTOR3 SphereCollider::CollideWith(VECTOR3& center, VECTOR3& point)
{
	if (IsInside(center, point))
	{
		return glm::normalize(point - center);
	}
	return VECTOR3(0);
}

bool SphereCollider::IsInside(VECTOR3& center, VECTOR3& point)
{
	return glm::distance(center, point) <= radius;
}

VECTOR3 SphereCollider::GetClosestPoint(VECTOR3& center, VECTOR3& point)
{
	if (glm::distance(center, point) <= this->radius)
	{
		return (point - center);
	}
	return glm::normalize(point - center) * radius;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////


VECTOR3 SquareCollider::CollideWithSphere(GameObject* caller, GameObject* other, SphereCollider* otherCollider)
{
	VECTOR3 closest = GetClosestPoint(caller->transform.position, other->transform.position);
	
	if (glm::distance(closest, caller->transform.position) <= otherCollider->GetRaduis()) // inside
	{
		return closest - caller->transform.position;
	}
	return VECTOR3(0);
}

VECTOR3 SquareCollider::CollideWithSquare(GameObject* caller, GameObject* other, SquareCollider* otherCollider)
{
	// TODO: Aplly collision logic
	return VECTOR3(0);
}

void* SquareCollider::Execute(GameObject* caller, void* params)
{
	return nullptr;
}

IComponent* SquareCollider::Clone(void* params) const
{
	return new SquareCollider(*this);
}

VECTOR3 SquareCollider::CollideWith(GameObject* caller, GameObject* other)
{
	ICollider* otherCollider = other->components.GetComponent<ICollider*>();
	if (dynamic_cast<SphereCollider*> (otherCollider))
	{
		return CollideWithSphere(caller, other, dynamic_cast<SphereCollider*>(otherCollider));
	}
	else if (dynamic_cast<SquareCollider*> (otherCollider))
	{
		return CollideWithSquare(caller, other, dynamic_cast<SquareCollider*>(otherCollider));
	}
	return VECTOR3(0);
}

VECTOR3 SquareCollider::CollideWith(GameObject* caller, VECTOR3& point)
{
	return CollideWith(caller->transform.position, point);
}

VECTOR3 SquareCollider::CollideWith(VECTOR3& center, VECTOR3& point)
{
	VECTOR3 result(0);
	QUATERNION invOrientation = glm::inverse(orientation);
	VECTOR3 localPoint = invOrientation * (point - center);
	realStandard_t halfX = sides.x / 2.0;
	realStandard_t halfY = sides.y / 2.0;
	realStandard_t halfZ = sides.z / 2.0;

	if (IsInside(center, point))
	{
		realStandard_t distX = glm::min(halfX - localPoint.x, localPoint.x + halfX);
		realStandard_t distY = glm::min(halfY - localPoint.y, localPoint.y + halfY);
		realStandard_t distZ = glm::min(halfZ - localPoint.z, localPoint.z + halfZ);
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

bool SquareCollider::IsInside(VECTOR3& center, VECTOR3& point)
{
	QUATERNION invOrientation = glm::inverse(orientation);
	VECTOR3 localPoint = invOrientation * (point - center);
	realStandard_t halfX = sides.x / 2.0;
	realStandard_t halfY = sides.y / 2.0;
	realStandard_t halfZ = sides.z / 2.0;
	return	(localPoint.x >= -halfX && localPoint.x <= halfX &&
			 localPoint.y >= -halfY && localPoint.y <= halfY &&
			 localPoint.z >= -halfZ && localPoint.z <= halfZ);
}

SquareCollider::cornerArray_t SquareCollider::GetCorners()
{
	cornerArray_t corners;
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		VECTOR3 corner(0.0);
		for (size_t j = 0; j < corner.length(); ++j)
		{
			corner[j] = ((i & (1 << j)) ? 0.5 : -0.5) * sides[j];
		}
		corner = orientation * corner;
		corners[i] = (corner);
	}
	return corners;
}

VECTOR3 SquareCollider::GetClosestPoint(VECTOR3& center, VECTOR3& point)
{
	cornerArray_t corners = GetCorners();
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		corners[i] = corners[i] + center;
	}
	VECTOR3 closest = point;
	for (size_t i = 0; i < closest.length(); i++)
	{
		realStandard_t min = DBL_MAX;
		realStandard_t max = -min;
		for (size_t j = 0; j < (size_t)1 << DIMENSIONS; j++)
		{
			max = glm::max(max, corners[j][i]);
			min = glm::min(max, corners[j][i]);
		}
		closest[i] = glm::clamp(closest[i], min, max);
	}
	return closest;
}