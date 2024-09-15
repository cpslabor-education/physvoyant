#ifndef PLANE
#define PLANE

#include "../defines.hpp"
#include INCL_GLM
#include INCL_GEOMETRY


class Plane
{
	VECTOR3 point;
	VECTOR3 normal;
public:
	// Constructors
	Plane();
	Plane(const VECTOR3& p1, const VECTOR3& p2, const VECTOR3& p3);
	Plane(const Plane& other) = default;
	Plane(Plane&& other) = default;

	// Destructor
	~Plane() = default;

	// Assignment operators
	Plane& operator=(const Plane& other) = default;
	Plane& operator=(Plane&& other) = default;

	// Comparison operators
	bool operator==(const Plane& other) const;
	bool operator!=(const Plane& other) const;
};


#endif
