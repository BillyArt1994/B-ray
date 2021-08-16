#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

struct Camera
{
	Camera(Vector3 cameraPos, float cilp, float aspect_ratio);
	//摄像机坐标//画布左上角坐标//画布水平向量-U//画布垂直向量-V
	Vector3 cameraPosition, high_left_corner, horizontal, vertical;
	float cilp;
};

Camera::Camera( Vector3 cameraPosV, float cilpV,float aspect_ratio) {
		//Camera
		float viewport_height = 2.0f;
		float viewport_width = aspect_ratio * viewport_height;

		cilp = cilpV;
		cameraPosition = cameraPosV;
		horizontal = Vector3(viewport_width, 0.0f, 0.0f);
		vertical = Vector3(0.0f, viewport_height, 0.0f);
		high_left_corner = cameraPosV - horizontal / 2 + vertical / 2 - Vector3(0.0f, 0.0f, cilp);
}

#endif // !CAMERA_H
