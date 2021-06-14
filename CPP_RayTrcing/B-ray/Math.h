#ifndef Math
#define Math
#include <cmath>
#include <string>
#include "Triangle.h"

inline float Det3x3Multiply(Vector3& a, Vector3& b, Vector3& c) {
	float positive = a.x()*b.y()*c.z() + a.z()*b.x()*c.y() + a.y()*b.z()*c.x();
	float negative = c.x()*b.y()*a.z() + c.z()*b.x()*a.y() + c.y()*a.x()*b.z();
	return positive - negative;
}

inline float dot(const Vector3 &a, const Vector3 &b) {
	return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

inline Vector3 cross(const Vector3 &a, const Vector3 &b) {
	return Vector3(a.y()*b.z() - a.z()*b.y(), a.z()*b.x() - a.x()*b.z(), a.x()*b.y() - a.y()*b.x());
}

inline std::string DecTiBin(const float dec) {
	std::string result = "";
	int temp = dec;
	while (temp)
	{
		result.insert(0, std::to_string(temp % 2));
		temp = temp / 2;
	}
	return result;
}

inline float CompareSize(Vector3 a) {
	float minSize = 0;
	float x = abs(a.x()), y = abs(a.y()), z = abs(a.z());
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

#endif // !Math
