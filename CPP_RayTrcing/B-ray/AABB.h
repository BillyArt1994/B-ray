#ifndef AABB_H
#define AABB_H
#include "Vector3.h"

class AABB {
public:
	Vector3 centralPoint = 0;
	float length = 0;

	Vector3 minPoint;
	Vector3 maxPoint;

	AABB(Vector3 cp, float len) :centralPoint(cp), length(len), minPoint(cp - (len / 2)), maxPoint(cp + (len / 2)) { ; }
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
	float intersects(Ray r) {
		Vector3 rd = r.GetDirection();
		Vector3 rp = r.GetOriginPos();

		float tValue[6] = {0};
		tValue[0] = (minPoint.x() - rp.x()) / rd.x();
		tValue[1] = (maxPoint.x() - rp.x()) / rd.x();
		tValue[2] = (minPoint.y() - rp.y()) / rd.y();
		tValue[3] = (maxPoint.y() - rp.y()) / rd.y();
		tValue[4] = (minPoint.z() - rp.z()) / rd.z();
		tValue[5] = (maxPoint.z() - rp.z()) / rd.z();

		float Maxt = FLT_MIN;
		for (int i = 0; i < 6; i++)
		{
			if (tValue[i] > Maxt)
			{
				Maxt = tValue[i];
			}
		}
		return Maxt;
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

bool isContain(Triangle& trig, Vector3 max, Vector3 min) {
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

