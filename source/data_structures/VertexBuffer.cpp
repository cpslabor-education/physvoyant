#include "../glad/gl.h"
#include "VertexBuffer.hpp"
#include INCL_ENGINE

VertexBuffer::VertexBuffer() : verticies(), VAO(0), VBO(0)
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Setup()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Define the vertex attributes (assuming 2D vertices with x, y)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	GLuint program = Engine::GetInstance()->GetActiveScene()->camera->GetProgram();

	const GLint positionLocation = glGetAttribLocation(program, "position");
	const GLint colorLocation = glGetAttribLocation(program, "color");

	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::SetSize()
{
	BindVAO();
	BindVBO();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint VertexBuffer::CreateVertexBuffer()
{
	glGenBuffers(1, &VBO);
	return VBO;
}

GLuint VertexBuffer::CreateVertexArray()
{
	glGenVertexArrays(1, &VAO);
	return VBO;
}

void VertexBuffer::PassData()
{
	BindVAO();
	BindVBO();
	glBufferData(GL_ARRAY_BUFFER, GetBufferSize(), verticies.data(), GL_STATIC_DRAW);
}

void VertexBuffer::DeleteBuffers()
{
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}

void VertexBuffer::BindVAO()
{
	glBindVertexArray(VAO);
}

void VertexBuffer::BindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::AddVertex(Vertex& vertex)
{
	verticies.push_back(std::move(vertex));
}

std::vector<Vertex>* VertexBuffer::GetBuffer()
{
	return &verticies;
}

size_t VertexBuffer::GetBufferSize()
{
	return verticies.size() * sizeof(Vertex);
}
