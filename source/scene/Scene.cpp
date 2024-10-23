#include "Scene.hpp"
#include "../defines.hpp"

Scene::Scene() : camera(nullptr), gameObjects(), window(nullptr), objectTree(nullptr), components()
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
	delete camera;
	glfwDestroyWindow(window);
}

void Scene::UpdateScene()
{
	components.UpdateAll(this);
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
	camera->Execute(this);
}

void Scene::AddObject(GameObject* object)
{
	gameObjects.push_back(object);
	if (objectTree != nullptr)
	{
		objectTree->Insert(object, object->transform.position.vector);
	}
}

void Scene::SetupWindow(int width, int height, char* title)
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, Engine::KeyCallback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}

