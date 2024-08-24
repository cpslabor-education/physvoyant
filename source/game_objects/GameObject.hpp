#ifndef GAME_OBJECT
#define GAME_OBJECT

class GameObject;

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_DATA_STRUCTURES
#include INCL_GEOMETRY

class GameObject : public IUpdateable
{
	ChunkedVector<IComponent*> components;
public:
	Transform transform;

	// Constructors
	GameObject() : components()
	{

	}
	GameObject(const GameObject& other);
	GameObject(GameObject&& other);

	// Destructor
	virtual ~GameObject();

	// Inherited via IUpdateable
	virtual void Update() override;

	// GameObject
	template <typename T>
	ChunkedVector<T*> GetComponentsOfType()
	{
		ChunkedVector<T*> result;
		for (int i = 0; i < components.size(); i++)
		{
			T* val = dynamic_cast<T*>(components[i]);
			if (val)
			{
				result.push_back(val);
			}
		}
		return result;
	}

	template <typename T>
	T GetComponentOfType()
	{
		for (int i = 0; i < components.size(); i++)
		{
			T val = dynamic_cast<T>(components[i]);
			if (val)
			{
				return val;
			}
		}
		return T();
	}

	void AddComponent(IComponent* component);
	void AddComponent(IComponent&& component);

	void RemoveComponents(unsigned long long ID);

};


#endif
