#ifndef RENDERABLE
#define RENDERABLE

class VertexBuffer;

class IRenderable
{
public:
	IRenderable() = default;
	virtual ~IRenderable() = default;

	virtual void Draw() = 0;
};


#endif
