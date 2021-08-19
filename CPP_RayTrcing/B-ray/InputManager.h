#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "SceneManager.h"
#include "Camera.h"

struct InputManager
{
	InputManager(){}
	InputManager(float ar,int wd):aspect_ratio(ar), image_width(wd), image_height(static_cast<int>(wd/ ar)){}
	float aspect_ratio;
	unsigned image_width, image_height;

	void startUp(SceneManager* sceneManager);
};
void InputManager::startUp(SceneManager* sceneManager) {
	image_width = 400;
	image_height = static_cast<int>(400 / sceneManager->getCurrentScene()->mainCamera->aspect_ratio);
}

#endif // !IMAGE_H
