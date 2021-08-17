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

struct OcterNode
{
	OcterNode(vector<pair<unsigned, unsigned >>& p, AABB& b) :data(p), box(b) {}
	vector<pair<unsigned, unsigned >>data;
	AABB box;
};

class OcterTree {

private:
	NBhash_map<OcterNode*> localCode;
	vector<Mesh*> meshList;
	unsigned maxOfTirg = -1;
	int gap = -1;
	AABB sceneBound;

	//获得场景中最大匹配编码
	bool FindMaxMatch(CharArray qcode, OcterNode* value) {
		unsigned i = 1;
		while (i <= qcode.size)
		{
			CharArray c = qcode.subchar(i);

			if (localCode.find(c, value))
			{
				return true;
			}
			else
			{
				i++;
			}
		}
		return false;
	}

	//获得坐标在空间中的编码
	CharArray EncodePosition(const Vector3& pos) {
		int x = static_cast<int>(floor(pos.x)),
			y = static_cast<int>(floor(pos.y)),
			z = static_cast<int>(floor(pos.z));

		CharArray result;
		unsigned  r;
		for (unsigned i = 0; i < 32; i++)
		{
			r = ((x >> i) & 1) + 2 * ((y >> i) & 1) + 4 * ((z >> i) & 1);
			result.addElement(r + '0', 31 - i);
		}
		return result;
	}

	void octreeBuild(vector<std::pair<unsigned, unsigned >>& index, AABB& bound, CharArray depthcode) {

		//三角面数量低于Maximum时设为叶节点并且存入哈希表中
		if (index.size() <= maxOfTirg)
		{
			OcterNode* node = new OcterNode(index, bound);
			localCode.insert(depthcode, node);
			return;
		}

		//八叉树深度大于maxDepth时设为叶节点并且存入哈希表中
		if (depthcode.size >= 32)
		{
			OcterNode* node = new OcterNode(index, bound);
			localCode.insert(depthcode, node);
			return;
		}

		array<AABB, 8> subBounding = bound.getEightSubAABB();
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
			octreeBuild(subIndex[0], subBounding[0], depthcode + 7);
			octreeBuild(subIndex[1], subBounding[1], depthcode + 6);
			octreeBuild(subIndex[2], subBounding[2], depthcode + 5);
			octreeBuild(subIndex[3], subBounding[3], depthcode + 4);
			octreeBuild(subIndex[4], subBounding[4], depthcode + 3);
			octreeBuild(subIndex[5], subBounding[5], depthcode + 2);
			octreeBuild(subIndex[6], subBounding[6], depthcode + 1);
			octreeBuild(subIndex[7], subBounding[7], depthcode + 0);
		}
		else
		{
			octreeBuild(subIndex[0], subBounding[0], depthcode + 0);
			octreeBuild(subIndex[1], subBounding[1], depthcode + 1);
			octreeBuild(subIndex[2], subBounding[2], depthcode + 2);
			octreeBuild(subIndex[3], subBounding[3], depthcode + 3);
			octreeBuild(subIndex[4], subBounding[4], depthcode + 4);
			octreeBuild(subIndex[5], subBounding[5], depthcode + 5);
			octreeBuild(subIndex[6], subBounding[6], depthcode + 6);
			octreeBuild(subIndex[7], subBounding[7], depthcode + 7);
		}
	}

public:

	OcterTree() {}
	OcterTree(vector<Mesh*>& m_meshList, unsigned m_maxfTrig, AABB& Bounding) :
		meshList(m_meshList), maxOfTirg(m_maxfTrig), sceneBound(Bounding),
		gap(static_cast<int>(2147483648 / Bounding.maxPoint.x)) {}

	//构建树
	void BuildTree() {
		vector<std::pair<unsigned, unsigned >> vertexIndex;
		unsigned vertexCount = 0;
		for (unsigned i = 0; i < meshList.size(); i++)
		{
			vertexCount = meshList[i]->getVertexCount();
			for (unsigned j = 0; j < vertexCount; j++)
			{
				vertexIndex.push_back({ i,j });
			}
		}
		CharArray code('0');
		octreeBuild(vertexIndex, sceneBound, code);
	}

	bool Intersect(const Ray& r, float& t, unsigned& meshIndex, unsigned& tirgIndex) {

		Ray ray = r;
		OcterNode* node = nullptr;
		CharArray qcode;
		vector<std::pair<unsigned, unsigned>>index;
		unsigned m_Index = -1;
		unsigned t_Index = -1;
		float minDis = 0.0f;
		Triangle* trig = nullptr;

		while (true)
		{
			float t_Step = 0;

			//检测射线是否还在场景内部
			if (!sceneBound.checkIfInside(ray.GetOriginPos()))
			{
				return false;
			}

			//获得空间编码
			qcode = EncodePosition(ray.GetOriginPos()*gap);

			//最大匹配位置代码

			if (FindMaxMatch(qcode, node))
			{
				index.swap(node->data);
				//匹配后检测此叶节点下 是否包含面片
				//进行面片求交
				if (index.size())
				{
					minDis = FLT_MAX;
					meshIndex = 0;
					tirgIndex = 0;

					for (unsigned i = 0; i < index.size(); i++)
					{
						m_Index = index.at(i).first;
						t_Index = index.at(i).second;
						trig = &(meshList[m_Index]->triangleArray[t_Index]);
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
			node->box.intersects(ray, t_Step);
			t_Step += 0.1f;
			ray = Ray(ray.RayRun(t_Step), ray.GetDirection());
		}
	}
};

#endif // OcterTree_H


