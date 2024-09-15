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

	void AddObject(GameObject* object);

private:

	Camera* camera;
	ChunkedVector<GameObject*> gameObjects;
	// OctTree<GameObject*, 5> objectTree;
	size_t boundsWidth = OCTTREE_CHUNK_SIZE * glm::pow(2, 5);
	GLFWwindow* window;

};


#endif
