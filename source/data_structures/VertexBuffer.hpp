#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "../defines.hpp"
#include INCL_GEOMETRY
#include INCL_GLM
#include <vector>


class VertexBuffer
{
	std::vector<Vertex> verticies;
	unsigned int bufferID;
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void AddVertex(Vertex* vertex);
	void Clear();
	std::vector<Vertex>* GetBuffer();
	unsigned int GetBufferID();

};



#endif
