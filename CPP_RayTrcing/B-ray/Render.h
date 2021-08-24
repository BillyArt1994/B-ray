#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include "svpng.h"
#include "Color.h"
#include "Mesh.h"
#include "Ray.h"
#include "InputManager.h"
#include "SceneManager.h"

class Render
{
public:
	Render(InputManager* iM,SceneManager* sM) :inputManager(iM), sceneManager(sM) {
		rgb =new unsigned char[inputManager->image_height*inputManager->image_width*3];
	}
	void Rendering();

private:
	unsigned char *rgb = nullptr;
	InputManager* inputManager = nullptr;
	SceneManager* sceneManager = nullptr;
	OcterTree* octerRoot = nullptr;
	void SaveTexture(unsigned wd, unsigned ht);
	Vector3 ray_color(const Ray& r, int depth);
};

void Render::Rendering() {
	unsigned height(inputManager->image_height),
			width(inputManager->image_width);
	unsigned char *p = rgb;
	Camera*camera = sceneManager->getCurrentScene()->mainCamera;
	Vector3 high_left_corner( camera->high_left_corner),
			horizontal(camera->horizontal),
			vertical (camera->vertical),
			camerPos (camera->cameraPosition);
	octerRoot = &sceneManager->getCurrentScene()->scene_OT;

	for (unsigned i = 0; i < height; i++) {
		for (unsigned j = 0; j < width; j++) {
			float u = float(j) / (width - 1);
			float v = float(i) / (height - 1);
			Vector3 pixelPos((high_left_corner + horizontal * u - vertical * v));
			Ray r(pixelPos, (pixelPos-camerPos).normalize());
			Color pixel_color = write_color(ray_color(r,50));
			*p++ = (unsigned char)pixel_color.x;    //R
			*p++ = (unsigned char)pixel_color.y;    //G
			*p++ = (unsigned char)pixel_color.z;    //B
		}
		int rate = static_cast<int>((i/(height-1.0f))*100);
		std::cout << rate << "%" << std::endl;
	}
	//保存图片
	SaveTexture(width,height);
}

void Render::SaveTexture(unsigned wd, unsigned ht) {
	FILE *fp = fopen("render.png", "wb");
	svpng(fp, wd, ht, rgb, 0);
	fclose(fp);
}

Color Render::ray_color(const Ray& r, int depth) {
	unsigned meshIndex = 0;
	unsigned trigIndex = 0;
	float t = 0.0f;

	if (depth <= 0)
		return Color(0.0f, 0.0f, 0.0f);

	if (octerRoot->Intersect(r, t, meshIndex, trigIndex))
	{
		Vector3 randomVector3 = random_in_unit_sphere();
		Vector3 target = r.GetOriginPos()+sceneManager->getCurrentScene()->scene_MeshList[meshIndex]->triangleArray[trigIndex].normal+ random_in_unit_sphere();
	//	Vector3 normal = sceneManager->getCurrentScene()->scene_MeshList[meshIndex]->triangleArray[trigIndex].normal;
		return 0.5f*ray_color(Ray(r.GetOriginPos(), target-r.GetOriginPos()), depth-1);
	//	return (normal*0.5f + 0.5f);
	}

/*
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
*/

	float bg_t = (r.GetDirection().normalize().y + 1.0f)*0.5f;
	return Color(1.0f, 1.0f, 1.0f)*(1.0f - bg_t) + Color(0.5f, 0.7f, 1.0f)*bg_t;
}



#endif // !RENDER_H

