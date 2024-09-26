#include <iostream>
#include "defines.hpp"
#include "engine/Engine.hpp"

//#include "data_structures/include_data_structures.hpp"
//#include "game_objects/include_objects.hpp"
//#include INCL_GLM
//#define GLM_FORCE_QUAT_DATA_WXYZ
//#define GLM_ENABLE_EXPERIMENTAL
//#include INCL_QUATERNION
//#include INCL_QUATERNION_EXTENSIONS
//#include INCL_GEOMETRY
//#include INCL_MATH
////#include <glm/gtx/matrix_interpolation.hpp>
//#include INCL_GLFW
#include INCL_COMPONENTS
#include INCL_SCENE_COMPONENTS
////#include "geometry/MovementSolver.hpp"
//#include <glm/gtx/compatibility.hpp>


int main()
{
	Engine* e = Engine::GetInstance();

	Scene* scene = new Scene();
	scene->objectTree = new OctTree<GameObject*>(VECTOR3(0), 5, 8);

	GameObject* tmp = new GameObject();
	tmp->transform.velocity = VECTOR3(1);
	scene->AddObject(tmp);

	ObjectMover* mover = new ObjectMover();
	mover->solverType = MovementSolver::Solvers::Leapfrog;
	mover->leapfrogSteps = 2;
	scene->components.AddComponent<ObjectMover*>(mover);
	delete mover;

	e->SetActiveScene(scene);

	for (int i = 0; i < 10000; i++)
	{
		e->Run();
		_sleep(100); // imaginary load
		realStandard_t time = TO_SECOND(e->clock.DeltaTime());
		e->Time(10);
		e->WriteInfo(time);
	}
















	// Trash here, don't look >:(

	//GameObject* dummy = new GameObject();
	//IComponent* cmp = new SphereCollider();
	//dummy->components.AddComponent<SphereCollider*>(cmp);
	//delete cmp;
	//dummy->components.UpdateAll();
	//OctTree<GameObject*>* tree = new OctTree<GameObject*>(VECTOR3(0), 2, 16);
	//tree->WithinSameSquare(VECTOR3(-15.9), VECTOR3(-16));
	//delete container[0];
	//tree->Insert(new GameObject(), VECTOR3(1, 1, 1));
	//tree->Insert(new GameObject(), VECTOR3(1, 1, 2));
	//tree->Insert(new GameObject(), VECTOR3(1, 1, 3));
	//tree->Insert(new GameObject(), VECTOR3(17, 17, 17));
	//tree->Insert(new GameObject(), VECTOR3(17, 17, 17));
	//tree->GetNeighbours(VECTOR3(1, 2, 3));

	//std::list<GameObject*>** tmp;
	//std::list<GameObject*>* tmp2;

	//uintStandard_t index = tree->Find(VECTOR3(17, 17, 18), &tmp);
	//tree->Insert(new GameObject(), VECTOR3(17, 17, 17));
	//tmp2 = tree->GetList(0);
	//dummy->transform.position = VECTOR3(1, 1, 1);

	//tree->MoveItem(index, (*tmp)[0], tree->Find(VECTOR3(-1, -1, -1)));
	//tree->MoveItem(index, (*tmp)[1], tree->Find(VECTOR3(-1, -1, -1)));

	//for (size_t i = 0; i < 32; i++)
	//{
	//	for (size_t j = 0; j < 32; j++)
	//	{
	//		for (size_t k = 0; k < 32; k++)
	//		{
	//			dummy = new GameObject();
	//			dummy->transform.position = VECTOR3(i, j, k);
	//			tree->Insert(dummy, dummy->transform.position);
	//		}
	//	}
	//}

	//tree->Insert(dummy, dummy->transform.position);

	//std::vector<GameObject*>* vec = nullptr;
	//index = tree->Find(VECTOR3(0, 1, 2), &vec);
	//tree->MoveItem(index, (*vec)[0], tree->Find(VECTOR3(-1, -1, -1)));
	//tree->Insert(new GameObject(), VECTOR3(-2, 5, -22));
	//std::list<GameObject*>* res[27];
	//tree->GetNeighbours(VECTOR3(-2, 5, -22), res);
	//delete tree;
	//delete dummy;
	//std::cout << _CrtDumpMemoryLeaks();
	//return 0;
	////tree->Find(VECTOR3(0, 0, 0));
	////tree->Find(VECTOR3(-321, 661, -301));
	////tree->Find(VECTOR3(-30021, 60061, -30001));
	//Engine* e = Engine::GetInstance();
	//e->clock.SetPhysicsTimeStep(1);
	//timeValue_t minMax[2]{ UINT_FAST64_MAX, 0 };
	//for (size_t i = 0; i < 100000; i++)
	//{
	//	e->clock.Update();
	//	timeValue_t curr = e->clock.DeltaTime();
	//	minMax[0] = glm::min(minMax[0], curr);
	//	minMax[1] = glm::max(minMax[1], curr);
	//}
	//e->WriteInfo(minMax[0]);
	//e->WriteInfo(minMax[1]);
	//e->WriteInfo(TO_SECOND(minMax[0]));
	//e->WriteInfo(TO_SECOND(minMax[1]));
	//delete e;
	//Scene sample;

	//GameObject* sphere1 = new GameObject();
	//sphere1->AddComponent((SphereCollider)(1, 0));
	//sphere1->transform.SetPosition(0, 0, 0);

	//GameObject* sphere2 = new GameObject();
	//sphere1->AddComponent((SphereCollider)(1, 0));
	//sphere1->transform.SetPosition(3, 0, 0);

	//sample.AddObject(sphere1);
	//sample.AddObject(sphere2);

	//sphere1->transform.ApplyForce(VECTOR3(1, 0, 0));
	//glm::abs(3);
	//glm::length(VECTOR3(3, 4, 5));
	//glm::dvec3 vector(100, 10, 5);
	//glm::dvec3 vector2(0, 0, 0);
	//glm::dvec3 result = CubicInterpolate(vector, vector2, 0.2);

	//QUATERNION quat(1, 1, 2, 32);

	//vector = glm::normalize(quat) * vector;
	//result = glm::lerp(vector, vector2, 0.2);
	//glm::lerp(0.0, 3.0, 0.2);

	//int l = vector.length();
	//glm::faceforward(vector, vector, vector);



	//glm::interpolate(VECTOR3(3,2,3), VECTOR3(3,2,2), 0.3);

	//std::cout << "asd";

	//VECTOR3 v1(1, 2, 3);
	//VECTOR3 v2(10, 0, 0);

	//QUATERNION q1(0, 1, 2, 3);
	//QUATERNION q2(0, 1, 0, 0);

	//q1 += q2;

	//v1 += v2;

	//v2[0] = 1;
	//v2[1] = 2;
	//v2[2] = 3;


	//glm::mat4 MyMatrix = glm::mat4();
	//glm::quat myQuat;

	//myQuat = glm::quat(0.707107, 0.707107, 0.00, 0.000);
	//glm::mat4 RotationMatrix = glm::toMat4(myQuat);

	//glm::highp_f64vec3 asd;
	//realStandard_t val = 0.5;
	//unsigned long long val2 = *(unsigned long long*) & val;


	//GameObject* o = new GameObject();
	//o->GetComponentsOfType<Engine>();

	//Engine::WriteInfo(e);
	//delete e;
	//// system("pause");
//#if DEBUG_LEVEL >= 2
//	Engine::WriteInfo(_CrtDumpMemoryLeaks());
//#endif
//	return 0;

	//glfwInit();
	//GLFWwindow* window;
	//window = glfwCreateWindow(640, 480, a, NULL, NULL);

	//glfwMakeContextCurrent(window);
	//glEnable(GL_DEPTH_TEST);
	//int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	//glViewport(0, 0, width, height);
	//glfwSwapInterval(1);
	//int counter = 0;
	//while (!glfwWindowShouldClose(window))
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glBegin(GL_LINE_STRIP);

	//	glVertex2f(0, 0);
	//	glVertex2f(cos(counter / 36.0), sin(counter / 36.0));
	//	++counter;
	//	glEnd();

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//	continue;
	//	glOrtho(0, width, height, 0, 0, 1);
	//	glfwSwapBuffers(window);
	//	// DrawTest(window);
	//	glfwWaitEvents();
	//}

	//std::cout << "Hello world";
	//glfwDestroyWindow(window);
	//// delete window;
	//glfwTerminate();
}
