#include "Renderer.hpp"
#include INCL_ENGINE


Renderer::Renderer()
{
	Initialise();
}

Renderer::~Renderer()
{
	glfwDestroyWindow(window);
}

int Renderer::CreateWindow(int width, int height, char* title)
{
	return CreateWindow(width, height, (const char*)title);
}

int Renderer::CreateWindow(int width, int height, const char* title)
{
	if (!glfwInit())
	{
	#if DEBUG_LEVEL >= 1
		WriteInfo("GLFW Initialisation failed");
	#endif // DEBUG_LEVEL >= 1
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == nullptr)
	{
	#if DEBUG_LEVEL >= 1
		WriteInfo("GLFW window creation failed");
	#endif // DEBUG_LEVEL >= 1
	}

	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, Engine::KeyCallback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	return 0;
}

void Renderer::Initialise()
{
	window = nullptr;
}
