#ifndef ENGINE_H
#define ENGINE_H
#include "SceneManager.h"
#include "RenderManager.h"
#include "InputManager.h"

class Engine {
public:
	Engine() {}
	~Engine() {}

	bool StartUp();
	void run();
	void shoutDown();

private:
	RenderManager renderManager;
	SceneManager sceneManager;
	InputManager inputManager;
};

bool Engine::StartUp() {
	sceneManager.startUp();
	inputManager.startUp(&sceneManager);
	renderManager.startUp(&inputManager, &sceneManager);
	printf("渲染系统启动成功\n");
	return true;
}

void Engine::run() {
	renderManager.run();
}

void Engine::shoutDown() {

}

#endif // !ENGINE_H

