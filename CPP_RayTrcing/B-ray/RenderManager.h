#ifndef RenderManager_H
#define RenderManager_H

#include "Render.h"
#include "InputManager.h"
#include "SceneManager.h"

class RenderManager
{
public:
	RenderManager() {};

	bool startUp(InputManager& iM, SceneManager& sM);
	void run();

private:
	Render m_renader;
	unsigned char *rgb =nullptr;
};

bool RenderManager::startUp(InputManager& iM, SceneManager& sM)
{
	unsigned width = iM.image_width;
	unsigned height = iM.image_height;
	rgb = new unsigned char[width*height*3];
	Camera* mainCamera = sM.getCurrentScene()->mainCamera;
	Vector3 high_left_corner = mainCamera->high_left_corner;
	Vector3 horizontal = mainCamera->horizontal;
	Vector3 vertical = mainCamera->vertical;
	Vector3 camerPos = mainCamera->cameraPosition;
	m_renader = Render(high_left_corner, horizontal, vertical,camerPos,width, height,sM.getCurrentScene()->sceneMeshList,sM.getCurrentScene()->sceneLightList, rgb);
	return true;
}

void RenderManager::run() {
	m_renader.Rendering();
	m_renader.SaveTexture();
}
#endif // !RenderManager
