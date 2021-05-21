#pragma once
#include "Hittable.h"
#include "Vector3.h"
#include "Mesh.h"

class Object :public Hittable
{
public:
	Object(){}
	bool hit(const Ray& r,Mesh , hit_record& rec) {

	}
private:

};
