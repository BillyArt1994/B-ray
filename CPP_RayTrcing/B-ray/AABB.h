#ifndef AABB_H
#define AABB_H

#include "Vector3.h"
#include "Math.h"
#include <array>
using std::array;

struct AABB {
	AABB() {}
	AABB(Vector3 maxP, Vector3 minP);
	Vector3 minPoint = 0;
	Vector3 maxPoint = 0;

	//	void buildAABB(const Mesh& mesh) {
		//	Vector3 minValue(FLT_MAX, FLT_MAX, FLT_MAX);
		//	Vector3 maxValue(FLT_MIN, FLT_MIN, FLT_MIN);
		//	int length = mesh.getVertexCount();

		//	for (size_t i = 0; i < length; i++)
		//	{
		//		minValue.x = Min(mesh.vertexArray[i].position.x, minValue.x);
		//		minValue.y = Min(mesh.vertexArray[i].position.y, minValue.y);
		//		minValue.z = Min(mesh.vertexArray[i].position.z, minValue.z);

		//		maxValue.x = Max(mesh.vertexArray[i].position.x, minValue.x);
		//		maxValue.y = Max(mesh.vertexArray[i].position.y, minValue.y);
		//		maxValue.z = Max(mesh.vertexArray[i].position.z, minValue.z);
		//	}

		//	minPoints = minValue;
		//	maxPoints = maxValue;
		//}

	bool checkIfInside(const Vector3& point);

	bool checkIfInside(const Triangle& trig);

	array<AABB,8> getEightSubAABB();


};

AABB::AABB(Vector3 maxP, Vector3 minP) :minPoint(minP), maxPoint(maxP) {}

bool AABB::checkIfInside(const Vector3& point) {
	if (point.x > maxPoint.x || point.y > maxPoint.y || point.z > maxPoint.z ||
		point.x < minPoint.x || point.y < minPoint.y || point.z < minPoint.z)
	{
		return false;
	}
	return true;
}

bool AABB::checkIfInside(const Triangle& trig) {
	if (checkIfInside(trig._vertexArray[0]->position))
	{
		return true;
	}
	if (checkIfInside(trig._vertexArray[1]->position))
	{
		return true;
	}
	if (checkIfInside(trig._vertexArray[2]->position))
	{
		return true;
	}
	return false;
}

array<AABB,8> AABB::getEightSubAABB() {
	array<AABB, 8> subBound;
	float length = (maxPoint.x - minPoint.x) / 2;
	Vector3 maxPfourB = maxPoint;
	Vector3 minPfourB = maxPoint - length;
	subBound[0].maxPoint = maxPfourB - Vector3(0, 0, length);
	subBound[0].minPoint = minPfourB - Vector3(0, 0, length);
	subBound[1].maxPoint = maxPfourB - Vector3(length, 0, length);
	subBound[1].minPoint = minPfourB - Vector3(length, 0, length);
	subBound[2].maxPoint = maxPfourB - Vector3(0, length, length);
	subBound[2].minPoint = minPfourB - Vector3(0, length, length);
	subBound[3].maxPoint = maxPfourB - Vector3(length, length, length);
	subBound[3].minPoint = minPfourB - Vector3(length, length, length);
	subBound[4].maxPoint = maxPfourB;
	subBound[4].minPoint = minPfourB;
	subBound[5].maxPoint = maxPfourB - Vector3(length, 0, 0);
	subBound[5].minPoint = minPfourB - Vector3(length, 0, 0);
	subBound[6].maxPoint = maxPfourB - Vector3(0, length, 0);
	subBound[6].minPoint = minPfourB - Vector3(0, length, 0);
	subBound[7].maxPoint = maxPfourB - Vector3(length, length, 0);
	subBound[7].minPoint = minPfourB - Vector3(length, length, 0);
	return subBound;
}
#endif // !AABB_H

