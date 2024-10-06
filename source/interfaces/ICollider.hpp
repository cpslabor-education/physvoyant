#ifndef ICOLLIDER
#define ICOLLIDER

class GameObject;

#include "../defines.hpp"
#include INCL_GLM

__interface ICollider : public IComponent
{
public:
	/// <summary>
	/// Checks for colliosion between two GameObjects
	/// </summary>
	/// <param name="caller">The parent of the collider (should be "this")</param>
	/// <param name="other">The other object to check for collision</param>
	/// <returns>The direction of collsion</returns>
	VECTOR3 CollideWith(GameObject* caller, GameObject* other);
	VECTOR3 CollideWith(GameObject* caller, VECTOR3& point);
};

#endif
