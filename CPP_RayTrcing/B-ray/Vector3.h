#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

struct Vector3 {

	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vector3() {}

	Vector3(const float value) :x(value), y(value), z(value) {}

	Vector3(const float a, const float b, const float c) :
		x(a), y(b), z(c) {}

	//ÔËËã·ûÖØÔØ
	inline Vector3 operator -(const Vector3 &b) {
		return Vector3(x - b.x, y - b.y, z - b.z);
	}

	inline Vector3 operator +(const Vector3 &b) {
		return Vector3(x + b.x, y + b.y, z + b.z);
	}

	inline Vector3 operator +(const float &b) {
		return Vector3(x + b, y + b, z + b);
	}

	inline Vector3 operator +=(const Vector3 &b) {
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	inline Vector3& operator *=(const float &b) {
		x = x * b;
		y = y * b;
		z = z * b;
		return *this;
	}

	inline Vector3 operator /(const float &b) {
		return Vector3(x / b, y / b, z / b);
	}

	inline bool operator ==(const Vector3& b) {
		if (x == b.x && y == b.y && z == b.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool operator !=(const Vector3& b) {
		if (x == b.x && y == b.y && z == b.z)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	inline float length() {
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	inline Vector3 normalize() {
		return *this / this->length();
	}

	inline Vector3 operator -() {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline Vector3 operator -=  (const Vector3 b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}
};

inline Vector3 operator *(const Vector3& a, const float &b) {
	return Vector3(a.x*b, a.y*b, a.z*b);
}

inline Vector3 operator *(const float& a, const Vector3 &b) {
	return Vector3(a*b.x, a*b.y, a*b.z);
}

inline Vector3 operator /(const float &a, const Vector3 &b) {
	return Vector3(a / b.x, a / b.y, a / b.z);
}

using Color = Vector3;
#endif // Vector3_H
