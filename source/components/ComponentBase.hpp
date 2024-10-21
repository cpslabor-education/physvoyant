#ifndef COMPONENT_BASE
#define COMPONENT_BASE

#include "../defines.hpp"
#include INCL_INTERFACES

class ComponentBase : public IComponent
{
protected:
	componentID_t ID;
public:
	ComponentBase(componentID_t ID = 0) : ID(ID) {};
	virtual ~ComponentBase() = default;
	virtual componentID_t GetID() const { return ID; };
	virtual void SetID(componentID_t ID) { this->ID = ID; };
};

#endif
