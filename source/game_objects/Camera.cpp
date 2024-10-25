#include "../glad/gl.h"
#include "Camera.hpp"
#define GLAD_GL_IMPLEMENTATION
#include INCL_GLFW
#include INCL_ENGINE

//#include INCL_SCENE

const VECTOR3 Camera::forward = { 0, 0, 1 };

Camera::Camera() : program(0), vertexShader(0), fragmentShader(0), transform(), renderCollector()
{

}

Camera::~Camera()
{
	DeleteShader(vertexShader);
	DeleteShader(fragmentShader);
}

void Camera::InitComponents()
{
	program = glCreateProgram();
}

GLuint Camera::CompileShader(GLuint type, const char* source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Check for compile errors
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		Engine::WriteInfo("ERROR::SHADER::COMPILATION_FAILED");
		Engine::WriteInfo(__FILE__);
		Engine::WriteInfo(__LINE__);
		Engine::WriteInfo(infoLog);
		DeleteShader(shader);
	}
	return shader;
}

void Camera::DeleteShader(GLuint& shader)
{
	if (shader != 0)
	{
		glDeleteShader(shader);
		shader = 0;
	}
}

void Camera::AttachShader(GLuint shader)
{
	glAttachShader(program, shader);

	GLint success = 0;
	glGetProgramiv(program, GL_ATTACHED_SHADERS, &success);
	if (success == GL_FALSE)
	{
		Engine::WriteInfo("Error: Shader attachment failed for program: " + program);
		return;
	}
}

void Camera::LinkProgram()
{
	glLinkProgram(program);
	GLint success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		Engine::WriteInfo("Error: Program linking failed.");
		Engine::WriteInfo(infoLog);
	}
}

void* Camera::Execute(Scene* caller, void* params)
{
	if (caller->window != nullptr)
	{
		


		// Set the data 
		uintStandard_t bufferSize = 0;
		std::vector<Vertex> verticies;
		VECTOR3 target = transform.position.vector + forward * transform.position.GetRotation();
		glm::mat4 view = glm::lookAt(transform.position.vector, target, Engine::upVector);


		glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(float), verticies.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	return nullptr;
}

ISceneComponent* Camera::Clone(void* params) const
{
	return new Camera(*this);
}
