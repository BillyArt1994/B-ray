#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Mesh.h"
#include "Material.h"
#include "Light.h"
#include "Ray.h"

class GameObject
{
public:
	GameObject(Mesh* mesh, Material* material) : _mesh(mesh), _material(material) {
	}

	Mesh* GetMesh() const { return _mesh; }
	Material* GetMaterial() const { return _material; }

private:
	Mesh* _mesh;
	Color _diffuse = Color(1,0,1);
	Material* _material;
};

#endif // !GAMEOBJECT_H

