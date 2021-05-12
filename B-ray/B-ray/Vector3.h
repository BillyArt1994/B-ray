#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
	private:
		double _x;
		double _y;
		double _z;
	public:
		double x() const { return this->_x; }
		double y() const { return this->_y; }
		double z() const { return this->_z; }


		Vector3(double x ,double y,double z):
		_x(x),_y(y),_z(z)
		{}

		Vector3(){}

		Vector3(double value):_x(value),_y(value),_z(value){}
	
		Vector3 operator -(const Vector3 &b ) {
			return Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
		}

		Vector3 operator +(const Vector3 &b) {
			return Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
		}

};

using Color = Vector3;

#endif // Vector3_H

