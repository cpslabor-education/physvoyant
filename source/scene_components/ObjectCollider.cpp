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
					continue;
				}
				VECTOR3 inResult = VECTOR3(0);
				if (dynamic_cast<SphereCollider*>(inCollider))
				{
					inResult = dynamic_cast<SphereCollider*>(inCollider)->CollideWith(in, out);
				}
				else if (dynamic_cast<SquareCollider*>(inCollider))
				{
					inResult = dynamic_cast<SquareCollider*>(inCollider)->CollideWith(in, out);
				}
				if (inResult == VECTOR3(0))
				{
					// no collision
					continue;
				}
				else
				{
					// collision
					in->transform.ApplyForce(inResult);
					out->transform.ApplyForce(inResult);
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

componentID_t ObjectCollider::GetID()
{
	return ID;
}
