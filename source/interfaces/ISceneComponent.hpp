#ifndef ISCENE_COMPONENT
#define ISCENE_COMPONENT

#include "../defines.hpp"

class Scene;

__interface ISceneComponent
{
public:
	void* Execute(Scene* caller, void* params = nullptr);
	ISceneComponent* Clone(void* params = nullptr) const;
	componentID_t GetID();
};

#endif