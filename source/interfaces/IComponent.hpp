#ifndef ICOMPONENT
#define ICOMPONENT

#include "../defines.hpp"

class GameObject;

class IComponent
{
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	virtual void* Execute(GameObject* caller, void* params = nullptr) = 0;
	virtual IComponent* Clone(void* params = nullptr) const = 0;
};

#endif
