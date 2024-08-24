#ifndef COLLIDERS
#define COLLIDERS

class SphereCollider;

#include "../defines.hpp"
#include INCL_INTERFACES

class SphereCollider : public ICollider
{
	double radius;
	unsigned __int64 layer;

public:
	SphereCollider();
	SphereCollider(const double radius, unsigned __int64 layer = 0);
	~SphereCollider();

	// Inherited via ICollider
	void Execute(GameObject* caller, void* params) override;
	IComponent* Clone(void* params) const override;
	VECTOR3 CollideWith(GameObject* caller, GameObject* other) override;

	double GetRaduis() { return radius; }
	void SetRadius(double raduis) { this->radius = radius; }

	unsigned __int64 GetLayer() { return layer; }
	void Setlayer(unsigned __int64 layer) { this->layer = layer; }
};

#endif
