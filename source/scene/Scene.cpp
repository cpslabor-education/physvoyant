#include "Scene.hpp"
#include "../defines.hpp"

Scene::Scene() : camera(), gameObjects(), window(nullptr), objectTree(), components(this)
{

}

Scene::~Scene()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	for (size_t i = 0; i < components.Count(); i++)
	{
		delete components[i];
	}
	delete objectTree;
}

void Scene::UpdateScene()
{
	components.UpdateAll();
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
	// camera.Update();
}

void Scene::AddObject(GameObject* object)
{
	gameObjects.push_back(object);
	objectTree->Insert(object, object->transform.position);
}
