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
	PosRot* positionPtr;
public:
	SphereRenderer();

	~SphereRenderer() = default;


	// Inherited via RenderableBase
	void* Execute(GameObject* caller, void* params = nullptr) override;
	IComponent* Clone(void* params = nullptr) const override { return new SphereRenderer(*this);};

	void Draw() override;

};

class SquareRenderer : public RenderableBase
{
public:
	VertexBuffer buffer;
	VECTOR3 halfSides;
	typedef std::array<VECTOR3, 1 << DIMENSIONS> cornerArray_t;

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
