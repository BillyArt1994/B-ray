#include "svpng.h"
#include "Mesh.h"
#include "Scene.h"
#include "Image.h"
#include "Camera.h"
#include "Render.h"
#include "Light.h"
#include "OBJLoader.h"
#include <iostream>
#include <time.h>　

int main() {
	//计时
	clock_t start, end;
	start = clock();

	//Light
	Light light(Color(1.0f, 1.0f, 1.0f), Vector3(2.0f, 3.0f, -5.0f), Vector3(0.0f));

	//Model
	Mesh torusMesh = OBJLoader::ReadObjectFile("C:\\Users\\huang\\Desktop\\Torus.obj");

	//Scene
	//Scene::addGameObject(&torusMesh);

	//Image
	//输出图形比例-长比宽,尺寸
	Image image((16.0f / 9.0f), 400);

	//camera
	Camera mainCamera ( Vector3(0, 0, -6), -1, image.aspect_ratio);

	//Render
	Render r(mainCamera,image,torusMesh,light);
	r.Rendering();
	

#pragma region 打印花费时间
	end = clock();
	double spendTime = double(end - start) / CLOCKS_PER_SEC;
	int m = static_cast<int>(spendTime / 60);
	float s = static_cast<float> (static_cast<int>(spendTime)%60 + (spendTime - static_cast<int>(spendTime)));
	std::cout << "渲染所花费时间：" << m << "分" << s << "秒" << std::endl;
	return 0;
#pragma endregion

}
