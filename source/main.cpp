#include <iostream>
#include <GLFW/glfw3.h>
#ifdef OPENGL_FOUND

#endif // OPENGL_FOUND


void DrawTest(GLFWwindow* window)
{
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(255.0f, 120.0f, 180.0f, 255.0f); //clear background screen to black

	//glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	//glLoadIdentity(); //Reset the drawing perspective
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20);
	glPushMatrix();
	glColor3f(1.0f, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.5, -1.5, -10.5);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.5, 1.5, -10.5);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.5, 1.5, -10.5);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.5, -1.5, -10.5);
	glEnd();
	glPopMatrix();

	glfwSwapBuffers(window);
	return;
}

int main()
{
	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Test page", NULL, NULL);

	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapInterval(1);
	int counter = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_LINE_STRIP);

		glVertex2f(0, 0);
		glVertex2f(cos(counter / 36.0), sin(counter / 36.0));
		++counter;
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
		continue;
		glOrtho(0, width, height, 0, 0, 1);
		glfwSwapBuffers(window);
		// DrawTest(window);
		glfwWaitEvents();
	}

	std::cout << "Hello world";
	glfwDestroyWindow(window);
	// delete window;
	glfwTerminate();
}
