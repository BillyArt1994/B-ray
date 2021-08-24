#ifndef MATH_H
#define MATH_H

#include "Vector3.h"
#include <cstdlib>

inline float Det3x3Multiply(Vector3& a, Vector3& b, Vector3& c) {
	float positive = a.x*b.y*c.z + a.z*b.x*c.y + a.y*b.z*c.x;
	float negative = c.x*b.y*a.z + c.z*b.x*a.y + c.y*a.x*b.z;
	return positive - negative;
}

inline float dot(const Vector3 &a, const Vector3 &b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vector3 cross(const Vector3 &a, const Vector3 &b) {
	return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

inline float Min(const float& x, const float& y, const float& z) {
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

inline float Min(const float& x, const float& y) {
	return x < y ? x : y;
}

inline float Max(const float& x, const float& y, const float& z) {
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

inline float Max(const float& x, const float& y) {
	return x > y ? x : y;
}

inline Vector3 Max(const Vector3& a, const Vector3& b) {
	return Vector3(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z));
}

inline Vector3 Min(const Vector3& a, const Vector3& b) {
	return Vector3(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z));
}

inline int Abs(int x) { int a = x >> 31; return ((x ^ a) - a); }

inline float CompareSize(Vector3 a) {
	float minSize = 0;
	float x = abs(a.x), y = abs(a.y), z = abs(a.z);
	if (x > minSize)
	{
		minSize = x;
	}
	if (y > minSize)
	{
		minSize = y;
	}
	if (z > minSize)
	{
		minSize = z;
	}

	return minSize;
}


inline bool is_pow_of_2(int x) {
	return !(x & (x - 1));
}

inline int Nearest2Power(int i) {
	i |= (i >> 1);
	i |= (i >> 2);
	i |= (i >> 4);
	i |= (i >> 8);
	i |= (i >> 16);
	return i + 1;
}

inline float clamp(const float x, const float min, const float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline float Q_rsqrt(float& number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = number * 0.5f;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2*y*y));
	//	y = y * (threehalfs - (x2*y*y));
	return y;
}

inline float random_float() {
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max) {
	// Returns a random real in [min,max).
	return min + (max - min)*random_float();
}

inline Vector3 random_vector3() {
	return Vector3(random_float(), random_float(), random_float());
}

inline Vector3 random_vector3(float min, float max) {
	return Vector3(random_float(), random_float(), random_float());
}

Vector3 random_in_unit_sphere() {
	while (true) {
		auto p = random_vector3(-1.0f, 1.0f);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}



#endif // !MATH
