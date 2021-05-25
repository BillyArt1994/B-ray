#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include "Vertex.h"
#include "Ray.h"

class Triangle {

private:
	Vertex _vertexIndex[3];
	float _dis;
public:
	Triangle(Vertex& a, Vertex& b, Vertex& c) {
		_vertexIndex[0] = a;
		_vertexIndex[1] = b;
		_vertexIndex[2] = c;
	}

	Triangle() {}

	float GetDis()const { return _dis;}

	void SetIndex(int& index, Vertex& vertex) {
		_vertexIndex[index] = vertex;
	}

	bool IntersectTriangle(const Ray& ray) {
		Vector3 E1 = _vertexIndex[1].position() - _vertexIndex[0].position();
		Vector3 E2 = _vertexIndex[2].position() - _vertexIndex[0].position();
		Vector3 T = ray.GetOriginPos() - _vertexIndex[0].position();
		float D = Det3x3Multiply(-ray.GetDirection(), E1, E2);

		if (D==0)
		{
			return false;
		}
		float D1 = Det3x3Multiply(-ray.GetDirection(), T, E2);
		float u = D1 / D;
		if (u<0)
		{
			return false;
		}
		float D2 = Det3x3Multiply(-ray.GetDirection(), E1, T);
		float v = D2 / D;
		if (v<0||v+u>1)
		{
			return false;
		}
		float D3 = Det3x3Multiply(T, E1, E2);
		float t = D3 / D;
		_dis = D3/D;
		return true;
	}

	float Det3x3Multiply(Vector3 a, Vector3 b, Vector3 c) {
		float positive = a.x()*b.y()*c.z() + a.z()*b.x()*c.y() + a.y()*b.z()*c.x();
		float negative = c.x()*b.y()*a.z() + c.z()*b.x()*a.y() + c.y()*a.x()*b.z();
		return positive - negative;
	}
};
#endif // !TRIANGLE_H
