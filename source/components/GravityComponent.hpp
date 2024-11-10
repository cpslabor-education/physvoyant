#ifndef GRAVITY_COMPONENT
#define GRAVITY_COMPONENT

#include "../defines.hpp"
#include "ComponentBase.hpp"

class GravityComponent : public ComponentBase
{
public:
	static realStandard_t gravitationalConstant;
	realStandard_t mass;
	bool pull;
	GravityComponent() : mass(0), pull(true)
	{
	}

	GravityComponent(const GravityComponent& other) = default;

	~GravityComponent()
	{
	}

	// Inherited via ComponentBase
	void* Execute(GameObject* caller, void* params) override;

	IComponent* Clone(void* params) const override;

};


#endif