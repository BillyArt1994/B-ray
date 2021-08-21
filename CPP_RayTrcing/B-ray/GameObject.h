#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Mesh.h"
#include "AABB.h"

class GameObject
{
public:
	GameObject(){}
	~GameObject();

	void buildBound();
	Mesh* mesh =nullptr;
	AABB* bound = nullptr;
	unsigned meshCount = 0;
};

void GameObject::buildBound() {
	AABB meshbound;
	Vector3 maxPoint(FLT_MIN), minPoint(FLT_MAX);
	for (size_t i = 0; i < meshCount; i++)
	{
		meshbound.buildAABB(&mesh[i]);
		maxPoint = Max(maxPoint, meshbound.maxPoint);
		minPoint = Min(minPoint, meshbound.minPoint);
	}
	bound = new AABB(maxPoint, minPoint);
}

GameObject::~GameObject() {

}

#endif // !GAMEOBJECT_H

