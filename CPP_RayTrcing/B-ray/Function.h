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

#endif // !FUNCTION_H
