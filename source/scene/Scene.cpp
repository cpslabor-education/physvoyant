#include "Scene.hpp"
#include "../defines.hpp"

Scene::Scene() : camera(), gameObjects(), objectTree(), boundsWidth(0), window(nullptr)
{

}

Scene::~Scene()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
}

void Scene::UpdateScene()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
	camera.Update();
}

void Scene::AddObject(GameObject* object)
{
	gameObjects.push_back(object);
	objectTree.Insert(object, object->transform.position);
}
