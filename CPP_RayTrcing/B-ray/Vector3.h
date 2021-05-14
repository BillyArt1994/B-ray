#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
private:
	double _x;
	double _y;
	double _z;
public:
	double x() const { return this->_x; }
	double y() const { return this->_y; }
	double z() const { return this->_z; }


	Vector3(double x, double y, double z) :
		_x(x), _y(y), _z(z)
	{}

	Vector3() {}

	Vector3(double value) :_x(value), _y(value), _z(value) {}

	double length() {
		return sqrt(this->x()*this->x() + this->y()*this->y() + this->z()*this->z());
	}

	Vector3 normalize() {
		return *this / this->length();
	}

	//ÔËËã·ûÖØÔØ
	inline Vector3 operator -(const Vector3 &b) {
		return Vector3(this->_x - b.x(), this->_y - b.y(), this->_z - b.z());
	}

	inline Vector3 operator +(const Vector3 &b) {
		return Vector3(this->_x + b.x(), this->_y + b.y(), this->_z + b.z());
	}

	inline Vector3 operator *(const double &b) {
		return Vector3(this->_x * b, this->_y * b, this->_z * b);
	}

	inline Vector3 operator *=(const double &b) {
		_x = _x * b;
		_y = _y * b;
		_z = _z * b;
		return *this;
	}

	inline Vector3 operator /(const double &b) {
		return Vector3(this->_x / b, this->_y / b, this->_z / b);
	}
};

using Color = Vector3;

inline double dot(const Vector3 &a, const Vector3 &b) {
	return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

#endif // Vector3_H

