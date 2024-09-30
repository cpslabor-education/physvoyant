#ifndef OBJECTS_COLLIDER
#define OBJECTS_COLLIDER

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_MATH

class ObjectCollider : public ISceneComponent
{
	componentID_t ID;
public:
	// Inherited via ISceneComponent
	void* Execute(Scene* caller, void* params) override;
	ISceneComponent* Clone(void* params) const override;
	componentID_t GetID() override;
};


#endif
