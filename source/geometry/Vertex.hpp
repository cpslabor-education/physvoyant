#ifndef VERTEX
#define VERTEX

#include "../defines.hpp"

struct Vertex
{
	VERTEX_VECTOR3 position;
	VERTEX_VECTOR3 color;
	// VECTOR3 normal; // no Phong shading now
};


#endif
