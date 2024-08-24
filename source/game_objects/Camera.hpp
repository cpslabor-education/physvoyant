#ifndef CAMERA
#define CAMERA

#include "../defines.hpp"
#include INCL_GLFW
#include INCL_INTERFACES

class Camera : public IUpdateable
{
	GLFWwindow* displayWindow;
public:
	Camera();

	Camera(Camera& other);

	~Camera();

	void operator=(const Camera& other);

	// Inherited via IUpdateable
	void Update() override;
};


#endif
