#ifndef ISCENE_COMPONENT
#define ISCENE_COMPONENT

#include "../defines.hpp"

class Scene;

class ISceneComponent
{
public:
	virtual void* Execute(Scene* caller, void* params = nullptr) = 0;
	virtual ISceneComponent* Clone(void* params = nullptr) const = 0;
};

#endif