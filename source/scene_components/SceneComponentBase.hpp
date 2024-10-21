#ifndef SCENE_COMPONENT_BASE
#define SCENE_COMPONENT_BASE


#include "../defines.hpp"
#include INCL_INTERFACES

class SceneComponentBase : public ISceneComponent
{
protected:
	componentID_t ID;
public:
	SceneComponentBase(componentID_t ID = 0) : ID(ID) {};
	virtual ~SceneComponentBase() = default;

	virtual componentID_t GetID() const { return ID; };
	virtual void SetID(componentID_t ID) { this->ID = ID; }
};



#endif
