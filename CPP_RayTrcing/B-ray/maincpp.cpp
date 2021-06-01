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

#include <time.h>¡¡

int main() {
	//¼ÆÊ±
	clock_t start, end;
	start = clock();
	//Light
	Light light(Color(1.0f, 1.0f, 1.0f), Vector3(2.0f, 3.0f, -5.0f), Vector3(0.0f));
	//Model
	Mesh tourMesh = ReadObjFile("C:\\Users\\billy\\Desktop\\Torus.obj");
	//Material
	Material mat1 = Material();
	//GameObject
	GameObject tours(&tourMesh, &mat1);
	//World GameObject
	vector<GameObject> worldList;
	worldList.push_back(tours);
	//Image
	Image image((16.0f / 9.0f), 400);
	//camera
	Camera mainCamera = Camera(Vector3(0, 0, -6), -1, image.GetRatio());
	//Render
	Render(mainCamera, image, worldList, light);

	end = clock();
	double spendTime = double(end - start) / CLOCKS_PER_SEC;
	int m = spendTime / 60;
	float s = (int)spendTime % 60+ (spendTime-(int)spendTime);
	std::cout << "time = " << m << "·Ö" << s << "Ãë" << std::endl;
	return 0;
}
