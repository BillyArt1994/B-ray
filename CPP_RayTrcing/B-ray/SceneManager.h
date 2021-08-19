#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include "Scene.h"
#include "OcterTree.h"

class SceneManager
{
public:
	SceneManager() {}
	SceneManager(Scene* m_scene):currentScene(m_scene){};
	~SceneManager() {};
	void startUp();
	void shutDown();
	void updata();
	Scene* getCurrentScene ()const;

private:
	Scene* currentScene;
};

void SceneManager::startUp() {
	currentScene = new Scene();
	currentScene->startUp();
}

Scene* SceneManager::getCurrentScene()const{
	return currentScene;
}

void SceneManager::shutDown() {

}

#endif // !SCENEMANAGER_H

