#include "Colliders.hpp"
#include INCL_GAME_OBJECTS

VECTOR3 SphereCollider::CollideWithSphere(PosRot& center, PosRot& otherCenter, SphereCollider* otherCollider)
{
	VECTOR3 result(0);
	if (glm::distance(center.vector, otherCenter.vector) <= otherCollider->radius + this->radius)
	{
		result = glm::normalize(otherCenter.vector - center.vector);
	}
	return result;
}

VECTOR3 SphereCollider::CollideWithSquare(PosRot& center, PosRot& otherCenter, SquareCollider* otherCollider)
{
	VECTOR3 closest = otherCollider->GetClosestPoint(otherCenter, center.vector);
	return CollideWith(center, closest);
}

void* SphereCollider::Execute(GameObject* caller, void* params)
{
	return nullptr;
}

IComponent* SphereCollider::Clone(void* params) const
{
	return new SphereCollider(*this);
}

VECTOR3 SphereCollider::CollideWith(GameObject& caller, GameObject& other)
{
	ICollider* otherCollider = other.components.GetComponent<ICollider*>();
	if (dynamic_cast<SphereCollider*> (otherCollider))
	{
		return CollideWithSphere(caller.transform.position, other.transform.position, dynamic_cast<SphereCollider*>(otherCollider));
	}
	else if (dynamic_cast<SquareCollider*> (otherCollider))
	{
		return CollideWithSquare(caller.transform.position, other.transform.position, dynamic_cast<SquareCollider*>(otherCollider));
	}
	return VECTOR3(0);
}

VECTOR3 SphereCollider::CollideWith(PosRot& center, VECTOR3& point)
{
	VECTOR3 result(0);
	if (glm::distance(center.vector, point) <= this->radius)
	{
		result = glm::normalize(point - center.vector);
	}
	return result;
}

VECTOR3 SphereCollider::GetClosestPoint(PosRot& center, VECTOR3& point)
{
	return glm::normalize(point - center.vector) * glm::min(this->radius, glm::distance(point, center.vector));
}

//////////////////////////////////////////////////////////////////

VECTOR3 SquareCollider::CollideWithSphere(PosRot& center, PosRot& otherCenter, SphereCollider* otherCollider)
{
	VECTOR3 closest = GetClosestPoint(center, otherCenter.vector);
	return -(otherCollider->CollideWith(otherCenter, closest));
}

VECTOR3 SquareCollider::CollideWithSquare(PosRot& center, PosRot& otherCenter, SquareCollider* otherCollider)
{
	cornerArray_t corners = GetCorners(&center);
	VECTOR3 result(0);
	VECTOR3 nullVector(0);
	for (size_t i = 0; i < corners.size(); i++)
	{
		result = otherCollider->CollideWith(otherCenter, corners[i]);
		if (result != nullVector) // inside
		{
			return -result;
		}
	}
	corners = otherCollider->GetCorners(&otherCenter);
	for (size_t i = 0; i < corners.size(); i++)
	{
		result = CollideWith(center, corners[i]);
		if (result != nullVector) // inside
		{
			return result;
		}
	}

	return VECTOR3(0);
}

SquareCollider::cornerArray_t SquareCollider::GetCorners(PosRot* center)
{
	cornerArray_t corners{ VECTOR3(0) };
	PosRot offset = (center == nullptr) ? 0 : *center;
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		VECTOR3 corner(0.0);
		for (size_t j = 0; j < corner.length(); ++j)
		{
			corner[j] = ((i & (1 << j)) ? 0.5 : -0.5) * sides[j];
		}
		corner = offset.GetRotation() * corner;
		corners[i] = offset.vector + corner;
	}
	return corners;
}

void* SquareCollider::Execute(GameObject* caller, void* params)
{
	return nullptr;
}

IComponent* SquareCollider::Clone(void* params) const
{
	return new SquareCollider(*this);
}

VECTOR3 SquareCollider::CollideWith(GameObject& caller, GameObject& other)
{
	ICollider* otherCollider = other.components.GetComponent<ICollider*>();
	if (dynamic_cast<SphereCollider*> (otherCollider))
	{
		return CollideWithSphere(caller.transform.position, other.transform.position, dynamic_cast<SphereCollider*>(otherCollider));
	}
	else if (dynamic_cast<SquareCollider*> (otherCollider))
	{
		return CollideWithSquare(caller.transform.position, other.transform.position, dynamic_cast<SquareCollider*>(otherCollider));
	}
	return VECTOR3(0);
}

VECTOR3 SquareCollider::CollideWith(PosRot& center, VECTOR3& point)
{
	VECTOR3 result(0);
	QUATERNION invOrientation = glm::inverse(center.GetRotation());
	VECTOR3 localPoint = invOrientation * (point)-center.vector;

	for (size_t i = 0; i < localPoint.length(); i++)
	{
		if (glm::abs(localPoint[i]) > sides[i] / 2.0)
		{
			// outside
			return result;
		}
	}
	uintStandard_t indexOfClosest = 0;
	VECTOR3 distances (0);
	for (size_t i = 0; i < localPoint.length(); i++)
	{
		distances[i] = glm::min(sides[i] / 2.0 - localPoint.x, localPoint.x + sides[i] / 2.0);
		if (distances[i] < distances[indexOfClosest])
		{
			indexOfClosest = i;
		}
	}
	result[indexOfClosest] = (localPoint[indexOfClosest] >= 0 ? 1.0 : -1.0);
	result = result * center.GetRotation();
	return result;
}

VECTOR3 SquareCollider::GetClosestPoint(PosRot& center, VECTOR3& point)
{
	cornerArray_t corners = GetCorners(&center);
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
