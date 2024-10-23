#ifndef CAMERA
#define CAMERA

class Camera;

#include "../defines.hpp"
#include INCL_GLFW
#include INCL_INTERFACES
#include "../scene_components/SceneComponentBase.hpp"

class Camera : SceneComponentBase
{
public:
	Camera();
	~Camera();

	// Inherited via ISceneComponent
	void* Execute(Scene* caller, void* params = nullptr) override;
	ISceneComponent* Clone(void* params = nullptr) const override;
};


#endif
