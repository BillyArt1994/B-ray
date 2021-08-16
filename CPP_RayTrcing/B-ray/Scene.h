#ifndef SCENE_H
#define SCENE_H
#include <Vector>
#include "Mesh.h"
#include "Light.h"
#include "OcterTree.h"
#include "Camera.h"
#include "Math.h"
#include "AABB.h"
#include <string>
using std::vector;

class Scene {
public:
	Scene(std::string sceneID):name(sceneID){}
	Scene(){}
	~Scene();
	std::string name= "SimpleScene";
	vector<Mesh*> scene_MeshList;
	vector<Light*> scene_LightList;
	Camera *mainCamera =nullptr;
	OcterTree scene_OT;
	AABB scene_BoxBound;

	void addMeshElement(Mesh* n_mesh);
	void addLightElement(Light* n_light);
	bool checkEmptyScene();
	void buildOctree();
	void buildBound();
};

void Scene::addMeshElement(Mesh* n_mesh ) {
	scene_MeshList.push_back(n_mesh);
}

void Scene::addLightElement(Light* n_light) {
	scene_LightList.push_back(n_light);
}

bool Scene::checkEmptyScene() {
	if (scene_MeshList.size()==0 && scene_LightList.size()==0)
	{
		return true;
	}
	return false;
}

void Scene::buildOctree() {
	float maxValue = Max(Max(Abs(scene_BoxBound.minPoint.x), Abs(scene_BoxBound.maxPoint.x)),
				   Max(Abs(scene_BoxBound.minPoint.y), Abs(scene_BoxBound.maxPoint.y)),
				   Max(Abs(scene_BoxBound.minPoint.z), Abs(scene_BoxBound.maxPoint.z)));
	int length = Nearest2Power(static_cast<int>(maxValue));
	scene_OT = OcterTree(scene_MeshList,20, AABB(Vector3(length, length, length), Vector3(-length, -length, -length)));
	scene_OT.BuildTree();
}

void Scene::buildBound() {
	if (scene_MeshList.size()==1)
	{
		scene_BoxBound = *(scene_MeshList[0]->Bound);
	}
}

Scene::~Scene() {

}


#endif // !SCENE_H

