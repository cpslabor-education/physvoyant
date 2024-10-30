#include "../glad/gl.h"
#include "Renderables.hpp"
#include INCL_GLM
#include <glm/gtc/matrix_transform.hpp>


TriangleRenderer::TriangleRenderer()
{

}

TriangleRenderer::TriangleRenderer(const TriangleRenderer& other)
{
	buffer.CreateVertexBuffer();
	buffer.CreateVertexArray();
	buffer.Setup();
	Vertex v;
	v.color = { 1, 0, 0 };
	v.position = { -0.6f, -0.4f , 0.1 };
	buffer.AddVertex(v);
	v.color = { 0, 1, 0 };
	v.position = { 0.6f, -0.4f , 0.1 };
	buffer.AddVertex(v);
	v.color = { 0, 0, 1 };
	v.position = { 0, 0.6f , 0.1 };
	buffer.AddVertex(v);
	buffer.SetSize();
}

TriangleRenderer::~TriangleRenderer()
{
}

void TriangleRenderer::Draw()
{
	buffer.BindVAO();
	buffer.BindVBO();

	glBufferData(GL_ARRAY_BUFFER, buffer.GetBufferSize(), buffer.GetBuffer()->data(), GL_STATIC_DRAW);
	//buffer.PassData();
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void* TriangleRenderer::Execute(GameObject* caller, void* params)
{
	realStandard_t angle = 0.05;
	glm::mat4 mat = glm::mat4(1.0f);
	glm::vec3 vector (0.0f, 0.0f, 1.0f);

	glm::mat4 rotationMatrix (1);
	{
		float const a = angle;
		float const c = cos(a);
		float const s = sin(a);

		glm::vec3 axis(normalize(UPVECTOR));
		glm::vec3 temp(((1.0f) - c) * axis);

		glm::mat4 Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		glm::mat4 Result;
		Result[0] = rotationMatrix[0] * Rotate[0][0] + rotationMatrix[1] * Rotate[0][1] + rotationMatrix[2] * Rotate[0][2];
		Result[1] = rotationMatrix[0] * Rotate[1][0] + rotationMatrix[1] * Rotate[1][1] + rotationMatrix[2] * Rotate[1][2];
		Result[2] = rotationMatrix[0] * Rotate[2][0] + rotationMatrix[1] * Rotate[2][1] + rotationMatrix[2] * Rotate[2][2];
		Result[3] = rotationMatrix[3];
		rotationMatrix = Result;
	}

	for (size_t i = 0; i < buffer.GetBuffer()->size(); i++)
	{
		VERTEX_VECTOR3& position = (*buffer.GetBuffer())[i].position;
		position = glm::vec4(position, 1.0f) * rotationMatrix;
	}

	return nullptr;
}

IComponent* TriangleRenderer::Clone(void* params) const
{
	return new TriangleRenderer(*this);
}



SphereRenderer::SphereRenderer() : positionPtr(nullptr)
{

}

void* SphereRenderer::Execute(GameObject* caller, void* params)
{
	this->positionPtr = &(caller->transform.position);
	return nullptr;
}

void SphereRenderer::Draw()
{
}

SquareRenderer::SquareRenderer() : buffer(), halfSides(1)
{

}

SquareRenderer::SquareRenderer(const SquareRenderer& other) : buffer(), halfSides(1)
{
	cornerArray_t corners = GetCorners();
	for (size_t i = 0; i < 1 << DIMENSIONS; i++)
	{
		Vertex v;
		v.color = VECTOR3(1, 0, 0);
		v.position = corners[i];
		buffer.AddVertex(v);
	}
}

SquareRenderer::cornerArray_t SquareRenderer::GetCorners(PosRot* center)
{
	SquareRenderer::cornerArray_t corners{ NULLVECTOR };
	PosRot offset = (center == nullptr) ? 0 : *center;
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		VECTOR3 corner(0.0);
		for (size_t j = 0; j < corner.length(); ++j)
		{
			corner[j] = ((i & ((size_t)1 << j)) ? halfSides[j] : -halfSides[j]);
		}
		corner = offset.GetRotation() * corner;
		corners[i] = offset.vector + corner;
	}
	return corners;
}

void* SquareRenderer::Execute(GameObject* caller, void* params)
{
	cornerArray_t corners = GetCorners();
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		(*(buffer.GetBuffer()))[i].position = corners[i];
	}
	return nullptr;
}

IComponent* SquareRenderer::Clone(void* params) const
{
	return new SquareRenderer(*this);
}

void SquareRenderer::Draw()
{
	//GLuint index = buffer.GetBufferID();

	//glBufferData(GL_ARRAY_BUFFER, buffer.GetBufferSize(), buffer.GetBuffer()->data(), GL_DYNAMIC_DRAW);

	//// 1282
	//glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), buffer.GetBuffer()->data());
	//glEnableVertexAttribArray(index);

	//glDrawArrays(GL_POINTS, 0, 8);
}
