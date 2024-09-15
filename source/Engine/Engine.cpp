#include "Engine.hpp"
#include <iostream>
#include <chrono>

Engine* Engine::instancePtr = nullptr;

Engine::~Engine()
{
	glfwTerminate();
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

void Engine::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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


void Engine::Initialise()
{
	activeScene = nullptr;
	glfwSetErrorCallback(ErrorCallback);
}

Engine::Engine() : activeScene(0), clock()
{

}
