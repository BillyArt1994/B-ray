#ifndef OcterTree_H
#define OcterTree_H

#include <Vector>
#include <array>
#include "Vector3.h"
#include "Mesh.h"
#include "Triangle.h"
#include "CharArray.h"
#include "NBHashMap.h"
#include "AABB.h"
#include "Math.h"
using std::vector;
using std::array;
using std::pair;

#define BitSize 32;

struct OcterNode
{
	OcterNode(vector<pair<unsigned, unsigned >> p, AABB b) :data(p), box(b) {}
	vector<pair<unsigned, unsigned >>data;
	AABB box;
};

class OcterTree {

private:
	NBhash_map<CharArray, OcterNode* > localCode;
	vector<Mesh*> meshList;
	unsigned maxOfTirg = -1;
	unsigned sceneSize = -1;
	unsigned gap = -1;
	AABB sceneBound;

	//获得场景中最大匹配编码
	NBhash_map<CharArray, OcterNode* >::iterator FindMaxMatch(CharArray qcode) {
		int i = 1;
		NBhash_map<CharArray, OcterNode* >::iterator result;
		while (i <= qcode.size)
		{
			CharArray c = qcode.subchar(i);
			result = localCode.find(c);
			if (result != localCode.end())
			{
				return result;
			}
			else
			{
				i++;
			}
		}
	}

	//获得坐标在空间中的编码
	CharArray EncodePosition(const Vector3& pos) {
		int x = floor(pos.x);
		int y = floor(pos.y);
		int z = floor(pos.z);

		CharArray result;
		for (unsigned i = 0; i < 32; i++)
		{
			unsigned  r = ((x >> i) & 1) + 2 * ((y >> i) & 1) + 4 * ((z >> i) & 1);
			result.addElement(r + '0', 31 - i);
		}
		return result;
	}

public:

	OcterTree(vector<Mesh*>& m_meshList, unsigned  m_maxfTrig, unsigned  m_sceneSize) :
		meshList(m_meshList), sceneSize(m_sceneSize), maxOfTirg(m_maxfTrig), gap(4294967296 / m_sceneSize) {}

	//构建树
	void BuildTree(vector<std::pair<unsigned, unsigned >> index, AABB bound, CharArray depthcode) {

		//三角面数量低于Maximum时设为叶节点并且存入哈希表中
		if (index.size() <= maxOfTirg)
		{
			OcterNode* node = new OcterNode(index, bound);
			localCode.insert({ depthcode,node });
			return;
		}

		//八叉树深度大于maxDepth时设为叶节点并且存入哈希表中
		if (depthcode.size >= 32)
		{
			OcterNode* node = new OcterNode(index, bound);
			localCode.insert({ depthcode,node });
			return;
		}

		array<AABB, 8> subBounding = sceneBound.getEightSubAABB();
		vector<std::pair<unsigned, unsigned >> subIndex[8];

		//所有三角面进行八叉树分割
		for (unsigned i = 0; i < index.size(); i++)
		{
			for (unsigned j = 0; j < 8; j++)
			{
				if (subBounding[j].checkIfInside(meshList[index[i].first]->triangleArray[index[i].second]))
				{
					subIndex[j].push_back(index[i]);
				}
			}
		}

		//迭代分割并进行编码
		if (depthcode.size >= 1)
		{
			BuildTree(subIndex[0], subBounding[0], depthcode + 7);
			BuildTree(subIndex[1], subBounding[1], depthcode + 6);
			BuildTree(subIndex[2], subBounding[2], depthcode + 5);
			BuildTree(subIndex[3], subBounding[3], depthcode + 4);
			BuildTree(subIndex[4], subBounding[4], depthcode + 3);
			BuildTree(subIndex[5], subBounding[5], depthcode + 2);
			BuildTree(subIndex[6], subBounding[6], depthcode + 1);
			BuildTree(subIndex[7], subBounding[7], depthcode + 0);
		}
		else
		{
			BuildTree(subIndex[0], subBounding[0], depthcode + 0);
			BuildTree(subIndex[1], subBounding[1], depthcode + 1);
			BuildTree(subIndex[2], subBounding[2], depthcode + 2);
			BuildTree(subIndex[3], subBounding[3], depthcode + 3);
			BuildTree(subIndex[4], subBounding[4], depthcode + 4);
			BuildTree(subIndex[5], subBounding[5], depthcode + 5);
			BuildTree(subIndex[6], subBounding[6], depthcode + 6);
			BuildTree(subIndex[7], subBounding[7], depthcode + 7);
		}
	}

	bool Intersect(Ray& r, float& t, unsigned& meshIndex, unsigned& tirgIndex) {
		Ray ray = r;

		while (true)
		{
			float t_Step = 0;

			//检测射线是否还在场景内部
			if (!sceneBound.checkIfInside(ray.GetOriginPos()))
			{
				return false;
			}

			//获得空间编码
			CharArray qcode = EncodePosition(ray.GetOriginPos()*gap);

			//最大匹配位置代码
			NBhash_map<CharArray, OcterNode* >::iterator mapIt = FindMaxMatch(qcode);
			if (mapIt != localCode.end())
			{
				//匹配后检测此叶节点下 是否包含面片
				vector<std::pair<unsigned, unsigned>> index = mapIt->second->data;
				//进行面片求交
				if (index.size())
				{
					float minDis = FLT_MAX;
					meshIndex = 0;
					tirgIndex = 0;

					for (unsigned i = 0; i < index.size(); i++)
					{
						unsigned m_Index = index.at(i).first;
						unsigned t_Index = index.at(i).second;
						Triangle* trig = &(meshList[m_Index]->triangleArray[t_Index]);
						if (trig->IntersectTriangle(r, t))
						{
							if (t < minDis)
							{
								minDis = t;
								meshIndex = m_Index;
								tirgIndex = t_Index;
							}
						}
					}

					if (minDis != FLT_MAX)
					{
						return true;
					}
				}
			}

			//当前射线并未求到交点，则与立方体网格求交并找到出口点添加1单位的扰动量穿越到下一个立方体网格中
			AABB box = mapIt->second->box;
			box.intersects(ray, t_Step);
			t_Step += 0.1f;
			ray = Ray(ray.RayRun(t_Step), ray.GetDirection());
		}
	}
};

#endif // OcterTree_H


