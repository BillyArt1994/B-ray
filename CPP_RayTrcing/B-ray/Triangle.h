#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vertex.h"
#include "Ray.h"
#include "Math.h"

class Triangle {
private:
	Vertex* _vertexIndex[3]{ NULL,NULL,NULL };
	Vector3 _normal = NULL;
public:
	Triangle(Vertex& a, Vertex& b, Vertex& c) {
		_vertexIndex[0] = &a;
		_vertexIndex[1] = &b;
		_vertexIndex[2] = &c;
	}

	Triangle() {}
	Vector3 GetNormal() { return _normal; }
	Vertex* GetVertex(int index) const { return _vertexIndex[index]; }

	void SetIndex(int index, Vertex& vertex) {
		_vertexIndex[index] = &vertex;
	}

	bool IntersectTriangle(const Ray& ray,float& t) {
		Vector3 v0 = _vertexIndex[0]->position();
		Vector3 v1 = _vertexIndex[1]->position();
		Vector3 v2 = _vertexIndex[2]->position();
		Vector3 orig = ray.GetOriginPos();
		Vector3 dir = ray.GetDirection();
		Vector3 E1 = v1 - v0;
		Vector3 E2 = v2 - v0;
		Vector3 P = cross(dir,E2);
		float det = dot(E1, P);

		Vector3 T;
		if (det > 0)
		{
			T = orig - v0;
		}
		else
		{
			T = v0 - orig;
			det = -det;
		}

		if (det < 0.0001f)
			return false;

		float u = dot(T, P);
		if (u<0.0f || u>det)
		{
			return false;
		}

		Vector3 Q = cross(T, E1);
		float v = dot(dir, Q);
		if (v<0.0f || v + u>det)
		{
			return false;
		}

		t = dot(E2, Q)*(1.0f / det);
		_normal = cross(E1, E2).normalize();
		return true;
	}
};

#endif // !TRIANGLE_H
