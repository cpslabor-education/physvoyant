#ifndef RENDERABLE
#define RENDERABLE

class VertexBuffer;

class IRenderable
{
public:
	IRenderable() = default;
	virtual ~IRenderable() = default;

	virtual VertexBuffer* GetVertexBuffer(GameObject* caller) = 0;
};


#endif
