#ifndef RENDERABLE_BASE
#define RENDERABLE_BASE

#include "../defines.hpp"
#include INCL_ENGINE
#include INCL_INTERFACES
#include INCL_COMPONENTS
#include INCL_DATA_STRUCTURES

class RenderableBase : public IRenderable, public ComponentBase
{
public:
	RenderableBase()
	{
		Engine::GetInstance()->GetActiveScene()->camera->renderCollector.push_back(this);
	};

	virtual ~RenderableBase()
	{
		for (std::list<IRenderable*>::iterator it = Engine::GetInstance()->GetActiveScene()->camera->renderCollector.begin(); it != Engine::GetInstance()->GetActiveScene()->camera->renderCollector.end(); ++it) 
		{
			if (*it == this)
			{
				Engine::GetInstance()->GetActiveScene()->camera->renderCollector.erase(it);
				break;
			}
		}
	};
};



#endif
