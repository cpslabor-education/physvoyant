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
	Engine::InitGLFW();
	e->clock.SetPhysicsTimeStep(TO_TIME_UNIT(0.1));
	e->SetFPS(0);

	e->SetActiveScene(SceneFactory::CameraTest());

	bool close = false;

	while (!close)
	{
		close = e->Run();
		glfwPollEvents();
		e->Time(60);
	}

	Engine::StopGLFW();
	delete e->GetActiveScene();
	delete e;
	std::cout << Engine::MemCheck();
	return 0;












	// Trash here, don't look >:(

	//GameObject* dummy = new GameObject();
	//IComponent* cmp = new SphereCollider();
	//dummy->components.AddComponent<SphereCollider*>(cmp);
	//delete cmp;
	//dummy->components.UpdateAll();
	//OcTree<GameObject*>* tree = new OcTree<GameObject*>(NULLVECTOR, 2, 16);
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


/*
//========================================================================
// OpenGL triangle example
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//! [code]

#include "defines.hpp"

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#define GLM_FORCE_QUAT_DATA_WXYZ
#include INCL_QUATERNION

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void mat4x4_ortho(glm::mat4x4& M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f / (r - l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f / (t - b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f / (f - n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;

	M[3][0] = -(r + l) / (r - l);
	M[3][1] = -(t + b) / (t - b);
	M[3][2] = -(f + n) / (f - n);
	M[3][3] = 1.f;
}
void mat4x4_rotate_Z(glm::mat4x4& Q, glm::mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	glm::mat4x4 R = {
		{   c,   s, 0.f, 0.f},
		{  -s,   c, 0.f, 0.f},
		{ 0.f, 0.f, 1.f, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	Q = M * R;
}

typedef struct Vertex
{
	glm::vec2 pos;
	glm::vec3 col;
} Vertex;

static const Vertex vertices[3] =
{
	{ { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
	{ {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
	{ {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
};

static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	// NOTE: OpenGL error checks have been omitted for brevity

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	const GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	const GLint mvp_location = glGetUniformLocation(program, "MVP");
	const GLint vpos_location = glGetAttribLocation(program, "vPos");
	const GLint vcol_location = glGetAttribLocation(program, "vCol");

	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), (void*)offsetof(Vertex, col));

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4x4 m, p, mvp;
		m = glm::identity<glm::mat4x4>();
		p = glm::identity<glm::mat4x4>();
		mvp = glm::identity<glm::mat4x4>();
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

		mvp = p * m;

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
		glBindVertexArray(vertex_array);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//! [code]

*/