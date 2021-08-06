#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
private:
	float _x;
	float _y;
	float _z;
public:
	inline float x() const { return this->_x; }
	inline float y() const { return this->_y; }
	inline float z() const { return this->_z; }

	void x(float value) { _x = value; }
	void y(float value) { _y = value; }
	void z(float value) { _z = value; }

	Vector3(float x, float y, float z) :
		_x(x), _y(y), _z(z) {}

	Vector3() {}

	Vector3(float value) :_x(value), _y(value), _z(value) {}

	float length() {
		return sqrt(this->x()*this->x() + this->y()*this->y() + this->z()*this->z());
	}

	Vector3 normalize() {
		return *this / this->length();
	}

	//‘ÀÀ„∑˚÷ÿ‘ÿ
	inline Vector3 operator -(const Vector3 &b) {
		return Vector3(_x - b.x(), _y - b.y(), _z - b.z());
	}

	inline Vector3 operator +(const Vector3 &b) {
		return Vector3(_x + b.x(), _y + b.y(), _z + b.z());
	}

	inline Vector3 operator +(const float &b) {
		return Vector3(_x + b, _y + b, _z + b);
	}

	inline Vector3 operator +=(const Vector3 &b) {
		_x += b.x();
		_y += b.y();
		_z += b.z();
		return *this;
	}

	inline Vector3& operator *=(const float &b) {
		_x = _x * b;
		_y = _y * b;
		_z = _z * b;
		return *this;
	}

	inline Vector3 operator /(const float &b) {
		return Vector3(_x / b, _y / b, _z / b);
	}

	inline bool operator ==(const Vector3& b) {
		if (_x == b.x() && _y == b.y() && _z == b.z())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool operator !=(const Vector3& b) {
		if (_x == b.x() && _y == b.y() && _z == b.z())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	inline Vector3 operator - () {
		_x =-_x;
		_y =-_y;
		_z =-_z;
		return *this;
	}

	inline Vector3 operator -=  (const Vector3 b) {
		_x -= b.x();
		_y -= b.y();
		_z -= b.z();
		return *this;
	}
};

inline Vector3 operator *(const Vector3& a, const float &b) {
	return Vector3(a.x()*b, a.y()*b, a.z()*b);
}

inline Vector3 operator *(const float& a, const Vector3 &b) {
	return Vector3(a*b.x(), a*b.y(), a*b.z());
}

inline Vector3 operator /(const float &a, const Vector3 &b) {
	return Vector3(a / b.x(), a / b.y(), a / b.z());
}

using Color = Vector3;
#endif // Vector3_H
