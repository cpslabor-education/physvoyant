#ifndef COLLIDERS
#define COLLIDERS

class SphereCollider;

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_QUATERNION

class SphereCollider : public ICollider
{
	realStandard_t radius;
	uintStandard_t layer;
public:
	SphereCollider();
	SphereCollider(const realStandard_t radius, uintStandard_t layer = 0);
	~SphereCollider();

	// Inherited via ICollider
	void Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject* caller, GameObject* other) override;
	VECTOR3 CollideWith(GameObject* caller, VECTOR3* point) override;

	realStandard_t GetRaduis() { return radius; }
	void SetRadius(realStandard_t raduis) { this->radius = radius; }

	uintStandard_t GetLayer() { return layer; }
	void Setlayer(uintStandard_t layer) { this->layer = layer; }
};

class SquareCollider : public ICollider
{
	VECTOR3 sides;
	QUATERNION orientation;
	uintStandard_t layer;
public:
	// Inherited via ICollider
	void Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject* caller, GameObject* other) override;
	VECTOR3 CollideWith(GameObject* caller, VECTOR3* point) override;
};

#endif
