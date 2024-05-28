#include <iostream>
#include "defines.hpp"
#include "engine/Engine.hpp"

#include "data_structures/include.hpp"


int main()
{
	Engine* e = Engine::GetInstance();

	dde

	delete e;
	// system("pause");

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
