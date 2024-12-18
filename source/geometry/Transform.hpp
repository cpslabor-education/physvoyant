#ifndef TRANSFORM
#define TRANSFORM

class Transform;

#include "../defines.hpp"
#include "PosRot.hpp"


class Transform
{
public:
	PosRot position;
	PosRot* positionLock;
	PosRot positionOffset;
	PosRot velocity;
	PosRot acceleration;

	realStandard_t mass;

	// TODO: apply force, apply motion

	// Constructors
	Transform() : position(0), positionLock(nullptr), positionOffset(0), velocity(0), acceleration(0), mass(0)
	{
	}

	Transform(const Transform& other) = default;
	Transform(Transform&& other) = default;

	// Destructor
	~Transform() = default;

	// Assignment operators
	Transform& operator=(const Transform& other);
	Transform& operator=(Transform&& other);

	// Comparison operators
	bool operator==(const Transform& other) const;
	bool operator!=(const Transform& other) const;


	void ApplyForce(VECTOR3 force)
	{
		acceleration.vector += force / mass;
	}
	void ApplyForce(VECTOR3 forceNormal, realStandard_t strength)
	{
		acceleration.vector += glm::normalize(forceNormal) * strength / mass;
	}
};


#endif
