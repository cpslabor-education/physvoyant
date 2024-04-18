#ifndef ENGINE
#define ENGINE

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

private:
	Engine();
	void Initialise();
	static Engine* instancePtr;

};
Engine* Engine::instancePtr = nullptr; // Move this to the .cpp file


#endif