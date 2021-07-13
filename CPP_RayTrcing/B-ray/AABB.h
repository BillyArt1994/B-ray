#ifndef AABB_H
#define AABB_H
#include "Vector3.h"
#include <math.h> 

class AABB {
public:
	Vector3 centralPoint = 0;
	float length = 0;

	Vector3 minPoint;
	Vector3 maxPoint;

	AABB(Vector3 cp, float len) :centralPoint(cp), length(len), minPoint(cp - (len / 2.0f)), maxPoint(cp + (len / 2.0f)) { ; }
	AABB() {}
	//获得八个子包围体
	vector<AABB> GetEightSubAABB() {
		vector<AABB> SubAABB;
		float quaLength = length / 4;
		float halfLength = length / 2;
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

	//与包围盒求交获得出口t值
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

};

//判断顶点是否存在在包围盒内
bool isInside(const Vector3& v, const AABB& aabb) {
	Vector3 ver = v;
	float x = ver.x();
	float y = ver.y();
	float z = ver.z();

	if (x <= aabb.maxPoint.x() && y <= aabb.maxPoint.y()
		&& z <= aabb.maxPoint.z() && x >= aabb.minPoint.x()
		&& y >= aabb.minPoint.y() && z >= aabb.minPoint.z()
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//判断三角面是否存在在包围盒内
bool isContain(const Triangle& trig,const AABB& aabb) {
	Vector3 v0 = trig.GetVertex(0)->position();
	Vector3 v1 = trig.GetVertex(1)->position();
	Vector3 v2 = trig.GetVertex(2)->position();

	if (isInside(v0, aabb) ||
		isInside(v1, aabb) ||
		isInside(v2, aabb)
		)
	{
		return true;
	}

	Vector3 c = aabb.centralPoint;
	Vector3 e = aabb.length/2.0f;

	v0 -= c;
	v1 -= c;
	v2 -= c;

	Vector3 f0 = v1 - v0;
	Vector3 f1 = v2 - v1;
	Vector3 f2 = v0 - v2;

	Vector3 u0 (1.0f, 0.0f, 0.0f);
	Vector3 u1 (0.0f, 1.0f, 0.0f);
	Vector3 u2 (0.0f, 0.0f, 1.0f);

	Vector3 axis_u0_f0 = cross(u0, f0);
	Vector3 axis_u0_f1 = cross(u0, f1);
	Vector3 axis_u0_f2 = cross(u0, f2);

	Vector3 axis_u1_f0 = cross(u0, f0);
	Vector3 axis_u1_f1 = cross(u0, f1);
	Vector3 axis_u1_f2 = cross(u0, f2);

	Vector3 axis_u2_f0 = cross(u0, f0);
	Vector3 axis_u2_f1 = cross(u0, f1);
	Vector3 axis_u2_f2 = cross(u0, f2);

	float p0 = dot(v0, axis_u0_f0);
	float p1 = dot(v1, axis_u0_f0);
	float p2 = dot(v2, axis_u0_f0);

	float r = e.x()*abs(dot(u0, axis_u0_f0)) +
			  e.y()*abs(dot(u1, axis_u0_f0)) +
			  e.z()*abs(dot(u2, axis_u0_f0));

	if (max(-Max(p0,p1,p2),Min(p0,p1,p2))>r)
	{
		return false;
	}

	return false;
}


#endif // !AABB_H

