#ifndef FUNCTION_H
#define FUNCTION_H

#include <random>
#include "Math.h"

inline float random_float() {
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float clamp(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

int INTMaxAABB(vector<GameObject>& worldObjet) {
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
	return ceil(maxDis);
}

#endif // !FUNCTION_H
