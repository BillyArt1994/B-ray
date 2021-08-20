#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray(){}
	Ray(const Ray& r) {
		_dirction = r._dirction;
		_originPos = r._originPos;
	}
	Ray(const Vector3 pos,const Vector3 dir):_originPos(pos), _dirction(dir){}

	Vector3 GetOriginPos() const { return _originPos; }
	Vector3 GetDirection() const { return _dirction; }

	Vector3 RayRun(float dis) {
		return _originPos + _dirction* dis;
	}

private:
	Vector3 _dirction, _originPos;
};

#endif

