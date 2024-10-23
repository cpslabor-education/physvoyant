#include "Camera.hpp"
#include INCL_SCENE
#include INCL_GLFW
#define GLAD_GL_IMPLEMENTATION
#include <gl/GL.h>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void* Camera::Execute(Scene* caller, void* params)
{
	if (caller->window == nullptr)
	{
		return nullptr;
	}
	else
	{		
		GLuint vertex_buffer;
		return nullptr;
	}
}

ISceneComponent* Camera::Clone(void* params) const
{
	return new Camera(*this);
}
