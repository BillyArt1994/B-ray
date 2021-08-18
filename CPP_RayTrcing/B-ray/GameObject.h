#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Mesh.h"
#include "AABB.h"

class GameObject
{
public:
	GameObject(){}
	~GameObject();
	GameObject(Mesh* mesh) : _mesh(mesh){
	}
	Mesh* getMesh() const { return _mesh; }
	AABB* getBound() const { return _bound; }
	void buildBound();
private:
	Mesh* _mesh = nullptr;
	AABB* _bound = nullptr;
};

void GameObject::buildBound() {
	_bound = new AABB();
	_bound->buildAABB(_mesh);
}

GameObject::~GameObject() {

}

#endif // !GAMEOBJECT_H

