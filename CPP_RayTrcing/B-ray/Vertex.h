#ifndef VERTEX_H
#define VERTEX_H
#include "Vector3.h"

struct Vertex
{
	Vertex(Vector3 pos, Vector3 nor, Vector3 uv) :position(pos), normal(nor), texcoord(uv) {}
	Vector3 position;
	Vector3 normal;
	Vector3 texcoord;
};
#endif // !VERTEX_H

