#include "../glad/gl.h"
#include "SceneFactory.hpp"
#include INCL_SCENE_COMPONENTS
#include INCL_COMPONENTS
#include INCL_GLFW

Scene* SceneFactory::FloatingShpehere()
{
	Engine* e = Engine::GetInstance();

	Scene* scene = new Scene();

	SphereCollider* c = new SphereCollider(1);
	GameObject* tmp = new GameObject();
	tmp->transform.velocity.vector = VECTOR3(0.1);
	tmp->components.AddComponent(c);
	scene->AddObject(tmp);
	delete c;

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::RungeKutta4;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent(mover);
	delete mover;

    return scene;
}

Scene* SceneFactory::SpheresCollide()
{
	Engine* e = Engine::GetInstance();

	Scene* scene = new Scene();
	scene->objectTree = new OcTree<GameObject*>(NULLVECTOR, 3, 8);

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::RungeKutta4;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent(mover);
	delete mover;

	ObjectCollider* collider = new ObjectCollider();
	scene->components.AddComponent(collider);
	delete collider;

	SphereCollider* c = new SphereCollider(1);

	GameObject* tmp = new GameObject();
	tmp->transform.velocity.vector = VECTOR3(0, 0.1, 0);
	tmp->transform.position.vector = VECTOR3(0, -5, 0);
	tmp->components.AddComponent(c);
	scene->AddObject(tmp);

	tmp = new GameObject();
	tmp->transform.velocity.vector = VECTOR3(0, -0.1, 0);
	tmp->transform.position.vector = VECTOR3(0, 5, 0);
	tmp->components.AddComponent(c);
	scene->AddObject(tmp);

	delete c;

	return scene;
}

Scene* SceneFactory::TonsOfSpheres()
{
	Engine* e = Engine::GetInstance();
	srand(1);
	Scene* scene = new Scene();
	GameObject* tmp = nullptr;
	SphereCollider* c = new SphereCollider();
	for (size_t i = 0; i < 2500; i++)
	{
		tmp = new GameObject();
		tmp->transform.velocity.vector = VECTOR3(rand() - RAND_MAX / 2, rand() - RAND_MAX / 2, rand() - RAND_MAX / 2);
		tmp->transform.position.vector = VECTOR3(0, 0, 0);
		tmp->components.AddComponent(c);
		scene->AddObject(tmp);
	}
	delete c;
	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::RungeKutta4;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent(mover);
	delete mover;
	return scene;
}

Scene* SceneFactory::CameraTest()
{
	Scene* s = new Scene();
	Engine::GetInstance()->SetActiveScene(s);
	s->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Default window");

	Camera* camera = new Camera();
	camera->transform.position.vector = VECTOR3(0, 0, -10);
	camera->InitComponents();
	GLuint shader = camera->CompileShader(GL_VERTEX_SHADER, Engine::shader_text.c_str());
	camera->AttachShader(shader);
	shader = camera->CompileShader(GL_FRAGMENT_SHADER, Engine::fragment_shader_text.c_str());
	camera->AttachShader(shader);
	camera->LinkProgram();
	s->camera = camera;

	GameObject* cube = new GameObject();
	TriangleRenderer square;
	cube->components.AddComponent(&square);
	s->AddObject(cube);
	gladInstallGLDebug();
	return s;
}
