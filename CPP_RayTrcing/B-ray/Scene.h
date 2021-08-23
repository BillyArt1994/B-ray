#ifndef SCENE_H
#define SCENE_H
#include <Vector>
#include "Mesh.h"
#include "Light.h"
#include "OcterTree.h"
#include "OBJLoader.h"
#include "Camera.h"
#include "Math.h"
#include "AABB.h"
#include "GameObject.h"
#include <string>
using std::vector;

class Scene {
public:
	Scene(){}
	~Scene();
	std::string name= "SimpleScene";
	Mesh* scene_MeshList;
	unsigned meshCount = 0;
	vector<GameObject*> scene_GameObject;
	vector<Light*> scene_LightList;
	OcterTree scene_OT;
	AABB scene_BoxBound;
	Camera *mainCamera = nullptr;

	void addMeshElement(Mesh* n_mesh);
	void addGameObjElement(GameObject* n_gameObj);
	void addLightElement(Light* n_light);
	void buildOctree();
	void buildBound();
	void startUp();
};

void Scene::startUp() {
	mainCamera = new Camera(Vector3(0, 0, -6), -1, (16.0f / 9.0f));
	GameObject* gameObject = OBJLoader::ReadObjectFile("Torus.obj");
	addGameObjElement(gameObject);
	buildBound();
	buildOctree();
}

void Scene::addLightElement(Light* n_light) {
	scene_LightList.push_back(n_light);
}

void Scene::addGameObjElement(GameObject* n_gameObject) {
	scene_GameObject.push_back(n_gameObject);
	Mesh* mesh_ptr = n_gameObject->mesh;
	for (size_t i = 0; i < n_gameObject->meshCount; i++, *mesh_ptr++)
	{
		scene_MeshList=mesh_ptr;
		++meshCount;
	}
}

void Scene::buildOctree() {
	float maxValue = Max(Max(Abs(scene_BoxBound.minPoint.x), Abs(scene_BoxBound.minPoint.y), Abs(scene_BoxBound.minPoint.z)),
		Max(Abs(scene_BoxBound.maxPoint.x), Abs(scene_BoxBound.maxPoint.y), Abs(scene_BoxBound.maxPoint.z)));
	int length = Nearest2Power(static_cast<int>(maxValue));
	scene_OT = OcterTree(scene_MeshList,meshCount,20, AABB(Vector3(length, length, length), Vector3(-length, -length, -length)));
	scene_OT.BuildTree();
}

void Scene::buildBound() {
	Vector3 minP(FLT_MAX), maxP(-FLT_MAX);
	for (unsigned i = 0; i < scene_GameObject.size(); i++)
	{
		scene_GameObject[i]->buildBound();
		maxP = Max(maxP, scene_GameObject[i]->bound->maxPoint);
		minP = Min(minP, scene_GameObject[i]->bound->minPoint);
	};
	maxP = Max(maxP, mainCamera->cameraPosition);
	minP = Min(minP, mainCamera->cameraPosition);
	scene_BoxBound.maxPoint = maxP;
	scene_BoxBound.minPoint = minP;
}

Scene::~Scene() {

}


#endif // !SCENE_H

