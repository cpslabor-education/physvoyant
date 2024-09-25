#ifndef GAME_OBJECT
#define GAME_OBJECT

class GameObject;

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_DATA_STRUCTURES
#include INCL_GEOMETRY
#include <vector>

class GameObject : public IUpdateable
{
public:
	ComponentContainer<IComponent*, GameObject> components;
	Transform transform;

	// Constructors
	GameObject() : components(ComponentContainer<IComponent*, GameObject>(this)), transform()
	{

	}
	GameObject(const GameObject& other);
	GameObject(GameObject&& other);

	// Destructor
	virtual ~GameObject();

	// Inherited via IUpdateable
	virtual void Update() override;
};


#endif