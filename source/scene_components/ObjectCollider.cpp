#include "ObjectCollider.hpp"
#include INCL_COMPONENTS

void* ObjectCollider::Execute(Scene* caller, void* params)
{
	if (caller->objectTree == nullptr || true)
	{
		std::vector<GameObject*>& helper = (caller->gameObjects);
		for (size_t i = 0; i < helper.size() - 1; i++)
		{
			GameObject* out = helper[i];
			if (out->components.GetComponent<ICollider*>() == nullptr)
			{
				continue;
			}
			for (size_t j = i + 1; j < helper.size(); j++)
			{
				GameObject* in = helper[j];
				ICollider* inCollider = in->components.GetComponent<ICollider*>();
				if (inCollider == nullptr)
				{
					// No collider
					continue;
				}
				VECTOR3 inResult = inCollider->CollideWith(*in, *out);
				if (inResult == NULLVECTOR)
				{
					// no collision
					continue;
				}
				else
				{
					// collision
					VECTOR3 projection = glm::dot(in->transform.velocity.vector, inResult) / glm::dot(inResult, inResult) * inResult;
					VECTOR3 reflected = in->transform.velocity.vector - 2.0 * projection;
					in->transform.velocity.vector = reflected;
					out->transform.velocity.vector = -reflected;
					in->transform.position.vector -= inResult / 2.0;
					out->transform.position.vector += inResult / 2.0;
				}
			}
		}
	}
	else
	{

	}
	return nullptr;
}

ISceneComponent* ObjectCollider::Clone(void* params) const
{
	return new ObjectCollider(*this);
}
