#ifndef OcterTree_H
#define OcterTree_H
#include <Vector>
#include "Vector3.h"
#include "Triangle.h"
#include "CharArray.h"
#include "AABB.h"
#include "Math.h"
using std::vector;

#include "sparsehash/dense_hash_map"
using google::dense_hash_map;

struct OcterNode
{
	vector<std::pair<unsigned, unsigned >>data;
	AABB box;
	OcterNode() {}
	OcterNode(vector<std::pair<unsigned, unsigned >>index, AABB abbox) :data(index), box(abbox) {}
};

class OcterTree {

private:
	//获得场景中最大匹配编码
	dense_hash_map<CharArray, OcterNode* >::iterator FindMaxMatch(CharArray qcode) {

#pragma region 二分法
		//dense_hash_map<CharArray, OcterNode* >::iterator result;
		//dense_hash_map<CharArray, OcterNode* >::iterator mapIt = localCode.end();

		//int a = 0;
		//int b = qcode.size;
		//int i = (a + b) / 2;

		//while (a < b - 1)
		//{
		//	CharArray c = qcode.subchar(i);
		//	result = localCode.find(c);
		//	if (result != localCode.end())
		//	{
		//		mapIt = result;
		//		a = i;
		//		i = (a + b) / 2;
		//	}
		//	else
		//	{
		//		b = i;
		//		i = (a + b) / 2;
		//	}
		//}
		//	return result;
#pragma endregion
		int i = qcode.size;
		dense_hash_map<CharArray, OcterNode* >::iterator result;
		while (i > 0)
		{
			CharArray c = qcode.subchar(i);
			result = localCode.find(c);
			if (result != localCode.end())
			{
				return result;
			}
			else
			{
				i--;
			}
		}
	}

	//获得坐标在空间中的编码
	CharArray EncodePosition(const Vector3& pos, const unsigned  bits) {
		int x = floor(pos.x());
		int y = floor(pos.y());
		int z = floor(pos.z());

		CharArray result;
		for (unsigned i = 0; i < bits; i++)
		{
			unsigned  r = ((x >> i) & 1) + 2 * ((y >> i) & 1) + 4 * ((z >> i) & 1);
			result.addElement(r + '0', bits - 1 - i);
		}
		return result;
	}

public:
	dense_hash_map<CharArray, OcterNode* > localCode;
	vector<GameObject>& world;
	unsigned maxDepth = -1;
	unsigned maximum = -1;
	unsigned length = -1;
	OcterTree(vector<GameObject>& t, unsigned  l, unsigned  md, unsigned  mi) :
		world(t), length(l), maxDepth(md), maximum(mi)
	{

		localCode.set_empty_key(CharArray());
		vector<std::pair<unsigned, unsigned >> index;

		for (unsigned i = 0; i < world.size(); i++)
		{
			for (unsigned j = 0; j < world.at(i).GetMesh()->GetTriangle().size(); j++)
			{
				index.push_back(std::pair<int, int>(i, j));
			}
		}

		CreatTree(index, Vector3(0), UINT_MAX, CharArray());
	}

	void CreatTree(vector<std::pair<unsigned, unsigned >> index, Vector3 centerPoint, float length, CharArray depthcode) {

		//三角面数量低于Maximum时设为叶节点并且存入哈希表中
		if (index.size() <= maximum)
		{
			AABB box = AABB(centerPoint, length);
			OcterNode* node = new OcterNode(index, box);
			localCode.insert({ depthcode,node });
			return;
		}

		//八叉树深度大于maxDepth时设为叶节点并且存入哈希表中
		if (depthcode.size >= maxDepth)
		{
			AABB box = AABB(centerPoint, length);
			OcterNode* node = new OcterNode(index, box);
			localCode.insert({ depthcode,node });
			return;
		}

		AABB Bounding(centerPoint, length);
		vector<AABB> subBounding = Bounding.GetEightSubAABB();
		vector<std::pair<unsigned, unsigned >> subIndex[8];

		//所有三角面进行八叉树分割
		for (unsigned i = 0; i < index.size(); i++)
		{
			for (unsigned j = 0; j < 8; j++)
			{
				if (isContain(world.at(index.at(i).first).GetMesh()->GetTriangle().at(index.at(i).second), subBounding.at(j).GetMaxPoint(), subBounding.at(j).GetMinPoint()))
				{
					subIndex[j].push_back(index.at(i));
				}
			}
		}

		//迭代分割并进行编码
		if (depthcode.size >= 1)
		{
			CreatTree(subIndex[0], subBounding[0].centralPoint, subBounding[0].length, depthcode + 7);
			CreatTree(subIndex[1], subBounding[1].centralPoint, subBounding[1].length, depthcode + 6);
			CreatTree(subIndex[2], subBounding[2].centralPoint, subBounding[2].length, depthcode + 5);
			CreatTree(subIndex[3], subBounding[3].centralPoint, subBounding[3].length, depthcode + 4);
			CreatTree(subIndex[4], subBounding[4].centralPoint, subBounding[4].length, depthcode + 3);
			CreatTree(subIndex[5], subBounding[5].centralPoint, subBounding[5].length, depthcode + 2);
			CreatTree(subIndex[6], subBounding[6].centralPoint, subBounding[6].length, depthcode + 1);
			CreatTree(subIndex[7], subBounding[7].centralPoint, subBounding[7].length, depthcode + 0);
		}
		else
		{
			CreatTree(subIndex[0], subBounding[0].centralPoint, subBounding[0].length, depthcode + 0);
			CreatTree(subIndex[1], subBounding[1].centralPoint, subBounding[1].length, depthcode + 1);
			CreatTree(subIndex[2], subBounding[2].centralPoint, subBounding[2].length, depthcode + 2);
			CreatTree(subIndex[3], subBounding[3].centralPoint, subBounding[3].length, depthcode + 3);
			CreatTree(subIndex[4], subBounding[4].centralPoint, subBounding[4].length, depthcode + 4);
			CreatTree(subIndex[5], subBounding[5].centralPoint, subBounding[5].length, depthcode + 5);
			CreatTree(subIndex[6], subBounding[6].centralPoint, subBounding[6].length, depthcode + 6);
			CreatTree(subIndex[7], subBounding[7].centralPoint, subBounding[7].length, depthcode + 7);
		}
	}

	bool Intersect(Ray& r, float& t, unsigned & meshIndex, unsigned& tirgIndex) {

		AABB root = AABB(Vector3(0), length);
		Ray ray = r;

		while (true)
		{
			float tStep = 0;

			//检测射线是否还在场景内部
			if (isInside(&ray.GetOriginPos(), root.maxPoint, root.minPoint) == false)
			{
				return false;
			}

			//获得空间编码
			CharArray qcode = EncodePosition(ray.GetOriginPos(), maxDepth);

			//最大匹配位置代码
			dense_hash_map<CharArray, OcterNode* >::iterator mapIt = FindMaxMatch(qcode);

			if (mapIt != localCode.end())
			{
				//匹配后检测此叶节点下 是否包含面片
				vector<std::pair<unsigned, unsigned>> index = mapIt->second->data;

				//进行面片求交
				if (index.size() != 0)
				{
					float minDis = FLT_MAX;
					meshIndex = 0;
					tirgIndex = 0;
					for (unsigned i = 0; i < index.size(); i++)
					{
						unsigned mIndex = index.at(i).first;
						unsigned tIndex = index.at(i).second;
						Triangle* trig = &(world.at(mIndex).GetMesh()->GetTriangle().at(tIndex));
						if (trig->IntersectTriangle(r, t))
						{
							if (t< minDis)
							{
								minDis = t;
								meshIndex = mIndex;
								tirgIndex = tIndex;
							}
						}
					}

					if (minDis!= FLT_MAX)
					{
						return true;
					}

				}
			}

			//当前射线并未求到交点，则与立方体网格求交并找到出口点添加1单位的扰动量穿越到下一个立方体网格中
			AABB box = mapIt->second->box;
			box.intersects(ray, tStep);
			tStep += 1;
			ray = Ray(ray.RayRun(tStep), ray.GetDirection());
		}
	}

};

#endif // OcterTree_H


