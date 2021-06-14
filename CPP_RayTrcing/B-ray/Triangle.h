#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vertex.h"
#include "Ray.h"
#include "Math.h"

class Triangle {
private:
	Vertex* _vertexIndex[3]{NULL,NULL,NULL};
	Vector3 _normal =NULL;
	float _dis = 0;
public:
	Triangle(Vertex& a, Vertex& b, Vertex& c) {
		_vertexIndex[0] = &a;
		_vertexIndex[1] = &b;
		_vertexIndex[2] = &c;
	}

	Triangle() {}

	Vector3 GetNormal() const { return _normal; }
	float GetDis() const { return _dis; }
	Vertex* GetVertex(int index) const { return _vertexIndex[index]; }

	void SetIndex(int index, Vertex& vertex) {
		_vertexIndex[index] = &vertex;
	}

	bool IntersectTriangle(const Ray& ray) {
		Vector3 v0 = _vertexIndex[0]->position();
		Vector3 v1 = _vertexIndex[1]->position();
		Vector3 v2 = _vertexIndex[2]->position();
		Vector3 orig = ray.GetOriginPos();
		Vector3 dir = -ray.GetDirection();

		Vector3 E1 = v1 - v0;
		Vector3 E2 = v2 - v0;
		Vector3 T = orig - v0;

		float D = Det3x3Multiply(dir, E1, E2);

		if (D==0)
		{
			return false;
		}

		float D1 = Det3x3Multiply(dir, T, E2);
		float u = D1 / D;

		if (u<0)
		{
			return false;
		}

		float D2 = Det3x3Multiply(dir, E1, T);
		float v = D2 / D;

		if (v<0||v+u>1)
		{
			return false;
		}
		float D3 = Det3x3Multiply(T, E1, E2);
		float t = D3 / D;
		_dis = D3/D;
		_normal = cross(E1, E2).normalize();
		return true;
	}
};

#endif // !TRIANGLE_H
