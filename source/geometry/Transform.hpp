#ifndef TRANSFORM
#define TRANSFORM

class Transform;

#include "../defines.hpp"
#include INCL_GLM
#include INCL_INTERFACES
#define GLM_FORCE_QUAT_DATA_WXYZ
#include INCL_QUATERNION


class Transform
{
public:
	VECTOR3 position;
	VECTOR3 velocity;
	VECTOR3 acceleration;

	QUATERNION rotation;
	QUATERNION angularVelocity;
	QUATERNION angularAcceleration;
	realStandard_t mass;

	// TODO: apply force, apply motion

	// Constructors
	Transform()	: position(0), velocity(0), acceleration(0), rotation(0, 0, 0, 0), angularVelocity(0, 0, 0, 0), angularAcceleration(0, 0, 0, 0), mass(0)
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


	void ApplyForce(VECTOR3 force);
	void ApplyForce(VECTOR3 forceNormal, realStandard_t strength);
	void ApplyRotation(QUATERNION rotation);

	Transform Derive()
	{
		Transform result;
		result.position = this->velocity;
		result.velocity = this->acceleration;
		result.acceleration = VECTOR3(0);
		result.rotation = this->angularVelocity;
		result.angularVelocity = this->angularAcceleration;
		result.angularAcceleration = glm::identity<QUATERNION>();
		return result;
	}
};


#endif
