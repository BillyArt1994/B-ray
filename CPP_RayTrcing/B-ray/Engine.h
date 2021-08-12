#ifndef ENGINE_H
#define ENGINE_H
#include "SceneManager.h"
#include "RenderManager.h"
#include "InputManager.h"

class Engine {
public:

	Engine(RenderManager rM, SceneManager sM, InputManager iM):
		_renderManager(rM), _sceneManager(sM), _inputManager(iM){}
	~Engine() {}

	bool StartUp();
	void run();

private:
	RenderManager _renderManager;
	SceneManager _sceneManager;
	InputManager _inputManager;
};
void Engine::run() {
	_renderManager.run();
}

bool Engine::StartUp() {
	bool success = true;
	 if (!_sceneManager.startUp())
	 {
		 printf("场景系统加载失败.....\n");
	 }

	 if (!_renderManager.startUp(_inputManager, _sceneManager))
	 {
		 printf("渲染系统启动失败.....\n");
	 }

	 if (success)
	 {
		 printf("渲染系统启动成功\n");
	 }
	 return success;
}

#endif // !ENGINE_H

