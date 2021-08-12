#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include "svpng.h"
#include "Color.h"
#include "Mesh.h"
#include "Ray.h"
#include "InputManager.h"

class Render
{
public:
	Render() {};
	Render(Camera* c, vector<Mesh*>& sML, vector<Light*>& sLL, InputManager& iM, unsigned char *p) :
		high_left_corner(c->high_left_corner), horizontal(c->horizontal), vertical(c->vertical),
		camerPos(c->cameraPosition), width(iM.image_width), height(iM.image_height),
		sceneMeshList(sML), sceneLightList(sLL), rgb(p) {}

	void Rendering();
	void SaveTexture();

private:
	unsigned char *rgb = nullptr;
	Vector3 high_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 camerPos;
	unsigned width;
	unsigned height;
	vector<Mesh*> sceneMeshList;
	vector<Light*> sceneLightList;
	Vector3 ray_color(const Ray& r);
};

void Render::Rendering() {
	unsigned char *p = rgb;
	for (unsigned i = 0; i < height; i++) {
		for (unsigned j = 0; j < width; j++) {
			float u = float(j) / (width - 1);
			float v = float(i) / (height - 1);
			Ray r(camerPos, ((high_left_corner + horizontal * u - vertical * v) - camerPos).normalize());
			Color pixel_color = write_color(ray_color(r));
			*p++ = (unsigned char)pixel_color.x;    //R
			*p++ = (unsigned char)pixel_color.y;    //G
			*p++ = (unsigned char)pixel_color.z;    //B
		}
		int rate = ((i/(height-1.0f))*100);
		std::cout << rate << "%" << std::endl;
	}
}

void Render::SaveTexture() {
	FILE *fp = fopen("render.png", "wb");
	svpng(fp, width, height, rgb, 0);
	fclose(fp);
}

Vector3 Render::ray_color(const Ray& r) {

#pragma region 传统全局遍历相交
	float minDis = FLT_MAX;
	int minIndex = -1;
	bool isHit = false;
	int objIndex = -1;

	for (int i = 0; i < sceneMeshList.size(); i++)
	{
		vector<Triangle>* trig = &(sceneMeshList[i]->triangleArray);
		for (int j = 0; j < trig->size(); j++)
		{
			float t;
			if (trig->at(j).IntersectTriangle(r, t) == true)
			{
				float dis = t;
				if (t < minDis)
				{
					minDis = dis;
					objIndex = i;
					minIndex = j;
					isHit = true;
				}
			}
		}
	}
	if (isHit == true)
	{
		return Color(1.0f, 0.0f, 0.0f);
	}
#pragma endregion
	float t = (r.GetDirection().y + 1.0f)*0.5f;
	return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;

}

#endif // !RENDER_H

