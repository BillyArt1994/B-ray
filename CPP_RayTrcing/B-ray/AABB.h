#ifndef AABB_H
#define AABB_H

#include "Vector3.h"
#include "Math.h"
#include "Mesh.h"
#include <array>
using std::array;

struct AABB {
	AABB() {}
	~AABB(){}
	AABB(Vector3 maxP, Vector3 minP);
	Vector3 minPoint = 0;
	Vector3 maxPoint = 0;

	void buildAABB(const Mesh* mesh) {
		Vector3 minValue(FLT_MAX, FLT_MAX, FLT_MAX);
		Vector3 maxValue(FLT_MIN, FLT_MIN, FLT_MIN);
		int length = mesh->faces_Count;

		for (size_t i = 0; i < length; i++)
		{
			minValue.x = Min(mesh->vertexArray[i].position.x, minValue.x);
			minValue.y = Min(mesh->vertexArray[i].position.y, minValue.y);
			minValue.z = Min(mesh->vertexArray[i].position.z, minValue.z);

			maxValue.x = Max(mesh->vertexArray[i].position.x, maxValue.x);
			maxValue.y = Max(mesh->vertexArray[i].position.y, maxValue.y);
			maxValue.z = Max(mesh->vertexArray[i].position.z, maxValue.z);
		}

		minPoint = minValue;
		maxPoint = maxValue;
	}

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

	Vector3 v0 (trig._vertexArray[0]->position);
	Vector3 v1 (trig._vertexArray[1]->position);
	Vector3 v2 (trig._vertexArray[2]->position);

	if (checkIfInside(v0)|| checkIfInside(v1)|| checkIfInside(v2))
	{
		return true;
	}

	Vector3 e ((maxPoint.x - minPoint.x)/2);
	Vector3 c ( maxPoint-e);

	v0 -= c;
	v1 -= c;
	v2 -= c;

	Vector3 boxNormal[3]{ Vector3(1.0f, 0.0f, 0.0f),Vector3(0.0f, 1.0f, 0.0f),Vector3(0.0f, 0.0f, 1.0f) };
	Vector3 tirgleEdge[3]{ v1 - v0,v2 - v1,v0 - v2 };
	Vector3 axisArray[13] = {
		boxNormal[0],boxNormal[1],boxNormal[2],
		cross(tirgleEdge[0],tirgleEdge[1]),
		cross(boxNormal[0],tirgleEdge[0]), cross(boxNormal[0], tirgleEdge[1]), cross(boxNormal[0], tirgleEdge[2]),
		cross(boxNormal[1],tirgleEdge[0]), cross(boxNormal[1], tirgleEdge[1]), cross(boxNormal[1], tirgleEdge[2]),
		cross(boxNormal[2],tirgleEdge[0]), cross(boxNormal[2], tirgleEdge[1]), cross(boxNormal[2], tirgleEdge[2]),
	};

	for (int i = 0; i < 13; i++)
	{
		float p0 = dot(v0, axisArray[i]);
		float p1 = dot(v1, axisArray[i]);
		float p2 = dot(v2, axisArray[i]);

		float r = e.x*abs(dot(boxNormal[0], axisArray[i])) +
			e.y*abs(dot(boxNormal[1], axisArray[i])) +
			e.z*abs(dot(boxNormal[2], axisArray[i]));

		if (Min(p0, p1, p2) > r || -Max(p0, p1, p2) > r)
		{
			return false;
		}
	}
	return true;
}

array<AABB, 8> AABB::getEightSubAABB() {
	array<AABB, 8> subBound;
	float length = (maxPoint.x - minPoint.x) / 2;
	Vector3 maxPfourB = maxPoint;
	Vector3 minPfourB = maxPoint - length;
	subBound[0].maxPoint = maxPfourB;
	subBound[0].minPoint = minPfourB;
	subBound[1].maxPoint = maxPfourB - Vector3(length, 0, 0);
	subBound[1].minPoint = minPfourB - Vector3(length, 0, 0);
	subBound[2].maxPoint = maxPfourB - Vector3(0, length, 0) ;
	subBound[2].minPoint = minPfourB - Vector3(0, length, 0);
	subBound[3].maxPoint = maxPfourB - Vector3(length, length, 0);
	subBound[3].minPoint = minPfourB - Vector3(length, length, 0);
	subBound[4].maxPoint = maxPfourB - Vector3(0, 0, length);
	subBound[4].minPoint = minPfourB - Vector3(0, 0, length);
	subBound[5].maxPoint = maxPfourB - Vector3(length, 0, length);
	subBound[5].minPoint = minPfourB - Vector3(length, 0, length);
	subBound[6].maxPoint = maxPfourB - Vector3(0, length, length);
	subBound[6].minPoint = minPfourB - Vector3(0, length, length);
	subBound[7].maxPoint = maxPfourB - Vector3(length, length, length);
	subBound[7].minPoint = minPfourB - Vector3(length, length, length);
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

