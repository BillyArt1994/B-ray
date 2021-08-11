#ifndef AABB_H
#define AABB_H

#include "Vector3.h"
#include "Math.h"

struct AABB {
	AABB(Vector3 maxP, Vector3 minP);
	Vector3 minPoints;
	Vector3 maxPoints;

	void buildAABB(const Mesh& mesh) {
		Vector3 minValue(FLT_MAX, FLT_MAX, FLT_MAX);
		Vector3 maxValue(FLT_MIN, FLT_MIN, FLT_MIN);
		int length = mesh.getVertexCount();

		for (size_t i = 0; i < length; i++)
		{
			minValue.x = Min(mesh.vertexArray[i].position.x, minValue.x);
			minValue.y = Min(mesh.vertexArray[i].position.y, minValue.y);
			minValue.z = Min(mesh.vertexArray[i].position.z, minValue.z);

			maxValue.x = Max(mesh.vertexArray[i].position.x, minValue.x);
			maxValue.y = Max(mesh.vertexArray[i].position.y, minValue.y);
			maxValue.z = Max(mesh.vertexArray[i].position.z, minValue.z);
		}

		minPoints = minValue;
		maxPoints = maxValue;
	}
};

AABB::AABB(Vector3 maxP, Vector3 minP):minPoints(minP), maxPoints(maxP){}
#endif // !AABB_H

