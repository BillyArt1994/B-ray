#ifndef SCENE_H
#define SCENE_H
#include <Vector>
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include <string>
using std::vector;

class Scene {
public:
	Scene(std::string sceneID):name(sceneID){}
	Scene(){}
	~Scene();
	std::string name= "SimpleScene";
	vector<Mesh*> sceneMeshList;
	vector<Light*> sceneLightList;
	Camera *mainCamera =nullptr;

	void addMeshElement(Mesh* n_mesh);
	void addLightElement(Light* n_light);

	bool checkEmptyScene();
};

void Scene::addMeshElement(Mesh* n_mesh ) {
	sceneMeshList.push_back(n_mesh);
}

void Scene::addLightElement(Light* n_light) {
	sceneLightList.push_back(n_light);
}

bool Scene::checkEmptyScene() {
	if (sceneMeshList.size()==0 && sceneLightList.size()==0)
	{
		return true;
	}
	return false;
}

Scene::~Scene() {

}
#endif // !SCENE_H

