#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct hit_record {
	Vector3 pos;
	Vector3 normal;
	float t;
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
private:
};
#endif // !HITTABLE_H
