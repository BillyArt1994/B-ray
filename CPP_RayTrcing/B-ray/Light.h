#ifndef LIGHT_H
#define LIGHT_H
#include "Vector3.h"
class Light
{
public:
	enum LightType
	{
		DirectionalLight
	};
	Light() {}
	Light(Color col,Vector3 pos,Vector3 rot):_Color(col),_position(pos),_roatiton(rot) {}
	Vector3 GetPos()const { return _position; }
	Vector3 GetRot()const { return _roatiton; }
	Vector3 GetCol()const { return _Color; }
private:
	Color _Color = Color(1.0f,1.0f,1.0f);
	Vector3 _position = Vector3(0.0f);
	Vector3 _roatiton = Vector3(0.0f);
};
#endif // !LIGHT_H

