#include "Colliders.hpp"
#include INCL_GAME_OBJECTS

VECTOR3 SphereCollider::CollideWithSphere(PosRot& center, PosRot& otherCenter, SphereCollider* otherCollider)
{
	VECTOR3 result(0);
	realStandard_t dist = otherCollider->radius + this->radius - glm::distance(center.vector, otherCenter.vector);
	if (dist >= 0)
	{
		result = glm::normalize(otherCenter.vector - center.vector) * dist;
	}
	return result;
}

VECTOR3 SphereCollider::CollideWithSquare(PosRot& center, PosRot& otherCenter, SquareCollider* otherCollider)
{
	return -(otherCollider->CollideWithSphere(otherCenter, center, this));
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
	return NULLVECTOR;
}

VECTOR3 SphereCollider::CollideWith(PosRot& center, VECTOR3& point)
{
	VECTOR3 result(0);
	realStandard_t dist = this->radius - glm::distance(center.vector, point);
	if (dist >= 0)
	{
		result = glm::normalize(point - center.vector) * dist;
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
	if (closest == otherCenter.vector)
	{
		VECTOR3 result(0);
		VECTOR3 escape = CollideWith(center, closest);
		if (escape == NULLVECTOR)
		{
			VECTOR3 diff = otherCenter.vector + glm::normalize(center.vector - otherCenter.vector) * REAL_EPSILON;
			diff = CollideWith(center, diff);
			PosRot newCenter (otherCenter.vector + diff);
			result = -(otherCollider->CollideWith(newCenter, closest)) + diff;
		}
		else
		{
			result = escape + glm::normalize(escape) * otherCollider->GetRaduis();
		}
		return result;
	}
	return -(otherCollider->CollideWith(otherCenter, closest));
}

VECTOR3 SquareCollider::CollideWithSquare(PosRot& center, PosRot& otherCenter, SquareCollider* otherCollider)
{
	VECTOR3 result(0);
	cornerArray_t cornersSelf = GetCorners(&center);
	VECTOR3 axesSelf[DIMENSIONS];
	for (size_t i = 0; i < DIMENSIONS; i++)
	{
		VECTOR3 axis(0);
		axis[i] = 1.0;
		axesSelf[i] = glm::normalize(center.GetRotation() * axis);
	}

	cornerArray_t cornersOther = otherCollider->GetCorners(&otherCenter);
	VECTOR3 axesOther[DIMENSIONS];
	for (size_t i = 0; i < DIMENSIONS; i++)
	{
		VECTOR3 axis(0);
		axis[i] = 1.0;
		axesOther[i] = glm::normalize(otherCenter.GetRotation() * axis);
	}

	realStandard_t minOverlap = std::numeric_limits<realStandard_t>::max();

	// First projection
	for (size_t i = 0; i < DIMENSIONS; ++i)
	{
		realStandard_t minSelf = std::numeric_limits<realStandard_t>::max();
		realStandard_t maxSelf = std::numeric_limits<realStandard_t>::min();
		realStandard_t minOther = std::numeric_limits<realStandard_t>::max();
		realStandard_t maxOther = std::numeric_limits<realStandard_t>::min();

		for (size_t j = 0; j < sizeof(cornerArray_t) / sizeof(VECTOR3); j++)
		{
			realStandard_t dotSelf = glm::dot(axesSelf[i], cornersSelf[j]);
			realStandard_t dotOther = glm::dot(axesSelf[i], cornersOther[j]);

			if (dotSelf < minSelf) { minSelf = dotSelf; }
			if (dotSelf > maxSelf) { maxSelf = dotSelf; }

			if (dotOther < minOther) { minOther = dotOther; }
			if (dotOther > maxOther) { maxOther = dotOther; }
		}

		if (minSelf > maxOther || minOther > maxSelf)
		{
			// proven for no collision
			return result;
		}
		else
		{
			realStandard_t overlap = glm::min(maxSelf - minOther, maxOther - minSelf);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;

				if (maxSelf > maxOther)
				{
					result = axesSelf[i] * overlap;
				}
				else
				{
					result = -axesSelf[i] * overlap;
				}
			}
		}
	}

	minOverlap = std::numeric_limits<realStandard_t>::max();

	// Check the other object for collision
	for (size_t i = 0; i < DIMENSIONS; ++i)
	{
		realStandard_t minSelf = std::numeric_limits<realStandard_t>::max();
		realStandard_t maxSelf = std::numeric_limits<realStandard_t>::min();
		realStandard_t minOther = std::numeric_limits<realStandard_t>::max();
		realStandard_t maxOther = std::numeric_limits<realStandard_t>::min();

		for (size_t j = 0; j < sizeof(cornerArray_t) / sizeof(VECTOR3); j++)
		{
			realStandard_t dotSelf = glm::dot(axesOther[i], cornersSelf[j]);
			realStandard_t dotOther = glm::dot(axesOther[i], cornersOther[j]);

			if (dotSelf < minSelf) { minSelf = dotSelf; }
			if (dotSelf > maxSelf) { maxSelf = dotSelf; }

			if (dotOther < minOther) { minOther = dotOther; }
			if (dotOther > maxOther) { maxOther = dotOther; }
		}

		if (minSelf > maxOther || minOther > maxSelf)
		{
			// proven for no collision
			return result;
		}
		else
		{
			realStandard_t overlap = glm::min(maxSelf - minOther, maxOther - minSelf);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;

				if (maxSelf > maxOther)
				{
					result = -axesOther[i] * overlap;
				}
				else
				{
					result = axesOther[i] * overlap;
				}
			}
		}
	}
	return result;
}

SquareCollider::cornerArray_t SquareCollider::GetCorners(PosRot* center)
{
	cornerArray_t corners{ NULLVECTOR };
	PosRot offset = (center == nullptr) ? 0 : *center;
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		VECTOR3 corner(0.0);
		for (size_t j = 0; j < corner.length(); ++j)
		{
			corner[j] = ((i & ((size_t)1 << j)) ? halfSides[j] : -halfSides[j]);
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
	return NULLVECTOR;
}

VECTOR3 SquareCollider::CollideWith(PosRot& center, VECTOR3& point)
{
	VECTOR3 result(0);
	QUATERNION invOrientation = glm::inverse(center.GetRotation());
	VECTOR3 localPoint = invOrientation * (point)-center.vector;

	for (size_t i = 0; i < localPoint.length(); i++)
	{
		if (glm::abs(localPoint[i]) > halfSides[i])
		{
			// outside
			return result;
		}
	}
	uintStandard_t indexOfClosest = 0;
	VECTOR3 distances(0);
	for (size_t i = 0; i < localPoint.length(); i++)
	{
		distances[i] = glm::min(halfSides[i] - localPoint[i], localPoint[i] + halfSides[i]);
		if (distances[i] < distances[indexOfClosest])
		{
			indexOfClosest = i;
		}
	}
	result[indexOfClosest] = (localPoint[indexOfClosest] >= 0 ? 1.0 : -1.0) * distances[indexOfClosest];
	result = result * center.GetRotation();
	return result;
}

VECTOR3 SquareCollider::GetClosestPoint(PosRot& center, VECTOR3& point)
{
	cornerArray_t corners = GetCorners(&center);
	VECTOR3 closest = point;
	for (size_t i = 0; i < closest.length(); i++)
	{
		realStandard_t min = std::numeric_limits<realStandard_t>::max();
		realStandard_t max = std::numeric_limits<realStandard_t>::min();
		for (size_t j = 0; j < (size_t)1 << DIMENSIONS; j++)
		{
			max = glm::max(max, corners[j][i]);
			min = glm::min(min, corners[j][i]);
		}
		closest[i] = glm::clamp(closest[i], min, max);
	}
	return closest;
}
