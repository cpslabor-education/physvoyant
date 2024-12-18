#ifndef SCENEFACTORY
#define SCENEFACTORY

class SceneFactory;

#include "../defines.hpp"
#include INCL_SCENE

class SceneFactory
{
public:
	static Scene* SceneTester();
	static Scene* CubesCollide();
	static Scene* CameraTest();
	static Scene* ThreeBodies();
	static Scene* OrbitingPlanet();
	static Scene* NBodyProblem();
	static Scene* NBodyOptimized();
};



#endif
