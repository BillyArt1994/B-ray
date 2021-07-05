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
#include <time.h>　

int main() {
	//计时
	clock_t start, end;
	start = clock();

	//Light
	Light light(Color(1.0f, 1.0f, 1.0f), Vector3(2.0f, 3.0f, -5.0f), Vector3(0.0f));

	//Model
	Mesh torusMesh = ReadObjFile("C:\\Users\\huang\\Desktop\\Torus.obj");
	//Mesh Box_BigMesh = ReadObjFile("C:\\Users\\huang\\Desktop\\Box_Big.obj");
	//Mesh Box_SmallMesh = ReadObjFile("C:\\Users\\huang\\Desktop\\Box_Small.obj");

	//Material
	Material mat1 = Material(Color(1.0f, 1.0f, 1.0f));
	//Material mat2 = Material(Color(0.5f, 1.0f, 1.0f));
	//Material mat3 = Material(Color(1.0f, 0.5f, 1.0f));

	//GameObject
	GameObject torus(&torusMesh,&mat1);
	//GameObject Box_Big(&Box_BigMesh, &mat2);
	//GameObject Box_Small(&Box_SmallMesh, &mat3);

	//World GameObject
	vector<GameObject> worldList;
	worldList.push_back(torus);
	//worldList.push_back(Box_Big);
	//worldList.push_back(Box_Small);

	//Image
	Image image((16.0f / 9.0f), 400);

	//camera
	Camera mainCamera = Camera(Vector3(0, 0, -6), -1, image.GetRatio());

	//Render
	Render(mainCamera, image, worldList, light);

#pragma region 打印花费时间
	end = clock();
	double spendTime = double(end - start) / CLOCKS_PER_SEC;
	int m = spendTime / 60;
	float s = (int)spendTime % 60 + (spendTime - (int)spendTime);
	std::cout << "time = " << m << "分" << s << "秒" << std::endl;
	return 0;
#pragma endregion

}
