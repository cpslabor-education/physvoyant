#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "../defines.hpp"
#include INCL_GEOMETRY
#include INCL_GLM

#include INCL_GLFW
#include <vector>


class VertexBuffer
{
	std::vector<Vertex> verticies;
	GLuint VBO;
	GLuint VAO;
public:
	VertexBuffer();
	~VertexBuffer();

	void Setup();
	void SetSize();

	GLuint CreateVertexBuffer();
	GLuint CreateVertexArray();
	void PassData();
	void DeleteBuffers();
	void BindVAO();
	void BindVBO();
	void Unbind();
	void AddVertex(Vertex& vertex);
	std::vector<Vertex>* GetBuffer();
	size_t GetBufferSize();
};



#endif
