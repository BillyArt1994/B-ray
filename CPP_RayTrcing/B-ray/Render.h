#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include "svpng.h"
#include "Camera.h"
#include "Image.h"
#include "Color.h"
#include "Ray.h"
#include "Mesh.h"
#include "GameObject.h"
#include "OcterTree.h"

class Render
{
public:
	Render(Camera& mainCamera, Image& image, vector<GameObject>& worldObjet, Light& light) {
		unsigned char rgb[400 * 225 * 3], *p = rgb;
		unsigned width = image.GetWidth();
		unsigned height = image.GetHeight();
		Vector3 high_left_corner = mainCamera.GetLC();
		Vector3 horizontal = mainCamera.GetHorizontal();
		Vector3 vertical = mainCamera.GetVertical();
		Vector3 camerPos = mainCamera.GetPos();

#pragma region 八叉树	
		int maxLength = INTMaxAABB(worldObjet, mainCamera);
		OcterTree root = OcterTree(worldObjet, maxLength*2,32,80);
#pragma endregion

#pragma region 射线求交并绘制颜色
		for (unsigned i = 0; i < height; i++) {

			for (unsigned j = 0; j < width; j++) {
				auto u = float(j) / (width - 1);
				auto v = float(i) / (height - 1);
				Ray r(camerPos, ((high_left_corner + horizontal * u - vertical * v) - camerPos).normalize());
				Color pixel_color = ray_color(r, worldObjet, root, light);
				write_color(std::cout, pixel_color);
				*p++ = (unsigned char)pixel_color.x();    //R
				*p++ = (unsigned char)pixel_color.y();    //G
				*p++ = (unsigned char)pixel_color.z();    //B
			}
			if (i % 2 == 0)
			{
				int rate = ceil(i*(100.0f / (height - 1)));
				std::cout << rate << "%" << std::endl;
			}
		}
		RenderTex(width, height, rgb);
	};
#pragma endregion

private:

	void RenderTex(const unsigned image_width, const unsigned image_height, const unsigned char *rgb) {
		FILE *fp = fopen("render.png", "wb");
		svpng(fp, image_width, image_height, rgb, 0);
		fclose(fp);
	}

	Color ray_color(Ray& r, vector<GameObject>& worldObjet, OcterTree& root, Light& light) {

		float t = 0;
		unsigned meshIndex = 0;
		unsigned tirgIndex = 0;
		bool ishit = root.Intersect(r, t,meshIndex,tirgIndex);
		if (ishit == true)
		{
			Vector3 normal = worldObjet[meshIndex].GetMesh()->GetTriangle()[tirgIndex].GetNormal();
			//Vector3 vertexPos = r.RayRun(t);
			//Material* metl = worldObjet[meshIndex].GetMaterial();
			//metl->SetLight(&light);
			//metl->SetNormal(normal);
			//metl->SetVertPos(vertexPos);
			//Color finalCol = metl->LambertModel();
			return normal;
		}
		else
		{
			Vector3 dir = r.GetDirection();
			auto t = (dir.y() + 1.0f)*0.5f;
			return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;
		}

#pragma region 传统全局遍历相交
		/*
		//遍历求交
		float minDis = FLT_MAX;
		int minIndex = -1;
		bool isHit = false;
		int objIndex = -1;

		for (int i = 0; i < worldObjet.size(); i++)
		{
			vector<Triangle>* trig = &(worldObjet[i].GetMesh()->GetTriangle());
			for (int j = 0; j < trig->size(); j++)
			{
				Triangle* hitTrig = &(trig->at(j));
				if (hitTrig->IntersectTriangle(r) == true)
				{
					float dis = hitTrig->GetRayDis();
					if (dis < minDis)
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
			Vector3 normal = worldObjet[objIndex].GetMesh()->GetTriangle()[minIndex].GetNormal();
			Vector3 vertexPos = r.RayRun(minDis);
			Material* metl = worldObjet[objIndex].GetMaterial();
			metl->SetLight(&light);
			metl->SetNormal(normal);
			metl->SetVertPos(vertexPos);
			Color finalCol = metl->LambertModel();
			return finalCol;
		}
		Vector3 dir = r.GetDirection();
		auto t = (dir.y() + 1.0f)*0.5f;
		return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;

		*/
#pragma endregion

	}

	int INTMaxAABB(vector<GameObject>& worldObjet, Camera camera) {
		float maxDis = 0;
		for (size_t i = 0; i < worldObjet.size(); i++)
		{
			vector<Triangle> trig = worldObjet[i].GetMesh()->GetTriangle();
			for (size_t i = 0; i < trig.size(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Vector3 v = trig.at(i).GetVertex(j)->position();
					float size = CompareSize(v);
					if (size > maxDis)
					{
						maxDis = size;
					}
				}
			}
		}

		float size = CompareSize(camera.GetPos());
		if (size > maxDis)
		{
			maxDis = size;
		}

		return ceil(maxDis);
	}
};

#endif // !RENDER_H

