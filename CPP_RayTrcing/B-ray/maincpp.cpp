#include "svpng.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Mesh.h"
#include "Camera.h"
#include "Image.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Color ray_color(Ray& r,Mesh& obj) {
	if (obj.CheckIntersection(r) == true)
	{
		return obj.GetNormal()*0.5f+Vector3(0.5f,0.5f,0.5f);
	}
	Vector3 dir = r.GetDirection();
	auto t = (dir.y() + 1.0f)*0.5f;
	return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;
}

int main() {

	Mesh obj = ReadObjFile("C:\\Users\\huang\\Desktop\\Torus.obj");
	// Image
	Image image((16.0f/9.0f),400);
	//camera
	Camera mainCamera = Camera(Vector3(0,0,-6),-1,image.GetRatio());
	// Render

	return 0;
}
