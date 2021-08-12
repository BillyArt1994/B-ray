#ifndef RenderManager_H
#define RenderManager_H

#include "Render.h"
#include "InputManager.h"
#include "SceneManager.h"

class RenderManager
{
public:
	RenderManager() {};
	~RenderManager();
	bool startUp(InputManager& iM, SceneManager& sM);
	void run();

private:
	Render* m_renader;
	unsigned char *rgb =nullptr;
};

bool RenderManager::startUp(InputManager& iM, SceneManager& sM)
{
	rgb = new unsigned char[iM.image_width *iM.image_height *3];
	m_renader = new Render((sM.getCurrentScene()->mainCamera),sM.getCurrentScene()->sceneMeshList,sM.getCurrentScene()->sceneLightList,iM, rgb);
	return true;
}

void RenderManager::run() {
	m_renader->Rendering();
	m_renader->SaveTexture();
}

RenderManager::~RenderManager() {
	delete m_renader;
	delete[] rgb;
}
#endif // !RenderManager
