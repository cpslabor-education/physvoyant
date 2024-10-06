#ifndef COLLIDERS
#define COLLIDERS

class SphereCollider;
class SquareCollider;

#include "../defines.hpp"
#include INCL_INTERFACES
#define GLM_FORCE_QUAT_DATA_WXYZ
#include INCL_QUATERNION
#include INCL_DATA_STRUCTURES
#include INCL_GAME_OBJECTS
#include <array>

class ColliderBase : public ICollider
{
protected:
	uintStandard_t layer;
	componentID_t ID;
public:
	ColliderBase() : layer(0), ID(0) {};
	ColliderBase(realStandard_t layer, uintStandard_t ID = 0) : layer(layer), ID(ID) {};
	virtual ~ColliderBase() = default;

	// Inherited via ICollider
	virtual void* Execute(GameObject* caller, void* params) = 0;
	virtual IComponent* Clone(void* params) const = 0;
	virtual componentID_t GetID() override { return ID; }
	virtual void SetID(componentID_t ID) override { this->ID = ID; }
	virtual VECTOR3 CollideWith(GameObject* caller, GameObject* other) = 0;
	virtual VECTOR3 CollideWith(GameObject* caller, VECTOR3& point) = 0;
	virtual VECTOR3 CollideWith(VECTOR3& center, VECTOR3& point) = 0;
	virtual bool IsInside(VECTOR3& center, VECTOR3& point) = 0;
	virtual VECTOR3 GetClosestPoint(VECTOR3& center, VECTOR3& point) = 0;
};

class SphereCollider : public ColliderBase
{
	realStandard_t radius;
	VECTOR3 CollideWithSphere(GameObject* caller, GameObject* other, SphereCollider* otherCollider);
	VECTOR3 CollideWithSquare(GameObject* caller, GameObject* other, SquareCollider* otherCollider);
public:
	SphereCollider();
	SphereCollider(const realStandard_t radius);
	~SphereCollider();

	// Inherited via ICollider
	void* Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject* caller, GameObject* other) override;
	VECTOR3 CollideWith(GameObject* caller, VECTOR3& point) override;
	VECTOR3 CollideWith(VECTOR3& center, VECTOR3& point) override;
	bool IsInside(VECTOR3& center, VECTOR3& point) override;
	VECTOR3 GetClosestPoint(VECTOR3& center, VECTOR3& point) override;

	realStandard_t GetRaduis() { return radius; }
	void SetRadius(realStandard_t raduis) { this->radius = radius; }

	uintStandard_t GetLayer() { return layer; }
	void Setlayer(uintStandard_t layer) { this->layer = layer; }
};

class SquareCollider : public ColliderBase
{
	VECTOR3 sides;
	QUATERNION orientation;
	VECTOR3 CollideWithSphere(GameObject* caller, GameObject* other, SphereCollider* otherCollider);
	VECTOR3 CollideWithSquare(GameObject* caller, GameObject* other, SquareCollider* otherCollider);
public:
	// Inherited via ICollider
	void* Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject* caller, GameObject* other) override;
	VECTOR3 CollideWith(GameObject* caller, VECTOR3& point) override;
	VECTOR3 CollideWith(VECTOR3& center, VECTOR3& point) override;
	bool IsInside(VECTOR3& center, VECTOR3& point) override;
	VECTOR3 GetClosestPoint(VECTOR3& center, VECTOR3& point) override;


	typedef std::array<VECTOR3, 1 << DIMENSIONS> cornerArray_t;
	cornerArray_t GetCorners();

	VECTOR3 GetSides() { return sides; }
	void SetSides(VECTOR3& sides) { this->sides = sides; }

	QUATERNION GetOrientation() { return orientation; }
	void SetOrientation(QUATERNION& orientation) { this->orientation = orientation; }
};

#endif
