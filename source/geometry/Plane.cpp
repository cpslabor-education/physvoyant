#include "Plane.hpp"

Plane::Plane() : point(0), normal(0)
{
}

Plane::Plane(const VECTOR3& p1, const VECTOR3& p2, const VECTOR3& p3) : point(p1), normal(glm::normalize(glm::cross(p2 - p1, p3 - p1)))
{
}

bool Plane::operator==(const Plane& other) const
{
	return (this->normal == other.normal && this->point == other.point);
}

bool Plane::operator!=(const Plane& other) const
{
	return !(*this == other);
}
