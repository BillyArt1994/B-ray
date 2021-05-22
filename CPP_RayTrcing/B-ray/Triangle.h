#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include "Vertex.h"

class Triangle {
	
private:
	Vector3 _vertexIndex[3];
public:
	Triangle(Vector3 a, Vector3 b , Vector3 c) {
		_vertexIndex[0] = a;
		_vertexIndex[1] = b;
		_vertexIndex[2] = c;
	}

	void SetIndex(int index, Vector3 value) {
		_vertexIndex[index] = value;
	}

	Triangle() {

	}

};
#endif // !TRIANGLE_H
