#ifndef MESH_H
#define MESH_H

#include "Vector3.h"
#include <vector>
#include "Triangle.h"
#include "Vertex.h"
using std::vector;

struct AABB;
struct Mesh {
public:
	std::string name;
	vector<Triangle> triangleArray;
	vector<Vertex> vertexArray;
	AABB* Bound;
	unsigned int getVertexCount() const { return vertexs_Count; }
	unsigned int getFaceCount() const { return faces_Count; }

	void setVertexCount(const unsigned& num) { vertexs_Count = num ;}
	void setFaceCount(const unsigned& num) { faces_Count = num ;}
private:
	unsigned vertexs_Count = 0, faces_Count = 0;
};

#endif // !MESH_H

