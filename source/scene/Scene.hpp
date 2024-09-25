#ifndef SCENE
#define SCENE

class Scene;

#include "../defines.hpp"
#include INCL_ENGINE
#include INCL_CAMERA
#include INCL_INTERFACES
#include INCL_GAME_OBJECTS
#include <vector>


class Scene 
{
	Camera camera;
	ChunkedVector<GameObject*> gameObjects;
	OctTree<GameObject*> objectTree;
	size_t boundsWidth;
	GLFWwindow* window;
public:

	Scene();

	~Scene();

	void UpdateScene();

	void AddObject(GameObject* object);
};


#endif
