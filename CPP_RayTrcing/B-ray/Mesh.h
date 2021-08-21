#ifndef MESH_H
#define MESH_H

#include "Vector3.h"
#include <vector>
#include "Triangle.h"
#include "Vertex.h"
using std::vector;

struct Mesh {
public:
	std::string name;
	Triangle* triangleArray;
	Vertex* vertexArray;
	Mesh(){}
	~Mesh(){}
	unsigned vertexs_Count = 0, faces_Count = 0;
};

#endif // !MESH_H

