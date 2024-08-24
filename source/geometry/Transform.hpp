#ifndef TRANSFORM
#define TRANSFORM

class Transform;

#include "../defines.hpp"
#include INCL_GLM
#include INCL_INTERFACES
#define GLM_FORCE_QUAT_DATA_WXYZ
#include INCL_QUATERNION


class Transform : public IUpdateable
{
	VECTOR3 position;
	VECTOR3 direction;
	QUATERNION rotation;
	double mass;
public:
	// Constructors
	Transform() : position(0, 0, 0), direction(0, 0, 0), rotation(0, 0, 0, 0), mass(0)
	{
	}

	Transform(const Transform& other) = default;
	Transform(Transform&& other) = default;

	// Destructor
	~Transform() = default;

	// Assignment operators
	Transform& operator=(const Transform& other);
	Transform& operator=(Transform&& other);

	// Binary arithmetic operators
	Transform operator+(const Transform& other) const; // ?
	Transform operator-(const Transform& other) const; // ?
	Transform operator*(const double& other) const; // scaling
	Transform operator/(const double& other) const; // scaling

	// Compound assignment operators
	Transform& operator+=(const Transform& other);
	Transform& operator-=(const Transform& other);
	Transform& operator*=(const double& other);
	Transform& operator/=(const double& other);

	// Comparison operators
	bool operator==(const Transform& other) const;
	bool operator!=(const Transform& other) const;


	void ApplyForce(VECTOR3 force);
	void ApplyRotation(QUATERNION rotation);


	// Inherited via IUpdateable
	void Update() override;


	VECTOR3 GetPosition() const
	{
		return position;
	}

	void SetPosition(const VECTOR3& value)
	{
		position = value;
	}

	void SetPosition(const double x, const double y, const double z)
	{
		position = VECTOR3(x, y, z);
	}


	VECTOR3 GetDirection() const
	{
		return direction;
	}

	void SetDirection(const VECTOR3& value)
	{
		direction = value;
	}

	void SetDirection(const double x, const double y, const double z)
	{
		position = VECTOR3(x, y, z);
	}


	QUATERNION GetRotation() const
	{
		return rotation;
	}

	void SetRotation(const QUATERNION& value)
	{
		rotation = value;
	}
	
	void SetRotation(const double w, const double x, const double y, const double z)
	{
		rotation = QUATERNION(w, x, y, z);
	}


	double GetMass() const
	{
		return mass;
	}

	void SetMass(const double& value)
	{
		mass = value;
	}
};


#endif
