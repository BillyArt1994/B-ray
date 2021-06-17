#ifndef OcterTree_H
#define OcterTree_H
#include <Vector>
#include "Vector3.h"
#include "Triangle.h"
#include "AABB.h"
#include "Math.h"
#include <unordered_map>
using std::vector;

struct OcterNode
{
	vector<Triangle> data = { Triangle() };
	AABB box;
	OcterNode() {}
	OcterNode(vector<Triangle> trig, AABB abbox) :data(trig), box(abbox) {}
};

class OcterTree {
public:
	std::unordered_map<std::string, OcterNode* > localCode;
	int maxDepth = -1;
	int maximum = -1;
	OcterTree(vector<Triangle> t, Vector3 cp, float l, std::string dc, int md, int mi) :maxDepth(md), maximum(mi) { CreatTree(t, cp, l, dc); }

	void CreatTree(vector<Triangle> trig, Vector3 centerPoint, float length, std::string depthcode) {

		if (trig.empty())
		{
			return;
		}

		if (trig.size() <= maximum)
		{
			AABB box = AABB(centerPoint, length);
			OcterNode* node = new OcterNode(trig,box);
			localCode.insert({ depthcode,node });
			return;
		}

		if (depthcode.length() >= maxDepth)
		{
			AABB box = AABB(centerPoint, length);
			OcterNode* node = new OcterNode(trig, box);
			localCode.insert({ depthcode,node });
			return;
		}

		AABB Bounding(centerPoint, length);
		vector<Triangle> subTrig[8];
		vector<AABB> subBounding = Bounding.GetEightSubAABB();

		for (int i = 0; i < trig.size(); i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (isContain(trig.at(i), subBounding.at(j).GetMaxPoint(), subBounding.at(j).GetMinPoint()))
				{
					subTrig[j].push_back(trig.at(i));
				}
			}
		}

		CreatTree(subTrig[0], subBounding[0].centralPoint, subBounding[0].length, depthcode + "0");
		CreatTree(subTrig[1], subBounding[1].centralPoint, subBounding[1].length, depthcode + "1");
		CreatTree(subTrig[2], subBounding[2].centralPoint, subBounding[2].length, depthcode + "2");
		CreatTree(subTrig[3], subBounding[3].centralPoint, subBounding[3].length, depthcode + "3");
		CreatTree(subTrig[4], subBounding[4].centralPoint, subBounding[4].length, depthcode + "4");
		CreatTree(subTrig[5], subBounding[5].centralPoint, subBounding[5].length, depthcode + "5");
		CreatTree(subTrig[6], subBounding[6].centralPoint, subBounding[6].length, depthcode + "6");
		CreatTree(subTrig[7], subBounding[7].centralPoint, subBounding[7].length, depthcode + "7");
	}

	Vector3 Intersect(Ray r) {
		bool T = false;
		int B = -1;

		std::string codex = DecTiBin(r.GetOriginPos().x(), maxDepth);
		std::string codey = DecTiBin(r.GetOriginPos().y(), maxDepth);
		std::string codez = DecTiBin(r.GetOriginPos().z(), maxDepth);
		std::string qcode = "";

		for (int i = 0; i < maxDepth; i++)
		{
			int x = codex.at(i) - '0', y = codey.at(i) - '0', z = codez.at(i) - '0';
			qcode += std::to_string(x + 2 * y + 4 * z);
		}

		std::unordered_map<std::string, OcterNode* >::iterator mapIt;

		//最大匹配位置代码
		for (int i = qcode.length(); i > 0; i--)
		{
			std::string str = qcode.substr(0, i);
			mapIt = localCode.find(str);
			if (mapIt != localCode.end())
			{
				B = qcode.length() - i;
				if (B>= qcode.length())
				{
					return Vector3(0);
				}
				break;
			}

		}

		//匹配后检测此叶节点下 是否包含面片
		std::string qcodeR = qcode.substr(0, B);
		mapIt == localCode.find(qcodeR);
		vector<Triangle> trig = mapIt->second->data;
		if (trig.size() == 0)
		{
			AABB box = mapIt->second->box;
			float t = box.intersects(r);
			t += 0.99f;
			Ray rnew(r.RayRun(t), r.GetDirection());
			Intersect(rnew);
		}
		else
		{
			for (int i = 0; i < trig.size(); i++)
			{
				bool ishit = trig.at(i).IntersectTriangle(r);
				if (ishit)
				{
					return Vector3(1,0,0);
				}
				else
				{
					AABB box = mapIt->second->box;
					float t = box.intersects(r);
					t += 0.99f;
					Ray rnew(r.RayRun(t), r.GetDirection());
					Intersect(rnew);
				}
			}
		}
	}
};

#endif // OcterTree_H
