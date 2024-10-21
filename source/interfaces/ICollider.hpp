#ifndef ICOLLIDER
#define ICOLLIDER

class GameObject;
class PosRot;

#include "../defines.hpp"
#include INCL_GLM

class ICollider
{
public:
	/// <summary>
	/// Checks for colliosion between two GameObjects
	/// </summary>
	/// <param name="caller">The parent of the collider (should be "this")</param>
	/// <param name="other">The other object to check for collision</param>
	/// <returns>The direction of collsion</returns>
	virtual VECTOR3 CollideWith(GameObject& caller, GameObject& other) = 0;
	virtual VECTOR3 CollideWith(PosRot& center, VECTOR3& point) = 0;
};

#endif
