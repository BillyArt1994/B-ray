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

	Color GetLightModel(Light* light, Ray& r) {
		if (_mesh->CheckIntersection(r))
		{
			_material->SetLight(light);
			_material->SetNV(_mesh);
			_diffuse = _material->LambertModel();
		}
		else
		{
			_diffuse = Color(1, 0, 1);
		}
		return _diffuse;
	}

private:
	Mesh* _mesh;
	Color _diffuse = Color(1,0,1);
	Material* _material;
};

#endif // !GAMEOBJECT_H

