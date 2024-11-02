#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "../defines.hpp"
#include INCL_GEOMETRY
#include INCL_GLM

#include INCL_GLFW
#include <vector>


class VertexBuffer
{
	GLuint VBO;
	GLuint VAO;
	GLuint IBO;
public:
	std::vector<Vertex> verticies;
	std::vector<GLuint> indices;

	VertexBuffer();
	~VertexBuffer();

	void Setup();

	GLuint CreateVertexBuffer();
	GLuint CreateVertexArray();
	GLuint CreateIndexBuffer();

	void PassData();
	void DeleteBuffers();
	void BindVAO();
	void BindVBO();
	void BindIBO();
	void BindAll();
	void Unbind();
	void AddVertex(Vertex& vertex);
	size_t GetVertexBufferSize();
	size_t GetIndexBufferSize();
};



#endif
