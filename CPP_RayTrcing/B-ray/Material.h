#ifndef MATERIAL_H
#define MATERIAL_H
#include "Vector3.h"
#include "Mesh.h"
#include "Light.h"

class Material
{
public:
	Material(){}

	Color LambertModel() {
		Vector3 lightDir =(*_lightPos - *_vertexPos).normalize();
		return *_normal*0.5+Vector3(0.5);//dot(*_normal, lightDir);
	}

	void SetNV(Mesh* mesh) {
		_normal = &mesh->GetNormal();
		_vertexPos = &mesh->GetVertex();
	}

	void SetLight(Light* light) {
		_lightPos = &light->GetPos();
	}

private:
	Vector3* _normal;
	Vector3* _lightPos;
	Vector3* _vertexPos;
};

#endif // !MATERIAL_H

