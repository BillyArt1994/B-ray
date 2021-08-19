#ifndef RenderManager_H
#define RenderManager_H

#include "Render.h"
#include "InputManager.h"
#include "SceneManager.h"

class RenderManager
{
public:
	RenderManager(){}
	~RenderManager();
	void startUp(InputManager* iM,SceneManager* sM);
	void run();

private:
	Render* m_renader;
};

void RenderManager::startUp(InputManager* iM, SceneManager* sM)
{
	m_renader = new Render(iM,sM);
}

void RenderManager::run() {
	m_renader->Rendering();
}

RenderManager::~RenderManager() {
}
#endif // !RenderManager
