#include <iostream>
#include "defines.hpp"
#include "engine/Engine.hpp"


int main()
{
	Engine* e = Engine::GetInstance();
	Engine::InitGLFW();
	e->clock.SetPhysicsTimeStep(TO_TIME_UNIT(1.0 / 60.0));
	e->SetFPS(0);
	Scene* scene = nullptr;

	do
	{
		scene = SceneFactory::SceneTester();
		e->SetActiveScene(scene);
		if (scene == nullptr)
		{
			break;
		}

		bool close = false;

		while (!close)
		{
			close = e->Run();
			glfwPollEvents();
			e->Time(60);
		}
		delete e->GetActiveScene();
		e->manualExit = false;
	} while (scene != nullptr);

	Engine::StopGLFW();
	delete e;
	// std::cout << Engine::MemCheck();
	return 0;
}