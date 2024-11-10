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
}

TriangleRenderer::~TriangleRenderer()
{
}

void TriangleRenderer::Draw()
{
	buffer.PassData();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	buffer.Unbind();
}

void* TriangleRenderer::Execute(GameObject* caller, void* params)
{
	QUATERNION& rot = caller->transform.position.GetRotation();

	rot = glm::rotate(glm::identity<QUATERNION>(), 0.1, VECTOR3(0, 0, 1));

	caller->transform.position.SetRotation(rot);

	for (size_t i = 0; i < buffer.verticies.size(); i++)
	{
		VECTOR3 position = buffer.verticies[i].position;
		position = position * caller->transform.position.GetRotation();
		buffer.verticies[i].position = position;
	}

	return nullptr;
}

IComponent* TriangleRenderer::Clone(void* params) const
{
	return new TriangleRenderer(*this);
}


VERTEX_VECTOR3 SphereRenderer::GetPointOnCircle(uintStandard_t i, uintStandard_t N)
{
	VERTEX_VECTOR3 circlePoint = VERTEX_VECTOR3(0);
	circlePoint.x += glm::cos(1.0 * i / N * glm::pi<realStandard_t>() * 2.0) * radius;
	circlePoint.y += glm::sin(1.0 * i / N * glm::pi<realStandard_t>() * 2.0) * radius;
	return circlePoint;
}

void SphereRenderer::MakeCircle(PosRot* offset, uintStandard_t N)
{
	PosRot actualOffset;
	if (offset != nullptr)
	{
		actualOffset = *offset;
	}
	Vertex v;
	v.position = actualOffset.vector;
	v.color = VERTEX_VECTOR3(1);
	Camera* camera = Engine::GetInstance()->GetActiveScene()->camera;
	v.normal = camera->transform.position.vector - actualOffset.vector;

	if (buffer.verticies.empty())
	{
		buffer.AddVertex(v);
	}
	else
	{
		buffer.verticies[0] = v;
	}
	VECTOR3 cameraDirection = glm::normalize(v.normal);
	glm::mat4 rotationMatrix = glm::identity<glm::mat4>();

	if (cameraDirection != Engine::upVector)
	{
		realStandard_t dotProduct = glm::dot(Engine::upVector, cameraDirection);
		realStandard_t angle = -glm::acos(dotProduct);
		
		VECTOR3 rotationAxis = glm::normalize(glm::cross(Engine::upVector, cameraDirection));

		rotationMatrix = glm::rotate(glm::mat<4, 4, realStandard_t>(1.0f), angle, rotationAxis);
	}

	for (size_t i = 1; i < N + 1; i++)
	{
		v.position = glm::vec4(GetPointOnCircle(i, N), 0.0f) * rotationMatrix;
		v.position += actualOffset.vector;
		if (buffer.verticies.size() == i)
		{
			buffer.AddVertex(v);
		}
		else
		{
			buffer.verticies[i] = v;
		}
	}

	if (buffer.indices.empty())
	{
		for (uintStandard_t i = 0; i < N; ++i)
		{
			buffer.indices.push_back(0);
			buffer.indices.push_back(i);
			buffer.indices.push_back(i + 1);
		}
		buffer.indices.push_back(0);
		buffer.indices.push_back(N);
		buffer.indices.push_back(1);
	}
}

SphereRenderer::SphereRenderer() : radius(1)
{

}

SphereRenderer::SphereRenderer(const SphereRenderer& other) : radius(other.radius)
{
	buffer.CreateVertexBuffer();
	buffer.CreateVertexArray();
	buffer.CreateIndexBuffer();
	buffer.Setup();

	MakeCircle();
}

void* SphereRenderer::Execute(GameObject* caller, void* params)
{
	MakeCircle(&caller->transform.position);
	return nullptr;
}

void SphereRenderer::Draw()
{
	buffer.PassData();

	glDrawElements(GL_TRIANGLES, buffer.indices.size(), GL_UNSIGNED_INT, nullptr);

	buffer.Unbind();
}

SquareRenderer::SquareRenderer() : buffer(), halfSides(1)
{

}

SquareRenderer::SquareRenderer(const SquareRenderer& other) : buffer(), halfSides(other.halfSides)
{
	buffer.CreateVertexBuffer();
	buffer.CreateVertexArray();
	buffer.CreateIndexBuffer();
	buffer.Setup();
	cornerArray_t corners = GetCorners();
	Vertex v;
	for (size_t i = 0; i < 1 << DIMENSIONS; i++)
	{
		switch (i % 4)
		{
			case 0:
				v.color = VERTEX_VECTOR3(1, 0, 0);
				break;
			case 1:
				v.color = VERTEX_VECTOR3(0, 1, 0);
				break;
			case 2:
				v.color = VERTEX_VECTOR3(0, 0, 1);
				break;
			case 3:
				v.color = VERTEX_VECTOR3(1, 1, 1);
				break;
			default:
				break;
		}
		v.position = corners[i];
		v.normal = v.position;
		buffer.AddVertex(v);
	}
	buffer.indices =
	{
		// Bottom face
		0, 2, 1,
		2, 3, 1,

		// Back face
		1, 5, 0,
		5, 4, 0,

		// Left face
		2, 0, 6,
		4, 6, 0,

		// Right face
		3, 7, 1,
		7, 5, 1,

		// Top face
		4, 5, 6,
		5, 7, 6,

		// Front face
		7, 3, 2,
		6, 7, 2
	};
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
	//QUATERNION& rot = caller->transform.position.GetRotation();

	//rot = glm::rotate(rot, 0.05, VECTOR3(1, 1, 1));

	//caller->transform.position.SetRotation(rot);

	cornerArray_t corners = GetCorners(&caller->transform.position);
	VERTEX_VECTOR3 center = caller->transform.position.vector;
	for (size_t i = 0; i < (size_t)1 << DIMENSIONS; i++)
	{
		VERTEX_VECTOR3 v = corners[i];
		buffer.verticies[i].position = v;
		buffer.verticies[i].normal = v - center;
	}
	return nullptr;
}

IComponent* SquareRenderer::Clone(void* params) const
{
	return new SquareRenderer(*this);
}

void SquareRenderer::Draw()
{
	buffer.PassData();

	glDrawElements(GL_TRIANGLES, buffer.indices.size(), GL_UNSIGNED_INT, nullptr);

	buffer.Unbind();
}
