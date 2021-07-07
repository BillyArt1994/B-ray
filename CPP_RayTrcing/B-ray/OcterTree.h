#ifndef OcterTree_H
#define OcterTree_H
#include <Vector>
#include "Vector3.h"
#include "Triangle.h"
#include "AABB.h"
#include "Math.h"
using std::vector;

#include "sparsehash/dense_hash_map"
using google::dense_hash_map;

struct OcterNode
{
	vector<std::pair<int, int>>data;
	AABB box;
	OcterNode() {}
	OcterNode(vector<std::pair<int, int>>index, AABB abbox) :data(index), box(abbox) {}
};

class OcterTree {

private:
	//获得场景中最大匹配编码
	dense_hash_map<std::string, OcterNode* >::iterator FindMaxMatch(std::string qcode) {
		dense_hash_map<std::string, OcterNode* >::iterator result;
		dense_hash_map<std::string, OcterNode* >::iterator mapIt = localCode.end();

		int a = 0;
		int b = qcode.length();
		int i = (a + b) / 2;

		while (a < b - 1)
		{
			std::string str = qcode.substr(0, i);
			result = localCode.find(str);
			if (result != localCode.end())
			{
				mapIt = result;
				a = i;
				i = (a + b) / 2;
			}
			else
			{
				b = i;
				i = (a + b) / 2;
			}
		}
		return result;
	}

	//获得空间编码
	std::string EncodePosition(const Vector3 pos, const int bits) {
		int x = floor(pos.x());
		int y = floor(pos.y());
		int z = floor(pos.z());

		char result[33];
		for (int i =0 ; i < bits; i++)
		{
			int r = ((x >> i) & 1) + 2 * ((y >> i) & 1) + 4 * ((z >> i) & 1);
			result[31-i] = r + '0';
		}
		result[bits] = '\0';
		return std::string(result);
	}

public:
	dense_hash_map<std::string, OcterNode* > localCode;
	vector<GameObject>& world;
	int maxDepth = -1;
	int maximum = -1;
	int length = 0;

	OcterTree(vector<GameObject>& t, int l, int md, int mi) :
		world(t), maxDepth(md), maximum(mi), length(l) {

		localCode.set_empty_key(std::string(""));
		vector<std::pair<int, int>> index;
		for (int i = 0; i < world.size(); i++)
		{
			for (int j = 0; j < world.at(i).GetMesh()->GetTriangle().size(); j++)
			{
				index.push_back(std::pair<int, int>(i, j));
			}
		}
		CreatTree(index, Vector3(0), INT_MAX, "");
	}

	void CreatTree(vector<std::pair<int, int>> index, Vector3 centerPoint, int length, std::string depthcode) {

		if (index.size() <= maximum)
		{
			AABB box = AABB(centerPoint, length);
			OcterNode* node = new OcterNode(index, box);
			localCode.insert({ depthcode,node });
			return;
		}

		if (depthcode.length() >= maxDepth)
		{
			AABB box = AABB(centerPoint, length);
			OcterNode* node = new OcterNode(index, box);
			localCode.insert({ depthcode,node });
			return;
		}

		AABB Bounding(centerPoint, length);
		vector<AABB> subBounding = Bounding.GetEightSubAABB();
		vector<std::pair<int, int>> subIndex[8];

		for (int i = 0; i < index.size(); i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (isContain(world.at(index.at(i).first).GetMesh()->GetTriangle().at(index.at(i).second), subBounding.at(j).GetMaxPoint(), subBounding.at(j).GetMinPoint()))
				{
					subIndex[j].push_back(index.at(i));
				}
			}
		}

		if (depthcode.size() >= 1)
		{
			CreatTree(subIndex[0], subBounding[0].centralPoint, subBounding[0].length, depthcode + "7");
			CreatTree(subIndex[1], subBounding[1].centralPoint, subBounding[1].length, depthcode + "6");
			CreatTree(subIndex[2], subBounding[2].centralPoint, subBounding[2].length, depthcode + "5");
			CreatTree(subIndex[3], subBounding[3].centralPoint, subBounding[3].length, depthcode + "4");
			CreatTree(subIndex[4], subBounding[4].centralPoint, subBounding[4].length, depthcode + "3");
			CreatTree(subIndex[5], subBounding[5].centralPoint, subBounding[5].length, depthcode + "2");
			CreatTree(subIndex[6], subBounding[6].centralPoint, subBounding[6].length, depthcode + "1");
			CreatTree(subIndex[7], subBounding[7].centralPoint, subBounding[7].length, depthcode + "0");
		}
		else
		{
			CreatTree(subIndex[0], subBounding[0].centralPoint, subBounding[0].length, depthcode + "0");
			CreatTree(subIndex[1], subBounding[1].centralPoint, subBounding[1].length, depthcode + "1");
			CreatTree(subIndex[2], subBounding[2].centralPoint, subBounding[2].length, depthcode + "2");
			CreatTree(subIndex[3], subBounding[3].centralPoint, subBounding[3].length, depthcode + "3");
			CreatTree(subIndex[4], subBounding[4].centralPoint, subBounding[4].length, depthcode + "4");
			CreatTree(subIndex[5], subBounding[5].centralPoint, subBounding[5].length, depthcode + "5");
			CreatTree(subIndex[6], subBounding[6].centralPoint, subBounding[6].length, depthcode + "6");
			CreatTree(subIndex[7], subBounding[7].centralPoint, subBounding[7].length, depthcode + "7");
		}
	}

	bool Intersect(Ray& r, float& t, int& indexMesh) {

		AABB root = AABB(Vector3(0), length);
		Ray ray = r;
		while (true)
		{
			float tStep = 0;
			if (isInside(&ray.GetOriginPos(), root.maxPoint, root.minPoint) == false)
			{
				return false;
			}

			Vector3 rp = ray.GetOriginPos();

			//获得空间编码
			std::string qcode =EncodePosition(rp, maxDepth);

			//最大匹配位置代码
			dense_hash_map<std::string, OcterNode* >::iterator mapIt = FindMaxMatch(qcode);

			if (mapIt != localCode.end())
			{
				//匹配后检测此叶节点下 是否包含面片
				vector<std::pair<int, int>> index = mapIt->second->data;

				if (index.size() != 0)
				{
					for (int i = 0; i < index.size(); i++)
					{
						Triangle trig = world.at(index.at(i).first).GetMesh()->GetTriangle().at(index.at(i).second);
						bool ishit = trig.IntersectTriangle(r, t);
						if (ishit)
						{
							indexMesh = index.at(i).first;
							return true;
						}
					}
				}

			}
			AABB box = mapIt->second->box;
			box.intersects(ray, tStep);
			tStep += 1;
			ray = Ray(ray.RayRun(tStep), ray.GetDirection());
		}
	}

};

#endif // OcterTree_H


