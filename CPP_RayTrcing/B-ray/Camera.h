#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

struct Camera
{
	Camera(Vector3 cameraPos, float cilpV, float aspect_ratio);
	//摄像机坐标//画布左上角坐标//画布水平向量-U//画布垂直向量-V
	float cilp, aspect_ratio;
	Vector3 cameraPosition,horizontal,vertical,high_left_corner;
	
};

Camera::Camera( Vector3 cameraPosV, float cilpV,float aspect_r):cilp(cilpV), aspect_ratio(aspect_r),
horizontal(Vector3(2.0f, 0.0f, 0.0f)), vertical( Vector3(0.0f,2.0f/aspect_ratio, 0.0f)), cameraPosition(cameraPosV),
high_left_corner(cameraPosV - horizontal / 2.0f + vertical / 2.0f - Vector3(0.0f, 0.0f, cilp)){}

#endif // !CAMERA_H
