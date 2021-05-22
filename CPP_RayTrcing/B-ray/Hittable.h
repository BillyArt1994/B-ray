#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Mesh.h"

struct hit_record {
	Vector3 pos;
	Vector3 normal;
	float t;
};

class Hittable:Mesh
{
public:
	bool hit(const Ray& r, hit_record& rec) {
		Vector3 v1 = triangle[]
		Vector3 normal = 
	}
private:
};
#endif // !HITTABLE_H
