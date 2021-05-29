#include "svpng.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Mesh.h"
#include "Camera.h"
#include "Image.h"
#include "Render.h"
#include "Light.h"
#include "Material.h"
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	//Light
	Light light(Color(1.0f, 1.0f, 1.0f), Vector3(2.0f, 3.0f, 0.0f),Vector3(0.0f));
	//Model
	Mesh tourMesh = ReadObjFile("C:\\Users\\huang\\Desktop\\box.obj");
	//Material
	Material mat1 = Material();
	//GameObject
	GameObject tours(&tourMesh,&mat1);
	//Image
	Image image((16.0f/9.0f),400);
	//camera
	Camera mainCamera = Camera(Vector3(0,0,-6),-1,image.GetRatio());
	//Render
	Render(mainCamera,image, tours,light);

	return 0;
}
