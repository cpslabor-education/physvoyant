#include <iostream>
#include "defines.hpp"
#include "engine/Engine.hpp"

#include "data_structures/include_data_structures.hpp"
#include "game_objects/include_objects.hpp"
#include INCL_GLM
#define GLM_FORCE_QUAT_DATA_WXYZ
#define GLM_ENABLE_EXPERIMENTAL
#include INCL_QUATERNION
#include INCL_QUATERNION_EXTENSIONS
#include INCL_GLFW
#include INCL_COMPONENTS

void Foo(int asd)
{

}

int main()
{
	Engine* e = Engine::GetInstance();
	Scene sample;

	GameObject* sphere1 = new GameObject();
	sphere1->AddComponent((SphereCollider)(1, 0));
	sphere1->transform.SetPosition(0, 0, 0);

	GameObject* sphere2 = new GameObject();
	sphere1->AddComponent((SphereCollider)(1, 0));
	sphere1->transform.SetPosition(3, 0, 0);

	sample.AddObject(sphere1);
	sample.AddObject(sphere2);

	sphere1->transform.ApplyForce(VECTOR3(1, 0, 0));

	std::cout << "asd";

	VECTOR3 v1(1, 2, 3);
	VECTOR3 v2(10, 0, 0);

	QUATERNION q1(0, 1, 2, 3);
	QUATERNION q2(0, 1, 0, 0);

	q1 += q2;

	v1 += v2;

	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;


	glm::mat4 MyMatrix = glm::mat4();
	glm::quat myQuat;

	myQuat = glm::quat(0.707107, 0.707107, 0.00, 0.000);
	glm::mat4 RotationMatrix = glm::toMat4(myQuat);

	glm::highp_f64vec3 asd;
	double val = 0.5;
	unsigned long long val2 = *(unsigned long long*) & val;


	GameObject* o = new GameObject();
	o->GetComponentsOfType<Engine>();

	Engine::WriteInfo(e);
	delete e;
	// system("pause");
#if DEBUG_LEVEL >= 2
	Engine::WriteInfo(_CrtDumpMemoryLeaks());
#endif
	return 0;

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
