#ifndef AABB_H
#define AABB_H
#include "Vector3.h"
#include <math.h> 

class AABB {
public:
	Vector3 centralPoint = 0;
	int length = 0;

	Vector3 minPoint;
	Vector3 maxPoint;

	AABB(Vector3 cp, int len) :centralPoint(cp), length(len), minPoint(cp - (len / 2)), maxPoint(cp + (round(len / 2))) { ; }
	AABB() {}
	//获得八个子包围体
	vector<AABB> GetEightSubAABB() {
		vector<AABB> SubAABB;
		int quaLength = length / 4;
		int halfLength = length / 2;
		Vector3 cp0(centralPoint.x() + quaLength, centralPoint.y() + quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp0, halfLength));
		Vector3 cp1(centralPoint.x() - quaLength, centralPoint.y() + quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp1, halfLength));
		Vector3 cp2(centralPoint.x() + quaLength, centralPoint.y() - quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp2, halfLength));
		Vector3 cp3(centralPoint.x() - quaLength, centralPoint.y() - quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp3, halfLength));
		Vector3 cp4(centralPoint.x() + quaLength, centralPoint.y() + quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp4, halfLength));
		Vector3 cp5(centralPoint.x() - quaLength, centralPoint.y() + quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp5, halfLength));
		Vector3 cp6(centralPoint.x() + quaLength, centralPoint.y() - quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp6, halfLength));
		Vector3 cp7(centralPoint.x() - quaLength, centralPoint.y() - quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp7, halfLength));
		return SubAABB;
	}

	bool intersects(const Ray& r, float& t) {
		Vector3 rd = r.GetDirection();
		Vector3 rp = r.GetOriginPos();
		Vector3 invdir = 1 / rd;
		float tmin, tmax, tminY, tmaxY, tminZ, tmaxZ;

		if (isinf(invdir.x()))
		{
			if (rp.x() > maxPoint.x() || rp.x() < minPoint.x())
			{
				return false;
			}
			tmin = -FLT_MAX;
			tmax = FLT_MAX;
		}
		else
		{
			tmin = (minPoint.x() - rp.x()) * invdir.x();
			tmax = (maxPoint.x() - rp.x()) * invdir.x();
			if (tmin > tmax) std::swap(tmin, tmax);
		}

		if (isinf(invdir.y()))
		{
			if (rp.y() > maxPoint.y() || rp.y() < minPoint.y())
			{
				return false;
			}
			tminY = -FLT_MAX;
			tmaxY = FLT_MAX;
		}
		else
		{
			tminY = (minPoint.y() - rp.y()) * invdir.y();
			tmaxY = (maxPoint.y() - rp.y()) * invdir.y();
			if (tminY > tmaxY) std::swap(tminY, tmaxY);
		}

		if (tmaxY < tmax)
		{
			tmax = tmaxY;
		}
		if (tminY > tmin)
		{
			tmin = tminY;
		}

		if (isinf(invdir.z()))
		{
			if (rp.z() > maxPoint.z() || rp.z() < minPoint.z())
			{
				return false;
			}
			tminZ = -FLT_MAX;
			tmaxZ = FLT_MAX;
		}
		else
		{
			tminZ = (minPoint.z() - rp.z()) * invdir.z();
			tmaxZ = (maxPoint.z() - rp.z()) * invdir.z();
			if (tminZ > tmaxZ) std::swap(tminZ, tmaxZ);
		}

		if (tmaxZ < tmax)
		{
			tmax = tmaxZ;
		}
		if (tminZ > tmin)
		{
			tmin = tminZ;
		}
		t = tmax;
	}

	Vector3 GetMinPoint() {
		return minPoint;
	}

	Vector3 GetMaxPoint() {
		return maxPoint;
	}
};

bool isInside(Vertex* v, Vector3 max, Vector3 min) {
	Vector3 ver = v->position();
	float x = ver.x();
	float y = ver.y();
	float z = ver.z();

	if (x <= max.x() && y <= max.y()
		&& z <= max.z() && x >= min.x()
		&& y >= min.y() && z >= min.z()
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isInside(Vector3* v, Vector3 max, Vector3 min) {
	Vector3 ver = *v;
	float x = ver.x();
	float y = ver.y();
	float z = ver.z();

	if (x <= max.x() && y <= max.y()
		&& z <= max.z() && x >= min.x()
		&& y >= min.y() && z >= min.z()
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isContain(const Triangle& trig, const Vector3& max, Vector3& min) {
	if (isInside(trig.GetVertex(0), max, min) ||
		isInside(trig.GetVertex(1), max, min) ||
		isInside(trig.GetVertex(2), max, min)
		)
	{
		return true;
	}
	return false;
}


#endif // !AABB_H

