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
	OcterNode(pair<unsigned, unsigned >* p, unsigned count, AABB& b) :data(p), dataCount(count), box(b) {}
	pair<unsigned, unsigned >* data;
	unsigned dataCount = 0;
	AABB box;
};

class OcterTree {

private:

	Mesh* meshList[36];
	unsigned meshCount = 0;
	unsigned maxOfTirg = 0;
	int gap = 0;
	AABB sceneBound;
	NBhash_map<OcterNode*> localCode;

	//获得场景中最大匹配编码
	OcterNode* FindMaxMatch(CharArray& qcode) {
		unsigned i(0);
		OcterNode* value = nullptr;
		do
		{
			++i;
		} while (!localCode.find(qcode.subchar(i), value));
		return value;
	}

	//获得坐标在空间中的编码
	CharArray EncodePosition(const Vector3& pos) {
		int x = static_cast<int>(floor(pos.x)),
			y = static_cast<int>(floor(pos.y)),
			z = static_cast<int>(floor(pos.z));

		char res[33]{ '\0' };
		for (int i = 31,j=0; i >= 0; --i,++j)
		{
			res[j] = ((x >> i)&1) + 2 * ((y >> i) & 1) + 4 * ((z >> i) & 1) + '0';
		}
		return res;
	}

	void octreeBuild(vector<std::pair<unsigned, unsigned >>& index, AABB& bound, CharArray depthcode) {

		unsigned length = index.size();
		//三角面数量低于Maximum时设为叶节点并且存入哈希表中
		if (length <= maxOfTirg)
		{
			std::pair<unsigned, unsigned>* p =new std::pair<unsigned, unsigned>[length];
			copy(index.begin(), index.end(), p);
			OcterNode* node = new OcterNode(p,length, bound);
			localCode.insert(depthcode,node);
			return;
		}

		//八叉树深度大于maxDepth时设为叶节点并且存入哈希表中
		if (depthcode.size >= 32)
		{
			std::pair<unsigned, unsigned>* p = new std::pair<unsigned, unsigned>[length];
			copy(index.begin(), index.end(), p);
			OcterNode* node = new OcterNode(p, length, bound);			
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
	OcterTree(vector<Mesh*> m_meshList, unsigned m_meshCount,unsigned m_maxfTrig, AABB& Bounding) :
		meshCount(m_meshCount),maxOfTirg(m_maxfTrig), sceneBound(Bounding),
		gap(static_cast<int>(2147483648 / Bounding.maxPoint.x)) {
		copy(m_meshList.begin(), m_meshList.end(), meshList);
	}

	//构建树
	void BuildTree() {
		localCode.tableInitialize();
		vector<std::pair<unsigned, unsigned >> trigIndex;
		unsigned faceCount = 0;
		for (unsigned i = 0; i < meshCount; i++)
		{
			faceCount = meshList[i]->getFaceCount();
			for (unsigned j = 0; j < faceCount; j++)
			{
				trigIndex.push_back({ i,j });
			}
		}
		CharArray code;
		octreeBuild(trigIndex, sceneBound, code);
	}

	bool Intersect(const Ray& r, float& t, unsigned& meshIndex, unsigned& tirgIndex) {

		Ray ray(r);
		OcterNode* node = nullptr;
		Triangle* trig = nullptr;
		CharArray qcode;
		unsigned m_Index(0), t_Index(0),length(0);
		float minDis(0.0f), t_Step(0.0f);

		while (true)
		{	//重置t_Step
			t_Step = 0;
			//检测射线是否还在场景内部
			if (!sceneBound.checkIfInside(ray.GetOriginPos()))
			{
				return false;
			}
			//获得空间编码
			qcode = EncodePosition(ray.GetOriginPos()*gap);
			//获得最大匹配位置代码
			node = FindMaxMatch(qcode);
			//匹配后检测此叶节点下 是否包含面片
			//进行面片求交
			length = node->dataCount;
			if (length)
			{
				minDis = FLT_MAX;
				meshIndex = 0;
				tirgIndex = 0;

				for (unsigned i = 0; i < length; i++)
				{
					m_Index = node->data[i].first;
					t_Index = node->data[i].second;
					if (meshList[m_Index]->triangleArray[t_Index].IntersectTriangle(r, t))
					{
						if (t < minDis)
						{
							minDis = t;
							meshIndex = m_Index;
							tirgIndex = t_Index;
						}
					}
				}
				if (minDis != FLT_MAX) return true;
			}
			//当前射线并未求到交点，则与立方体网格求交并找到出口点添加1单位的扰动量穿越到下一个立方体网格中
			node->box.intersects(ray, t_Step);
			ray = Ray(ray.RayRun(t_Step + 0.1f), ray.GetDirection());
		}

	}
};

#endif // OcterTree_H


