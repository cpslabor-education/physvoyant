#ifndef ICOMPONENT
#define ICOMPONENT

#include "../defines.hpp"

class GameObject;

__interface IComponent
{
public:
	void* Execute(GameObject* caller, void* params = nullptr);
	IComponent* Clone(void* params = nullptr) const;
	componentID_t GetID();
	void SetID(componentID_t ID);
};

#endif
