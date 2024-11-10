#ifndef RENDERABLES
#define RENDERABLES

#include "RenderableBase.hpp"

class TriangleRenderer : public RenderableBase
{
	VertexBuffer buffer;
public:
	TriangleRenderer();
	TriangleRenderer(const TriangleRenderer& other);
	~TriangleRenderer();

	// Inherited via RenderableBase
	void Draw() override;

	void* Execute(GameObject* caller, void* params) override;

	IComponent* Clone(void* params) const override;

};

// Nope, Geodesic Dome can wait
class SphereRenderer : public RenderableBase
{
	VERTEX_VECTOR3 GetPointOnCircle(uintStandard_t i, uintStandard_t N);
	VertexBuffer buffer;
	void MakeCircle(PosRot* offset = nullptr, uintStandard_t N = 24);
public:
	realStandard_t radius;
	SphereRenderer();
	SphereRenderer(const SphereRenderer& other);
	~SphereRenderer() = default;


	// Inherited via RenderableBase
	void* Execute(GameObject* caller, void* params = nullptr) override;
	IComponent* Clone(void* params = nullptr) const override { return new SphereRenderer(*this);};

	void Draw() override;

};

class SquareRenderer : public RenderableBase
{
	VertexBuffer buffer;
public:
	VECTOR3 halfSides;
	typedef std::array<VERTEX_VECTOR3, 1 << DIMENSIONS> cornerArray_t;

	SquareRenderer();
	SquareRenderer(const SquareRenderer& other);

	~SquareRenderer() = default;

	cornerArray_t GetCorners(PosRot* center = nullptr);

	// Inherited via RenderableBase
	void* Execute(GameObject* caller, void* params = nullptr) override;
	IComponent* Clone(void* params = nullptr) const override;

	void Draw() override;

};




#endif
