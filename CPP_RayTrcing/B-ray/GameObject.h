#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Mesh.h"

class GameObject
{
public:
	GameObject(Mesh* mesh) : _mesh(mesh){
	}

	Mesh* GetMesh() const { return _mesh; }

private:
	Mesh* _mesh;
	Color _diffuse = Color(1,0,1);
};

#endif // !GAMEOBJECT_H

