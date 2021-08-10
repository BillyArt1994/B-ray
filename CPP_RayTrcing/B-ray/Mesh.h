#ifndef MESH_H
#define MESH_H
#include "Vector3.h"
#include <vector>
#include "Triangle.h"
#include "Vertex.h"
using std::vector;

struct Mesh {
	std::string name;
	vector<Triangle> triangleArray;
	vector<Vertex> vertexArray;
	unsigned vertexs_Count = 0;
	unsigned faces_Count = 0;
};
#endif // !MESH_H

