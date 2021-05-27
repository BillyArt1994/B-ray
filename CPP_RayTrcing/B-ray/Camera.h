#ifndef CAMERA_H
#define CAMERA_H
#include "Vector3.h"
class Camera
{
public:
	Camera(Vector3 cameraPos,float cilp,float aspect_ratio) {
		//Camera
		auto viewport_height = 2.0f;
		auto viewport_width = aspect_ratio * viewport_height;
		_cilp = cilp;

		_cameraPosition = cameraPos;
		_horizontal = Vector3(viewport_width, 0.0f, 0.0f);
		_vertical = Vector3(0.0f, viewport_height, 0.0f);
		_high_left_corner = cameraPos - _horizontal / 2 + _vertical / 2 - Vector3(0.0f, 0.0f, _cilp);
	}

	Vector3 GetPos()const { return _cameraPosition; }
	Vector3 GetLC()const { return _high_left_corner; }
	
private:
	Vector3 _cameraPosition;
	Vector3 _high_left_corner;
	Vector3 _horizontal;
	Vector3 _vertical;
	float _cilp;
};


#endif // !CAMERA_H
