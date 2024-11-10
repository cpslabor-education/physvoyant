#include "../glad/gl.h"
#include "VertexBuffer.hpp"
#include INCL_ENGINE

VertexBuffer::VertexBuffer() : verticies(), VAO(0), VBO(0), IBO(0)
{
}

VertexBuffer::~VertexBuffer()
{
	DeleteBuffers();
}

void VertexBuffer::Setup()
{
	CreateVertexArray();
	CreateVertexBuffer();
	CreateIndexBuffer();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	GLuint program = Engine::GetInstance()->GetActiveScene()->camera->GetProgram();

	const GLint positionLocation = glGetAttribLocation(program, "position");
	const GLint colorLocation = glGetAttribLocation(program, "color");
	const GLint normalLocation = glGetAttribLocation(program, "normal");

	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(normalLocation);
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint VertexBuffer::CreateVertexBuffer()
{
	if (VBO == 0)
	{
		glGenBuffers(1, &VBO);
	}
	return VBO;
}

GLuint VertexBuffer::CreateVertexArray()
{
	if (VAO == 0)
	{
		glGenVertexArrays(1, &VAO);
	}
	return VAO;
}

GLuint VertexBuffer::CreateIndexBuffer()
{
	if (IBO == 0)
	{
		glGenBuffers(1, &IBO);
	}
	return IBO;
}

void VertexBuffer::PassData()
{
	BindVAO();
	BindVBO();
	glBufferData(GL_ARRAY_BUFFER, GetVertexBufferSize(), verticies.data(), GL_STATIC_DRAW);

	if (indices.size() != 0)
	{
		BindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}
}

void VertexBuffer::DeleteBuffers()
{
	verticies.clear();
	indices.clear();
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
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
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

void VertexBuffer::BindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

void VertexBuffer::BindAll()
{
	BindVAO();
	BindVBO();
	BindIBO();
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

size_t VertexBuffer::GetVertexBufferSize()
{
	return verticies.size() * sizeof(Vertex);
}

size_t VertexBuffer::GetIndexBufferSize()
{
	return indices.size() * sizeof(GLuint);
}
