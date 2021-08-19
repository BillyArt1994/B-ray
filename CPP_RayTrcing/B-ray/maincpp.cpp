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
	
	//Engine
	Engine SSGE;
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
