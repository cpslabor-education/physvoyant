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
	Scene();

	~Scene();

	void UpdateScene();

	bool AddObject(GameObject* object);

private:

	Camera* camera;
	ChunkedVector<GameObject*> gameObjects;
	GLFWwindow* window;

};


#endif
