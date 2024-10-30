#include "../glad/gl.h"
#include "Camera.hpp"
#define GLAD_GL_IMPLEMENTATION
#include INCL_GLFW
#include INCL_ENGINE
#include INCL_GLM
#include <glm/gtc/type_ptr.hpp>

//#include INCL_SCENE

const VECTOR3 Camera::forward = { 0, 0.001, 1 };

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
		glUseProgram(program);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		VECTOR3 target = transform.position.vector + forward * transform.position.GetRotation();
		int width, height;
		glfwGetWindowSize(caller->window, &width, &height);

		glm::mat4 view = glm::identity<glm::mat4>(); //glm::lookAt(transform.position.vector, target, Engine::upVector);

		float left = -1.0f;
		float right = 1.0f;
		float bottom = -1.0f;
		float top = 1.0f;
		float near = -1.0f;
		float far = 1.0f;
		glm::mat4 projection = glm::ortho(left, right, bottom, top, near, far); // glm::perspective(90.0, 1.0 * width / height, 1.0, 100.0);



		const GLint projectionLocation = glGetUniformLocation(program, "projection");
		const GLint viewLocation = glGetUniformLocation(program, "view");


		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		//glUniformMatrix4fv(
		//	glGetUniformLocation(program, "projection"),
		//	1,
		//	GL_FALSE,
		//	glm::value_ptr(projection)
		//	);

		for (std::list<IRenderable*>::iterator it = renderCollector.begin(); it != renderCollector.end(); ++it)
		{
			(*it)->Draw();
		}

		// glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(float), verticies.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	return nullptr;
}

ISceneComponent* Camera::Clone(void* params) const
{
	return new Camera(*this);
}
