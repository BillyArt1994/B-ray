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
#include <windows.h>

#define THREAD_NUM 5

class RenderParams {
public:
	int width = 0;
	int height = 0;
	unsigned char * startAddr = NULL;

	Vector3 camerPos = Vector3(0, 0, 0);
	Vector3 high_left_corner = Vector3(0, 0, 0);
	Vector3 horizontal = Vector3(0, 0, 0);
	Vector3 vertical = Vector3(0, 0, 0);

	vector<GameObject>* worldObjet = NULL;
	OcterTree* root = NULL;
	Light light = Light();

	RenderParams(int width, int height, unsigned char * startAddr,
		Vector3 camerPos, Vector3 high_left_corner, Vector3 horizontal, Vector3 vertical,
		vector<GameObject>* worldObjet, OcterTree* root, Light light):
		width(width), height(height), startAddr(startAddr), camerPos(camerPos), 
		high_left_corner(high_left_corner), horizontal(horizontal), vertical(vertical), 
		worldObjet(worldObjet), root(root), light(light) {}

	//RenderParams() {}
};

class Render
{
public:
	Render(Camera& mainCamera, Image& image, vector<GameObject>& worldObjet, Light& light) {
		unsigned char * rgb = (unsigned char *)malloc(400 * 225 * 3 * sizeof(char));
		unsigned char *p = rgb;
		int width = image.GetWidth();
		int height = image.GetHeight();
		Vector3 high_left_corner = mainCamera.GetLC();
		Vector3 horizontal = mainCamera.GetHorizontal();
		Vector3 vertical = mainCamera.GetVertical();
		Vector3 camerPos = mainCamera.GetPos();

#pragma region 八叉树	
		int maxLength = INTMaxAABB(worldObjet, mainCamera);
		OcterTree root = OcterTree(worldObjet, maxLength * 2, 12, 3);
#pragma endregion

		HANDLE hThread[THREAD_NUM];
		RenderParams* params[THREAD_NUM];
		for (int i = 0; i < THREAD_NUM; ++i) {
			params[i] = new RenderParams(width, height / THREAD_NUM, p + i * width * (height / THREAD_NUM) * 3 ,
								     camerPos, high_left_corner + i * vertical / THREAD_NUM, horizontal, vertical / THREAD_NUM, &worldObjet, &root, light);

			hThread[i] = CreateThread(NULL, 0, PartialRender, (LPDWORD)params[i], 0, NULL);
		}
		WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);

		for (int i = 0; i < THREAD_NUM; ++i) {
			delete params[i];
		}

		RenderTex(width, height, rgb);
	};

private:

	//线程函数
	static DWORD WINAPI PartialRender(LPVOID lpParameter)
	{
		struct RenderParams params = *(struct RenderParams *)lpParameter;
		unsigned char *p = params.startAddr;

		for (int i = 0; i < params.height; i++) {
			for (int j = 0; j < params.width; j++) {
				auto u = float(j) / params.width;
				auto v = float(i) / params.height;

				Ray r(params.camerPos, ((params.high_left_corner + params.horizontal * u - params.vertical * v) - params.camerPos).normalize());
				Color pixel_color = ray_color(r, *(params.worldObjet), *(params.root), params.light);
				write_color(std::cout, pixel_color);
				*p++ = (unsigned char)pixel_color.x();    //R
				*p++ = (unsigned char)pixel_color.y();    //G
				*p++ = (unsigned char)pixel_color.z();    //B
			}
		}
		return 0;
	}

	static void RenderTex(const unsigned image_width, const unsigned image_height, const unsigned char *rgb) {
		FILE *fp = fopen("render.png", "wb");
		svpng(fp, image_width, image_height, rgb, 0);
		fclose(fp);
	}

	static Color ray_color(Ray& r, vector<GameObject>& worldObjet, OcterTree& root, Light& light) {
		float t = 0;
		int index = 0;
		bool ishit = root.Intersect(r, t, index);

		if (ishit == true)
		{
			return Vector3(1, 0, 0);
		}
		else
		{
			Vector3 dir = r.GetDirection();
			auto t = (dir.y() + 1.0f)*0.5f;
			return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;
		}

#pragma region 传统遍历相交
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

	static int INTMaxAABB(vector<GameObject>& worldObjet, Camera camera) {
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

