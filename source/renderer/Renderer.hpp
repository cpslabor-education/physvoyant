#ifndef RENDERER
#define RENDERER

#include "../defines.hpp"
#include INCL_GLFW

class Renderer
{
public:
	Renderer();

	Renderer(Renderer& other)
	{
	}

	~Renderer();

	void operator=(const Renderer& other)
	{

	}

	int CreateWindow(int width, int height, char* title);
	int CreateWindow(int width, int height, const char* title);

	GLFWwindow* window;

private:
	void Initialise();

};

#endif
