#ifndef SCENEFACTORY
#define SCENEFACTORY

class SceneFactory;

#include "../defines.hpp"
#include INCL_SCENE

class SceneFactory
{
public:
	static Scene* GetDefaultScene();
	static Scene* FloatingShpehere();
	static Scene* SpheresCollide();
	static Scene* TonsOfSpheres();
};



#endif
