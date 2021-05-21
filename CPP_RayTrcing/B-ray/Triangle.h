#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include "Vertex.h"

class Triangle {
	
private:
	int _vertexIndex[3];
public:
	Triangle(int a, int b , int c) {
		_vertexIndex[0] = a;
		_vertexIndex[1] = b;
		_vertexIndex[2] = c;
	}

	void SetIndex(int index,int value) {
		_vertexIndex[index] = value;
	}

	Triangle() {

	}

};
#endif // !TRIANGLE_H
