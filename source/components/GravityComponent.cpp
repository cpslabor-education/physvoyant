#include "GravityComponent.hpp"
#include <vector>
#include INCL_ENGINE

realStandard_t GravityComponent::gravitationalConstant = 6.674010551359e-11;

void* GravityComponent::Execute(GameObject* caller, void* params)
{
	if (!pull)
	{
		return nullptr;
	}
	std::vector<GameObject*>& helper = Engine::GetInstance()->GetActiveScene()->gameObjects;

	for (size_t i = 0; i < helper.size(); i++)
	{
		GravityComponent* other = helper[i]->components.GetComponent<GravityComponent*>();
		if (other != nullptr && other != this)
		{
			realStandard_t dist = glm::distance(caller->transform.position.vector, helper[i]->transform.position.vector);
			if (dist <= SNE16)
			{
				continue;
			}
			realStandard_t force = gravitationalConstant * ((this->mass * other->mass) / (dist * dist)) / other->mass;
			VECTOR3 pull = (caller->transform.position.vector - helper[i]->transform.position.vector) * force;
			helper[i]->transform.acceleration.vector += pull;
		}
	}

	return nullptr;
}

IComponent* GravityComponent::Clone(void* params) const
{
	return new GravityComponent(*this);
}
