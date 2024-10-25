#ifndef RENDERABLE_BASE
#define RENDERABLE_BASE

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_COMPONENTS
#include INCL_DATA_STRUCTURES

class RenderableBase : public IRenderable, public ComponentBase
{
protected:
	VertexBuffer buffer;
public:
	RenderableBase()
	{
	}

	~RenderableBase()
	{
	}

	virtual VertexBuffer* GetVertexBuffer(GameObject* caller) = 0;

	// Inherited via ComponentBase
	virtual void* Execute(GameObject* caller, void* params) override = 0;
	virtual IComponent* Clone(void* params) const override = 0;
	virtual void* Execute(GameObject* caller, void* params = nullptr) = 0;
	virtual IComponent* Clone(void* params = nullptr) const = 0;
};



#endif
