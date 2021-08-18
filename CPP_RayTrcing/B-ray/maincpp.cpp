#include "svpng.h"
#include "Mesh.h"
#include "Scene.h"
#include "Camera.h"
#include "Render.h"
#include "Engine.h"
#include "Light.h"
#include "OBJLoader.h"
#include "RenderManager.h"
#include <iostream>
#include <chrono> 

int main() {
	//计时
	auto start = std::chrono::system_clock::now();

	//Light
	Light light(Color(1.0f, 1.0f, 1.0f), Vector3(2.0f, 3.0f, -5.0f), Vector3(0.0f));

	//Model
	GameObject* torusMesh  = new GameObject(OBJLoader::ReadObjectFile("Torus.obj"));

	//Image
	//输出图形比例-长比宽,尺寸
	InputManager inputManager((16.0f / 9.0f), 400);

	//camera
	Camera mainCamera(Vector3(0, 0, -6), -1, inputManager.aspect_ratio);

	//Scene
	Scene simpleScene("simpleScene");
	simpleScene.addLightElement(&light);
	simpleScene.addGameObjElement(torusMesh);
	simpleScene.mainCamera = &mainCamera;
	SceneManager sceneManger(&simpleScene);

	//Render
	RenderManager renderManager;
	
	//Engine
	Engine SSGE(renderManager, sceneManger, inputManager);

	if (!SSGE.StartUp())
	{
		printf("引擎启动失败......\n");
	}

	SSGE.run();

#pragma region 打印花费时间
	auto end = std::chrono::system_clock::now();
	double duration_second = std::chrono::duration<double>(end-start).count();
	std::cout << "渲染所花费时间：" << duration_second << "秒" << std::endl;
	return 0;
#pragma endregion

}
