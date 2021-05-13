#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray(){}
	Ray(const Vector3 &pos,const Vector3 &dir):_originPos(pos), _dirction(dir){}

	Vector3 GetOriginPos() const { return _originPos; }
	Vector3 GetDirection() const { return _dirction; }

	Vector3 RayRun(double dis) {
		return _originPos + dis * _dirction;
	}

private:
	Vector3 _dirction;
	Vector3 _originPos;
}

#endif

