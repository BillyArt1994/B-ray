#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
private:
	float _x;
	float _y;
	float _z;
public:
	float x() const { return this->_x; }
	float y() const { return this->_y; }
	float z() const { return this->_z; }

	void x(float& value) { _x = value; }
	void y(float& value) { _y = value; }
	void z(float& value) { _z = value; }

	Vector3(float x, float y, float z) :
		_x(x), _y(y), _z(z)
	{}

	Vector3() {}

	Vector3(float& value) :_x(value), _y(value), _z(value) {}


	float length() {
		return sqrt(this->x()*this->x() + this->y()*this->y() + this->z()*this->z());
	}

	Vector3 normalize() {
		return *this / this->length();
	}

	//ÔËËã·ûÖØÔØ
	inline Vector3 operator -(const Vector3 &b) {
		_x -= b.x();
		_y -= b.y();
		_z -= b.z();
		return *this;
	}

	inline Vector3 operator +(const Vector3 &b) {
		_x += b.x();
		_y += b.y();
		_z += b.z();
		return *this;
	}

	inline Vector3 operator *(const float &b) {
		_x = _x * b;
		_y = _y * b;
		_z = _z * b;
		return *this;
	}

	inline Vector3& operator *=(const float &b) {
		_x = _x * b;
		_y = _y * b;
		_z = _z * b;
		return *this;
	}

	inline Vector3 operator /(const float &b) {
		return Vector3(this->_x / b, this->_y / b, this->_z / b);
	}

	inline Vector3 operator -() {
		_x = -_x;
		_y = -_y;
		_z = -_z;
		return *this;
	}
};

using Color = Vector3;

inline float dot(const Vector3 &a, const Vector3 &b) {
	return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

#endif // Vector3_H

