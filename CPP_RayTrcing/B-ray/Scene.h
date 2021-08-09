#ifndef SCENE_H
#define SCENE_H
#include <Vector>
#include "Mesh.h"

class Scene {
public:
	static std::vector<Mesh*> worldList;

	void addGameObject(Mesh* n_mesh);
};

void Scene::addGameObject(Mesh* n_mesh ) {
	worldList.push_back(n_mesh);
}

#endif // !SCENE_H

