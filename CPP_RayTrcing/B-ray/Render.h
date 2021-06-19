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
	const int samples_per_pixel = 5;

	Render(Camera& mainCamera, Image& image, vector<GameObject>& worldObjet, Light& light) {
		unsigned char rgb[400 * 225 * 3], *p = rgb;
		int width = image.GetWidth();
		int height = image.GetHeight();
		Vector3 high_left_corner = mainCamera.GetLC();
		Vector3 horizontal = mainCamera.GetHorizontal();
		Vector3 vertical = mainCamera.GetVertical();
		Vector3 camerPos = mainCamera.GetPos();

		//建TM的树
		vector<Triangle> trig;
		for (int i = 0; i < worldObjet.size(); i++)
		{
			trig = worldObjet[i].GetMesh()->GetTriangle();
		}
		float maxDis = 0;
		for (int i = 0; i < trig.size(); i++)
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
		float size = CompareSize(mainCamera.GetPos());
		if (size > maxDis)
		{
			maxDis = size;
		}
		OcterTree root = OcterTree(trig, Vector3(0), maxDis, "",32, 20);


		for (int i = 0; i < height; i++) {

			for (int j = 0; j < width; j++) {
				auto u = (j) / (width - 1);
				auto v = (i) / (height - 1);
				Ray r(camerPos, (high_left_corner + horizontal * u - vertical * v - camerPos).normalize());
				Color pixel_color = ray_color(r, worldObjet,root);
				write_color(std::cout, pixel_color, samples_per_pixel);
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

private:

	void RenderTex(const unsigned image_width, const unsigned image_height, const unsigned char *rgb) {
		FILE *fp = fopen("render.png", "wb");
		svpng(fp, image_width, image_height, rgb, 0);
		fclose(fp);
	}

	Color ray_color(Ray& r, vector<GameObject>& worldObjet,OcterTree& root) {

		/*
		float minDis = FLT_MAX;
		int minIndex = -1;
		bool isHit = false;
		int objIndex = -1;
		*/
		float t = 0;
		bool ishit = root.Intersect(r, t);
		if (ishit ==true)
		{
			return Vector3(1,0,0);
		}
		else
		{
			return Vector3(0);
		}
		
#pragma region 传统遍历相交

		/*
		//遍历求交
		for (int i = 0; i < worldObjet.size(); i++)
		{
			vector<Triangle>* trig = &(worldObjet[i].GetMesh()->GetTriangle());
			for (int j = 0; j < trig->size(); j++)
			{
				Triangle* hitTrig = &(trig->at(j));
				if (hitTrig->IntersectTriangle(r) == true)
				{
					float dis = hitTrig->GetDis();
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
};

#endif // !RENDER_H

