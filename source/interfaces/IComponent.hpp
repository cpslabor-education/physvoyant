#ifndef ICOMPONENT
#define ICOMPONENT

class GameObject;

__interface IComponent
{
public:
	void Execute(GameObject* caller, void* params = nullptr);
	IComponent* Clone(void* params = nullptr) const;
};

#endif
