#ifndef SCENEFACTORY
#define SCENEFACTORY

class SceneFactory;

#include "../defines.hpp"
#include INCL_SCENE

static class SceneFactory
{
public:
	static Scene* GetDefaultScene();
};



#endif
