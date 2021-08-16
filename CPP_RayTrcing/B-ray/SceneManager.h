#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include "Scene.h"
#include "OcterTree.h"

class SceneManager
{
public:

	SceneManager(Scene* m_scene):currentScene(m_scene){};
	~SceneManager() {};
	bool startUp();
	void shuDown();
	void updata();
	Scene* getCurrentScene();

private:
	Scene* currentScene;
};

bool SceneManager::startUp() {
	if (currentScene->checkEmptyScene())
	{
		printf("场景无任何对象\n");
		return false;
	}

	return true;
}
Scene* SceneManager::getCurrentScene() {
	return currentScene;
}

#endif // !SCENEMANAGER_H

