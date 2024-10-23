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
public:
	Camera* camera;
	std::vector<GameObject*> gameObjects;
	GLFWwindow* window;
	OctTree<GameObject*>* objectTree;
	ComponentContainer<ISceneComponent*> components;

	Scene();

	~Scene();

	void UpdateScene();
	void AddObject(GameObject* object);
	void SetupWindow(int width, int height, char* title);
};


#endif
