#include "Scene.hpp"
#include "../defines.hpp"

Scene::Scene() : camera(nullptr), window(nullptr)
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
	camera->Update();
}

void Scene::AddObject(GameObject* object)
{
	gameObjects.push_back(object);
}
