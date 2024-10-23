#include "../glad/gl.h"
#include "Camera.hpp"
#include INCL_SCENE
#define GLAD_GL_IMPLEMENTATION
#include INCL_GLFW

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
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		return nullptr;
	}
}

ISceneComponent* Camera::Clone(void* params) const
{
	return new Camera(*this);
}
