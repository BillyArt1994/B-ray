#ifndef VERTEX_H
#define VERTEX_H
#include "Vector3.h"

class Vertex
{
public:
	Vertex(Vector3 vertex,Vector3 normal,Vector3 texcoord):
		_vertex(vertex), _normal(normal), _texcoord(texcoord){}

	Vertex(Vector3 vertex) :_vertex(vertex) {}

	Vertex(){}

	void SetVertex(Vector3 vertex) {
		_vertex = vertex;
	}

	void SetNormal(Vector3 normal) {
		_vertex = normal;
	}

	void SetTexcoord(Vector3 texcoord) {
		_vertex = texcoord;
	}
	
	void SetIndex(int index) {
		_index = index;
	}

	Vector3 position()const { return _vertex; }
	Vector3 normal()const { return _normal; }
	Vector3 texcoord()const { return _texcoord; }
	int index()const { return _index; }

private:
	Vector3 _vertex;
	Vector3 _normal;
	Vector3 _texcoord;
	int _index;
};
#endif // !VERTEX_H

