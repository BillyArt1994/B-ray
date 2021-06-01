#ifndef MATERIAL_H
#define MATERIAL_H
#include <iostream>
#include "Vector3.h"
#include "Mesh.h"
#include "Light.h"
#include <cmath>
#include <algorithm>

class Material
{
public:
	Material(){}

	Color LambertModel() {
		Vector3 lightDir =(_lightPos - _vertexPos).normalize();
		return std::max(dot(_normal, lightDir), 0.0f) ;
	}

	void SetNormal(Vector3& normal) {
		_normal = normal;
	}

	void SetVertPos(Vector3& vertPos) {
		_vertexPos = vertPos;
	}

	void SetLight(Light* light) {
		_lightPos = light->GetPos();
	}

private:
	Vector3 _normal;
	Vector3 _lightPos;
	Vector3 _vertexPos;
};

#endif // !MATERIAL_H

