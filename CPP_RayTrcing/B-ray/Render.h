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

class Render
{
public:
	Render(Camera& mainCamera, Image& image, vector<GameObject>& worldObjet, Light& light) {
		unsigned char rgb[400 * 225 * 3], *p = rgb;
		int width = image.GetWidth();
		int height = image.GetHeight();
		Vector3 high_left_corner = mainCamera.GetLC();
		Vector3 horizontal = mainCamera.GetHorizontal();
		Vector3 vertical = mainCamera.GetVertical();
		Vector3 camerPos = mainCamera.GetPos();
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				auto u = double(j) / (width - 1);
				auto v = double(i) / (height - 1);
				Ray r(camerPos, (high_left_corner + horizontal * u - vertical * v - camerPos).normalize());
				Color pixel_Color = ray_color(r, worldObjet, light);
				write_color(std::cout, pixel_Color);

				*p++ = (unsigned char)pixel_Color.x();    //R
				*p++ = (unsigned char)pixel_Color.y();    //G
				*p++ = (unsigned char)pixel_Color.z();    //B
			}

			if (i % 22 == 0)
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

	Color ray_color(Ray& r, vector<GameObject>& worldObjet, Light& light) {

		vector<Triangle*> allTriangle;
		vector<Material*> allMaterial;
		for (int i = 0; i < worldObjet.size(); i++)
		{
			vector<Triangle> *temp = &(worldObjet[i].GetMesh()->GetTriangle());
			allTriangle.insert(allTriangle.end(), temp->begin(), temp->end());
			allMaterial.push_back(worldObjet[i].GetMaterial());
		}

		for (int i = 0; i < allTriangle.size(); i++)
		{
			float minDis = FLT_MAX;
			int minIndex = -1;
			bool isHit = false;
			Triangle* trig = allTriangle[i];
			if (trig->IntersectTriangle(r) == true)
			{
				float dis = trig->GetDis();
				if (dis < minDis)
				{
					minDis = dis;
					minIndex = i;
					isHit = true;
				}
			}
		}

		Vector3 dir = r.GetDirection();
		auto t = (dir.y() + 1.0f)*0.5f;
		return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;
	}
};

#endif // !RENDER_H

