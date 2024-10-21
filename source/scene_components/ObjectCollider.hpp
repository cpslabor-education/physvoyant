#ifndef OBJECTS_COLLIDER
#define OBJECTS_COLLIDER

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_MATH
#include "SceneComponentBase.hpp"

class ObjectCollider : public SceneComponentBase
{
public:
	ObjectCollider() : SceneComponentBase() {};
	~ObjectCollider() = default;
	// Inherited via ISceneComponent
	void* Execute(Scene* caller, void* params) override;
	ISceneComponent* Clone(void* params) const override;
};


#endif
