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

	virtual componentID_t GetID() override { return ID; }
	virtual void SetID(componentID_t ID) override { this->ID = ID; }
	virtual uintStandard_t GetLayer() { return layer; }
	virtual void Setlayer(uintStandard_t layer) { this->layer = layer; }

	// Inherited via ICollider
	virtual void* Execute(GameObject* caller, void* params) = 0;
	virtual IComponent* Clone(void* params) const = 0;
	virtual VECTOR3 CollideWith(GameObject& caller, GameObject& other) = 0;
	virtual VECTOR3 CollideWith(PosRot& center, VECTOR3& point) = 0;
	virtual VECTOR3 GetClosestPoint(PosRot& center, VECTOR3& point) = 0;
};

class SphereCollider : public ColliderBase
{
	realStandard_t radius;
	VECTOR3 CollideWithSphere(PosRot& center, PosRot& otherCenter, SphereCollider* otherCollider);
	VECTOR3 CollideWithSquare(PosRot& center, PosRot& otherCenter, SquareCollider* otherCollider);
public:
	SphereCollider(const realStandard_t radius = 0) : radius(radius) {};
	~SphereCollider() = default;

	realStandard_t GetRaduis() { return radius; }
	void SetRadius(realStandard_t raduis) { this->radius = radius; }

	// Inherited via ColliderBase
	void* Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject& caller, GameObject& other) override;
	VECTOR3 CollideWith(PosRot& center, VECTOR3& point) override;
	VECTOR3 GetClosestPoint(PosRot& center, VECTOR3& point) override;
};

class SquareCollider : public ColliderBase
{
	VECTOR3 sides;
	VECTOR3 CollideWithSphere(PosRot& center, PosRot& otherCenter, SphereCollider* otherCollider);
	VECTOR3 CollideWithSquare(PosRot& center, PosRot& otherCenter, SquareCollider* otherCollider);
public:
	typedef std::array<VECTOR3, 1 << DIMENSIONS> cornerArray_t;
	cornerArray_t GetCorners(PosRot* center = nullptr);

	VECTOR3 GetSides() { return sides; }
	void SetSides(VECTOR3& sides) { this->sides = sides; }

	// Inherited via ColliderBase
	void* Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject& caller, GameObject& other) override;
	VECTOR3 CollideWith(PosRot& center, VECTOR3& point) override;
	VECTOR3 GetClosestPoint(PosRot& center, VECTOR3& point) override;

};

#endif
