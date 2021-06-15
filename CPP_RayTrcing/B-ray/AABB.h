#ifndef AABB_H
#define AABB_H
#include "Vector3.h"

class AABB {
public:
	Vector3 centralPoint;
	float length;

	AABB(Vector3 cp,float len) :centralPoint(cp),length(len) { ; }
	
	//获得八个子包围体
	vector<AABB> GetEightSubAABB() {
		vector<AABB> SubAABB;
		float quaLength = length/4;
		float halfLength = length/2;
		Vector3 cp1(centralPoint.x()-quaLength, centralPoint.y() - quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp1, halfLength));
		Vector3 cp2(centralPoint.x() + quaLength, centralPoint.y() - quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp2, halfLength));
		Vector3 cp3(centralPoint.x() - quaLength, centralPoint.y() + quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp2, halfLength));
		Vector3 cp4(centralPoint.x() + quaLength, centralPoint.y() + quaLength, centralPoint.z() + quaLength);
		SubAABB.push_back(AABB(cp3, halfLength));
		Vector3 cp5(centralPoint.x() - quaLength, centralPoint.y() - quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp4, halfLength));
		Vector3 cp6(centralPoint.x() + quaLength, centralPoint.y() - quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp6, halfLength));
		Vector3 cp7(centralPoint.x() - quaLength, centralPoint.y() + quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp7, halfLength));
		Vector3 cp8(centralPoint.x() + quaLength, centralPoint.y() + quaLength, centralPoint.z() - quaLength);
		SubAABB.push_back(AABB(cp8, halfLength));
		return SubAABB;
	}

	Vector3 GetMinPoint() {
		return Vector3(centralPoint - (length / 2));
	}

	Vector3 GetMaxPoint() {
		return Vector3(centralPoint + (length / 2));
	}
};

bool isInside(Vertex* v, Vector3 max, Vector3 min) {
	Vector3 ver = v->position();
	float x = ver.x();
	float y = ver.y();
	float z = ver.z();

	if (x <max.x() && y < max.y()
		&& z<max.z() && x>min.x() 
		&& y>min.y() && z>min.z()
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

float intersects() {
	//0 
	//1 o-l/2
	//2 

}
#endif // !AABB_H

