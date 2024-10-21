#ifndef ENGINE
#define ENGINE

#include "../defines.hpp"
#include INCL_GLFW
#include INCL_RENDERER
#include INCL_DATA_STRUCTURES
#include INCL_SCENE
#include "Clock.hpp"

class Engine
{
	Engine();
	void Initialise();
	static Engine* instancePtr;
	Scene* activeScene;
	uintStandard_t fps;
public:
	Clock clock;
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
	template<typename T>
	static void WriteInfo(T message)
	{
		std::cout << message << std::endl;
	}

	void SetActiveScene(Scene* scene);
	Scene* GetActiveScene();
	void Start();
	void Stop();

	bool Run();
	void Time(uintStandard_t fps = -1);

	static int MemCheck();

	//int CreateWindow(int width, int height, char* title);
	//int CreateWindow(int width, int height, const char* title);
	//void DestroyWindow(int index);
	//void DestroyAllWindows();

	//void FocusWindow(int index);
	//void FocusWindow(GLFWwindow* window);

	uintStandard_t GetFPS() const
	{
		return fps;
	}

	void SetFPS(const uintStandard_t& value)
	{
		fps = value;
	}
};


#endif