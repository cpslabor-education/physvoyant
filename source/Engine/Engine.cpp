#include "Engine.hpp"
#include "../Defines.hpp"
#include <iostream>
#include <chrono>

Engine* Engine::instancePtr = nullptr;

Engine::~Engine()
{
	DestroyAllWindows();
	delete windows;
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

void Engine::WriteInfo(char* message)
{
	std::cout << message << std::endl;
}

void Engine::WriteInfo(const char* message)
{
	std::cout << message << std::endl;
}

void Engine::WriteInfo(long long message)
{
	std::cout << message << std::endl;
}

void Engine::WriteInfo(double message)
{
	std::cout << message << std::endl;
}

unsigned long long Engine::GetEpochTime()
{
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	return ms.count();
}

void Engine::KeyCallback(GLFWwindow* windows, int key, int scancode, int action, int mods)
{
}

int Engine::CreateWindow(int width, int height, char* title)
{
	return CreateWindow(width, height, (const char*)title);

}

int Engine::CreateWindow(int width, int height, const char* title)
{
	int freeIndex = -1;

	for (int i = 0; i < MAX_WINDOWS; i++)
	{
		if (windows[i] == nullptr)
		{
			freeIndex = i;
			break;
		}
	}

	if (freeIndex == -1)
	{
	#if DEBUG_LEVEL >= 1
		WriteInfo("Can't create more windows");
	#endif // DEBUG_LEVEL >= 1
		return -1;
	}

	windows[freeIndex] = new Renderer();

	return windows[freeIndex]->CreateWindow(width, height, title);
}

void Engine::DestroyWindow(int index)
{
	delete windows[index];
}

void Engine::DestroyAllWindows()
{
	for (int i = 0; i < MAX_WINDOWS; i++)
	{
		delete windows[i];
	}
}

Engine::Engine()
{
	Initialise();
}

void Engine::Initialise()
{
	windows = new Renderer * [MAX_WINDOWS];
	for (int i = 0; i < MAX_WINDOWS; i++)
	{
		windows[i] = nullptr;
	}
	glfwSetErrorCallback(ErrorCallback);
}