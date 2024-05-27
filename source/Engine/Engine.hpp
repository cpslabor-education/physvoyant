#ifndef ENGINE
#define ENGINE

#include <GLFW/glfw3.h>
#include "../Renderer/Renderer.hpp"

class Engine
{
public:
	Engine(Engine& other) = delete;

	void operator=(const Engine& other) = delete;

	~Engine();

	static Engine* GetInstance()
	{
		if (instancePtr == nullptr)
		{
			instancePtr = new Engine();
		}
		return instancePtr;
	}

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void ErrorCallback(int error, char* description);
	static void ErrorCallback(int error, const char* description);
	static void WriteInfo(char* message);
	static void WriteInfo(const char* message);
	static void WriteInfo(long long message);
	static void WriteInfo(double message);

	static unsigned long long GetEpochTime();

	int CreateWindow(int width, int height, char* title);
	int CreateWindow(int width, int height, const char* title);
	void DestroyWindow(int index);
	void DestroyAllWindows();


private:
	Engine();
	void Initialise();
	static Engine* instancePtr;
	Renderer** windows;

};


#endif