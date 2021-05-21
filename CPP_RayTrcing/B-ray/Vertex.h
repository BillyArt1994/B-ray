#ifndef VERTEX_H
#define VERTEX_H
#include "Vector3.h"

class Vertex
{
public:
	Vertex(Vector3 vertex,Vector3 normal,Vector3 texcoord):
		_vertex(vertex), _normal(normal), _texcoord(texcoord){}

	Vertex(Vector3 vertex) :_vertex(vertex) {}

	void SetVertex(Vector3 vertex) {
		_vertex = vertex;
	}

	void SetNormal(Vector3 normal) {
		_vertex = normal;
	}

	void SetTexcoord(Vector3 texcoord) {
		_vertex = texcoord;
	}
	
	Vector3 vertex()const { return this->_vertex; }
	Vector3 normal()const { return this->_normal; }
	Vector3 texcoord()const { return this->_texcoord; }

private:
	Vector3 _vertex;
	Vector3 _normal;
	Vector3 _texcoord;
};
#endif // !VERTEX_H

