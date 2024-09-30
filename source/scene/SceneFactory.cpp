#include "SceneFactory.hpp"
#include INCL_SCENE_COMPONENTS
#include INCL_COMPONENTS

Scene* SceneFactory::FloatingShpehere()
{
	Engine* e = Engine::GetInstance();

	Scene* scene = new Scene();

	SphereCollider* c = new SphereCollider(1);
	GameObject* tmp = new GameObject();
	tmp->transform.velocity = VECTOR3(0.1);
	tmp->components.AddComponent<SphereCollider*>(c);
	scene->AddObject(tmp);
	delete c;

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::RungeKutta4;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent<ObjectMover*>(mover);
	delete mover;

    return scene;
}

Scene* SceneFactory::SpheresCollide()
{
	Engine* e = Engine::GetInstance();

	Scene* scene = new Scene();
	scene->objectTree = new OctTree<GameObject*>(VECTOR3(0), 3, 8);

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::RungeKutta4;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent<ObjectMover*>(mover);
	delete mover;

	ObjectCollider* collider = new ObjectCollider();
	scene->components.AddComponent<ObjectCollider*>(collider);
	delete collider;

	SphereCollider* c = new SphereCollider(1);

	GameObject* tmp = new GameObject();
	tmp->transform.velocity = VECTOR3(0, 0.1, 0);
	tmp->transform.position = VECTOR3(0, -5, 0);
	tmp->components.AddComponent<SphereCollider*>(c);
	scene->AddObject(tmp);

	tmp = new GameObject();
	tmp->transform.velocity = VECTOR3(0, -0.1, 0);
	tmp->transform.position = VECTOR3(0, 5, 0);
	tmp->components.AddComponent<SphereCollider*>(c);
	scene->AddObject(tmp);

	delete c;

	return scene;
}
