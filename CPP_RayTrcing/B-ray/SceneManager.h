#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include "Scene.h"

class SceneManager
{
public:

	SceneManager(Scene* m_scene):currentScene(m_scene){};
	~SceneManager() {};
	bool startUp();
	Scene* getCurrentScene()const {	return currentScene;}
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


#endif // !SCENEMANAGER_H

