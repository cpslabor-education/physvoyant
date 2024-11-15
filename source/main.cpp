#include <iostream>
#include "defines.hpp"
#include "engine/Engine.hpp"


int main()
{
	Engine* e = Engine::GetInstance();
	Engine::InitGLFW();
	e->clock.SetPhysicsTimeStep(TO_TIME_UNIT(1.0 / 60.0));
	e->SetFPS(0);

	e->SetActiveScene(SceneFactory::OrbitingPlanet());

	bool close = false;

	while (!close)
	{
		close = e->Run();
		glfwPollEvents();
		e->Time(60);
	}

	delete e->GetActiveScene();
	Engine::StopGLFW();
	delete e;
	std::cout << Engine::MemCheck();
	return 0;
}