#include "../glad/gl.h"
#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() : verticies(), bufferID(0)
{
}

VertexBuffer::~VertexBuffer()
{

}

unsigned int VertexBuffer::CreateBuffer()
{
	glGenBuffers(1, &bufferID);
	return bufferID;
}

void VertexBuffer::DeleteBuffer()
{
	if (bufferID != 0)
	{
		glDeleteBuffers(1, &bufferID);
	}
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::AddVertex(Vertex* vertex)
{
	verticies.push_back(*vertex);
}

void VertexBuffer::Clear()
{
	verticies.clear();
}

std::vector<Vertex>* VertexBuffer::GetBuffer()
{
	return &verticies;
}

unsigned int VertexBuffer::GetBufferID()
{
	return bufferID;
}
