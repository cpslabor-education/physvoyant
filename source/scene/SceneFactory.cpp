#include "../glad/gl.h"
#include "SceneFactory.hpp"
#include INCL_SCENE_COMPONENTS
#include INCL_COMPONENTS
#include INCL_GLFW

Scene* SceneFactory::SceneTester()
{
	std::string tests[] =
	{
		"Cubes Collide",
		"Three Bodies",
		"Orbiting Planet",
		"NBody Problem",
		"NBody Optimized"
	};
	Scene* (*functions[])() =
	{
		CubesCollide,
		ThreeBodies,
		OrbitingPlanet,
		NBodyProblem,
		NBodyOptimized
	};

	std::cout << "=============================================" << std::endl;
	std::cout << "Available tests:" << std::endl;
	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		std::cout << i << ": " << tests[i] << std::endl;
	}
	int index = -1;

	std::cout << "Select index (-1 to exit): ";
	std::cin >> index;
	Scene* testScene = nullptr;
	if (index >= 0 && index < sizeof(tests) / sizeof(tests[0]))
	{
		testScene = (*functions[index])();
	}
	return testScene;
}

Scene* SceneFactory::CubesCollide()
{
	Engine* e = Engine::GetInstance();

	Scene* scene = new Scene();
	Engine::GetInstance()->SetActiveScene(scene);
	scene->objectTree = new OcTree<GameObject*>(NULLVECTOR, 3, 8);
	scene->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Cubes Collide");

	Camera* camera = new Camera();
	camera->transform.position.vector = VECTOR3(0, 3, 0);
	camera->transform.position.SetRotation(glm::rotate(glm::identity<QUATERNION>(), -glm::pi<realStandard_t>() / 2.0, VECTOR3(1, 0, 0)));
	camera->InitComponents();
	GLuint shader = camera->CompileShader(GL_VERTEX_SHADER, Engine::shader_text.c_str());
	camera->AttachShader(shader);
	shader = camera->CompileShader(GL_FRAGMENT_SHADER, Engine::fragment_shader_text.c_str());
	camera->AttachShader(shader);
	camera->LinkProgram();
	scene->camera = camera;


	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::SemiImplicitEuler;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent(mover);
	delete mover;

	ObjectCollider* collider = new ObjectCollider();
	scene->components.AddComponent(collider);
	delete collider;

	SquareCollider* c = new SquareCollider();
	c->SetHalfSides(VECTOR3(1));

	SquareRenderer square;
	square.halfSides = VECTOR3(1);
	GameObject* tmp = new GameObject();
	tmp->transform.velocity.vector = VECTOR3(0.5, 0, 0);
	tmp->transform.position.vector = VECTOR3(-3, 0, 0);
	tmp->components.AddComponent(c);
	tmp->components.AddComponent(&square);
	scene->AddObject(tmp);

	tmp = new GameObject();
	tmp->transform.velocity.vector = VECTOR3(-0.5, 0, 0);
	tmp->transform.position.vector = VECTOR3(3, 0, 0);
	tmp->components.AddComponent(c);
	tmp->components.AddComponent(&square);
	scene->AddObject(tmp);

	delete c;

	return scene;
}

Scene* SceneFactory::CameraTest()
{
	Scene* s = new Scene();
	Engine::GetInstance()->SetActiveScene(s);
	s->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Triangle test");

	Camera* camera = new Camera();
	camera->ortho = true;
	camera->transform.position.vector = VECTOR3(0, 0, -5);
	camera->transform.position.SetRotation(glm::rotate(glm::identity<QUATERNION>(), -0.1, VECTOR3(1, 0, 0)));
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

Scene* SceneFactory::ThreeBodies()
{
	Scene* s = new Scene();
	Engine::GetInstance()->SetActiveScene(s);
	s->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Three bodies");

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::Leapfrog;
	mover->leapfrogSteps = 2;
	s->components.AddComponent(mover);

	Camera* camera = new Camera();
	camera->transform.position.vector = VECTOR3(0, 0, 5);
	camera->transform.position.SetRotation(glm::rotate(glm::identity<QUATERNION>(), -glm::pi<realStandard_t>() - 0.1, VECTOR3(1, 0, 0)));
	camera->InitComponents();
	GLuint shader = camera->CompileShader(GL_VERTEX_SHADER, Engine::shader_text.c_str());
	camera->AttachShader(shader);
	shader = camera->CompileShader(GL_FRAGMENT_SHADER, Engine::fragment_shader_text.c_str());
	camera->AttachShader(shader);
	camera->LinkProgram();
	s->camera = camera;

	GravityComponent gravity;
	SphereRenderer sphere;
	// sphere.halfSides = VECTOR3(1);


	// The "sun"
	GameObject* body = new GameObject();
	gravity.mass = 1e10;
	sphere.radius = 1.0;
	body->components.AddComponent(&gravity);
	body->components.AddComponent(&sphere);
	s->AddObject(body);

	// Planet
	body = new GameObject();
	gravity.mass = 1e5;
	sphere.radius = 0.5;
	// sphere.halfSides = VECTOR3(0.5);
	body->transform.velocity.vector = VECTOR3(-0.8, 1, 0);
	body->transform.position.vector = VECTOR3(3, 1.5, 0);
	body->components.AddComponent(&gravity);
	body->components.AddComponent(&sphere);
	s->AddObject(body);

	// Asteroid
	body = new GameObject();
	gravity.mass = 1e3;
	sphere.radius = 0.3;
	// sphere.halfSides = VECTOR3(0.3);
	body->transform.velocity.vector = VECTOR3(1.4, 0.7, 0);
	body->transform.position.vector = VECTOR3(-2, -2.5, 0);
	body->components.AddComponent(&gravity);
	body->components.AddComponent(&sphere);
	s->AddObject(body);

	return s;
}

Scene* SceneFactory::OrbitingPlanet()
{
	Scene* s = new Scene();
	Engine::GetInstance()->SetActiveScene(s);
	s->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Orbiting planet");

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::Leapfrog;
	mover->leapfrogSteps = 2;
	s->components.AddComponent(mover);

	Camera* camera = new Camera();
	camera->transform.position.vector = VECTOR3(0, 0, 2);
	camera->transform.position.SetRotation(glm::rotate(glm::identity<QUATERNION>(), -glm::pi<realStandard_t>() - 0.1, VECTOR3(1, 0, 0)));
	camera->InitComponents();
	GLuint shader = camera->CompileShader(GL_VERTEX_SHADER, Engine::shader_text.c_str());
	camera->AttachShader(shader);
	shader = camera->CompileShader(GL_FRAGMENT_SHADER, Engine::fragment_shader_text.c_str());
	camera->AttachShader(shader);
	camera->LinkProgram();
	s->camera = camera;

	GravityComponent gravity;
	SphereRenderer sphere;
	// sphere.halfSides = VECTOR3(1);


	// The "sun"
	GameObject* body = new GameObject();
	gravity.mass = 1e10;
	body->components.AddComponent(&gravity);
	body->components.AddComponent(&sphere);
	s->AddObject(body);

	sphere.radius = 0.5;
	// Planet
	body = new GameObject();
	gravity.mass = 1e5;
	// sphere.halfSides = VECTOR3(0.5);
	body->transform.position.vector = VECTOR3(2, 0, 0);
	body->transform.velocity.vector = VECTOR3(0, 0.8, 0);
	body->components.AddComponent(&gravity);
	body->components.AddComponent(&sphere);
	s->AddObject(body);

	return s;
}

Scene* SceneFactory::NBodyProblem()
{
	std::cout << "Number of planets: ";
	uintStandard_t N = 0;
	std::cin >> N;
	Scene* s = new Scene();
	Engine::GetInstance()->SetActiveScene(s);
	s->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "N body problem");

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::Leapfrog;
	mover->leapfrogSteps = 2;
	s->components.AddComponent(mover);

	Camera* camera = new Camera();
	camera->transform.position.vector = VECTOR3(0, 0, 20);
	camera->transform.position.SetRotation(glm::rotate(glm::identity<QUATERNION>(), -glm::pi<realStandard_t>() - 0.1, VECTOR3(1, 0, 0)));
	camera->InitComponents();
	GLuint shader = camera->CompileShader(GL_VERTEX_SHADER, Engine::shader_text.c_str());
	camera->AttachShader(shader);
	shader = camera->CompileShader(GL_FRAGMENT_SHADER, Engine::fragment_shader_text.c_str());
	camera->AttachShader(shader);
	camera->LinkProgram();
	s->camera = camera;

	GravityComponent gravity;
	SphereRenderer sphere;

	GameObject* body = nullptr;

	srand(2);

	for (size_t i = 0; i < N; i++)
	{
		body = new GameObject();
		realStandard_t ratio = 1.0 * rand() / RAND_MAX;
		gravity.mass = 1e6 + glm::pow(10, ratio * 8);
		sphere.radius = 0.6 + ratio;
		body->transform.position.vector = VECTOR3(rand() % 32 - 16, rand() % 32 - 16, 0);
		body->transform.velocity.vector = VECTOR3((rand() % 4 - 2) * 0.2, (rand() % 4 - 2) * 0.2, 0);
		body->components.AddComponent(&gravity);
		body->components.AddComponent(&sphere);
		s->AddObject(body);
	}
	return s;
}

Scene* SceneFactory::NBodyOptimized()
{
	std::cout << "Number of planets: ";
	uintStandard_t N = 0;
	std::cin >> N;
	Scene* s = new Scene();
	Engine::GetInstance()->SetActiveScene(s);
	s->SetupWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "N body problem");

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::Leapfrog;
	mover->leapfrogSteps = 2;
	s->components.AddComponent(mover);

	Camera* camera = new Camera();
	camera->transform.position.vector = VECTOR3(0, 0, 20);
	camera->transform.position.SetRotation(glm::rotate(glm::identity<QUATERNION>(), -glm::pi<realStandard_t>() - 0.1, VECTOR3(1, 0, 0)));
	camera->InitComponents();
	GLuint shader = camera->CompileShader(GL_VERTEX_SHADER, Engine::shader_text.c_str());
	camera->AttachShader(shader);
	shader = camera->CompileShader(GL_FRAGMENT_SHADER, Engine::fragment_shader_text.c_str());
	camera->AttachShader(shader);
	camera->LinkProgram();
	s->camera = camera;

	GravityComponent gravity;
	gravity.pull = false;
	SphereRenderer sphere;

	GameObject* body = nullptr;

	srand(2);

	for (size_t i = 0; i < N; i++)
	{
		body = new GameObject();
		realStandard_t ratio = 1.0 * rand() / RAND_MAX;
		gravity.mass = 1e6 + glm::pow(10, ratio * 8);
		sphere.radius = 0.6 + ratio;
		body->transform.position.vector = VECTOR3(rand() % 32 - 16, rand() % 32 - 16, 0);
		body->transform.velocity.vector = VECTOR3((rand() % 4 - 2) * 0.2, (rand() % 4 - 2) * 0.2, 0);
		body->components.AddComponent(&gravity);
		body->components.AddComponent(&sphere);
		s->AddObject(body);
	}
	gravity.pull = true;
	body = new GameObject();
	gravity.mass = 1e14;
	sphere.radius = 1.8;
	body->transform.position.vector = VECTOR3(0);
	body->transform.velocity.vector = VECTOR3(0);
	body->components.AddComponent(&gravity);
	body->components.AddComponent(&sphere);
	s->AddObject(body);
	return s;
}
