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

	//void buildAABB(const Mesh& mesh) {
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

	array<AABB, 8> getEightSubAABB();

	bool intersects(const Ray& r, float& t);
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

array<AABB, 8> AABB::getEightSubAABB() {
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

//与包围盒求交获得出口t值
bool AABB::intersects(const Ray& r, float& t) {
	Vector3 rd = r.GetDirection();
	Vector3 rp = r.GetOriginPos();
	Vector3 invdir = 1 / rd;
	float tmin, tmax, tminY, tmaxY, tminZ, tmaxZ;

	if (isinf(invdir.x))
	{
		if (rp.x > maxPoint.x || rp.x < minPoint.x)
		{
			return false;
		}
		tmin = -FLT_MAX;
		tmax = FLT_MAX;
	}
	tmin = (minPoint.x - rp.x) * invdir.x;
	tmax = (maxPoint.x - rp.x) * invdir.x;
	if (tmin > tmax) std::swap(tmin, tmax);

	if (isinf(invdir.y))
	{
		if (rp.y > maxPoint.y || rp.y < minPoint.y)
		{
			return false;
		}
		tminY = -FLT_MAX;
		tmaxY = FLT_MAX;
	}
	tminY = (minPoint.y - rp.y) * invdir.y;
	tmaxY = (maxPoint.y - rp.y) * invdir.y;
	if (tminY > tmaxY) std::swap(tminY, tmaxY);

	if (tmaxY < tmax)
	{
		tmax = tmaxY;
	}

	if (tminY > tmin)
	{
		tmin = tminY;
	}

	if (isinf(invdir.z))
	{
		if (rp.z > maxPoint.z || rp.z < minPoint.z)
		{
			return false;
		}
		tminZ = -FLT_MAX;
		tmaxZ = FLT_MAX;
	}

	tminZ = (minPoint.z - rp.z) * invdir.z;
	tmaxZ = (maxPoint.z - rp.z) * invdir.z;

	if (tminZ > tmaxZ) std::swap(tminZ, tmaxZ);

	if (tmaxZ < tmax)
	{
		tmax = tmaxZ;
	}

	if (tminZ > tmin)
	{
		tmin = tminZ;
	}

	t = tmax;
	return true;
}
#endif // !AABB_H

