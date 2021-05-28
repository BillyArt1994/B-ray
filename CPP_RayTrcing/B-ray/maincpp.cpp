#include "svpng.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Mesh.h"
#include "Camera.h"
#include "Image.h"
#include "Render.h"
#include "Light.h"
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	Light light(Color(1, 1, 1), Vector3(0, 0, 0),Vector3());
	Mesh obj = ReadObjFile("C:\\Users\\huang\\Desktop\\Torus.obj");
	// Image
	Image image((16.0f/9.0f),400);
	//camera
	Camera mainCamera = Camera(Vector3(0,0,-6),-1,image.GetRatio());
	// Render
	Render(mainCamera,image,obj);
	return 0;
}
