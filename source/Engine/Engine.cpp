#include "../glad/gl.h"
#include "Engine.hpp"
#define GLAD_GL_IMPLEMENTATION
#include INCL_GLFW
#include <iostream>
#include <chrono>
#include <thread>

Engine* Engine::instancePtr = nullptr;
std::string Engine::shader_text =
R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec3 fragNormal; 

void main()
{
	gl_Position = projection * view * vec4(position, 1.0);
	vertexColor = color;
	fragNormal = normalize(mat3(view) * normal);
})";

std::string Engine::fragment_shader_text =
R"(
#version 330 core

in vec3 vertexColor;
in vec3 fragNormal;
out vec4 fragColor;

void main() 
{
	vec3 norm = normalize(fragNormal);
	vec3 colorVariation = vec3(0.5) + 0.5 * norm;

	fragColor = vec4(vertexColor * colorVariation, 1.0);
}
)";

VECTOR3 Engine::upVector = UPVECTOR;


Engine::~Engine()
{

}

void Engine::ErrorCallback(int error, char* description)
{
	std::cout << "Error code: " << error << "\nDescription: " << description << std::endl;
}

void Engine::ErrorCallback(int error, const char* description)
{
	std::cout << "Error code: " << error << "\nDescription: " << description << std::endl;
}

void Engine::SetActiveScene(Scene* scene)
{
	activeScene = scene;
}

Scene* Engine::GetActiveScene()
{
	return activeScene;
}

void Engine::InitGLFW()
{
	glfwSetErrorCallback(ErrorCallback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	WriteInfo("GLFW version:");
	WriteInfo(glfwGetVersionString());
}

void Engine::StopGLFW()
{
	glfwTerminate();
}

bool Engine::Run()
{
	++frameIndex;
	if (activeScene != nullptr)
	{
		activeScene->UpdateScene();
		return glfwWindowShouldClose(activeScene->window) || manualExit;
	}
	return true;
}

void Engine::Time(uintStandard_t fps)
{
	if (fps == 0)
	{
		fps = this->fps;
	}
	clock.SetCurrentTime();
	register intStandard_t delta = clock.DeltaTime();
	register intStandard_t timeToPass = TO_TIME_UNIT(1.0 / fps) - delta;
	std::this_thread::sleep_for(TIME_CAST_SIZE(timeToPass));
	clock.SetCurrentTime();
	clock.StartMeasure();
}

int Engine::MemCheck()
{
	return _CrtDumpMemoryLeaks();
}

void Engine::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		WriteInfo("Exit via key press");
		Engine::GetInstance()->manualExit = true;
	}

	if (key == GLFW_KEY_W)
	{
		Engine::GetInstance()->activeScene->camera->transform.position.vector += VECTOR3(0, 0.5, 0);
	}
	else if (key == GLFW_KEY_S)
	{
		Engine::GetInstance()->activeScene->camera->transform.position.vector += VECTOR3(0, -0.5, 0);
	}
	if (key == GLFW_KEY_A)
	{
		Engine::GetInstance()->activeScene->camera->transform.position.vector += VECTOR3(-0.5, 0, 0);
	}
	else if (key == GLFW_KEY_D)
	{
		Engine::GetInstance()->activeScene->camera->transform.position.vector += VECTOR3(0.5, 0, 0);
	}
	if (key == GLFW_KEY_E)
	{
		Engine::GetInstance()->activeScene->camera->transform.position.vector += VECTOR3(0, 0, 0.5);
	}
	else if (key == GLFW_KEY_Q)
	{
		Engine::GetInstance()->activeScene->camera->transform.position.vector += VECTOR3(0, 0, -0.5);
	}

	if (key == GLFW_KEY_UP)
	{
		QUATERNION rot = Engine::GetInstance()->activeScene->camera->transform.position.GetRotation();

		rot = glm::rotate(rot, -0.05, VECTOR3(1, 0, 0));

		Engine::GetInstance()->activeScene->camera->transform.position.SetRotation(rot);
	}
	else if (key == GLFW_KEY_DOWN)
	{
		QUATERNION rot = Engine::GetInstance()->activeScene->camera->transform.position.GetRotation();

		rot = glm::rotate(rot, 0.05, VECTOR3(1, 0, 0));

		Engine::GetInstance()->activeScene->camera->transform.position.SetRotation(rot);
	}
	if (key == GLFW_KEY_LEFT)
	{
		QUATERNION rot = Engine::GetInstance()->activeScene->camera->transform.position.GetRotation();

		rot = glm::rotate(rot, -0.05, VECTOR3(0, 0, 1));

		Engine::GetInstance()->activeScene->camera->transform.position.SetRotation(rot);
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		QUATERNION rot = Engine::GetInstance()->activeScene->camera->transform.position.GetRotation();

		rot = glm::rotate(rot, 0.05, VECTOR3(0, 0, 1));

		Engine::GetInstance()->activeScene->camera->transform.position.SetRotation(rot);
	}


#if DEBUG_LEVEL >= 1
	WriteInfo("Key pressed from:");
	WriteInfo(window);
#endif
}

//int Engine::CreateWindow(int width, int height, char* title)
//{
//	return CreateWindow(width, height, const_cast<char*>(title));
//}
//
//int Engine::CreateWindow(int width, int height, const char* title)
//{
//	int freeIndex = -1;
//
//	for (int i = 0; i < MAX_WINDOWS; i++)
//	{
//		if ((*windows)[i] == nullptr)
//		{
//			freeIndex = i;
//			break;
//		}
//	}
//
//	if (freeIndex == -1)
//	{
//	#if DEBUG_LEVEL >= 1
//		WriteInfo("Can't create more windows");
//	#endif // DEBUG_LEVEL >= 1
//		return freeIndex;
//	}
//
//	(*windows)[freeIndex] = new Renderer();
//	(*windows)[freeIndex]->CreateWindow(width, height, title);
//	return freeIndex;
//}
//
//void Engine::DestroyWindow(int index)
//{
//	delete (*windows)[index];
//}
//
//void Engine::DestroyAllWindows()
//{
//	for (int i = 0; i < MAX_WINDOWS; i++)
//	{
//		delete (*windows)[i];
//		(*windows)[i] = nullptr;
//	}
//}
//
//void Engine::FocusWindow(int index)
//{
//	glfwFocusWindow((*windows)[index]->window);
//}
//
//void Engine::FocusWindow(GLFWwindow* window)
//{
//	glfwFocusWindow(window);
//}

Engine::Engine() : activeScene(0), clock(), fps(0), frameIndex(0), manualExit(false)
{

}
