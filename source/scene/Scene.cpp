#include "Scene.hpp"
#include "../defines.hpp"

Scene::Scene() : camera(), gameObjects(), window(nullptr), objectTree(nullptr), components()
{

}

Scene::~Scene()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
		gameObjects[i] = nullptr;
	}
	gameObjects.clear();
	delete objectTree;
}

void Scene::UpdateScene()
{
	components.UpdateAll(this);
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
	// camera.Update();
}

void Scene::AddObject(GameObject* object)
{
	gameObjects.push_back(object);
	if (objectTree != nullptr)
	{
		objectTree->Insert(object, object->transform.position.vector);
	}
}
