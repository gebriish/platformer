#include "vec2.h"
#include <cmath>

vec2::vec2()
	: vec2(0.0, 0.0)
{}

vec2::vec2(float d)
	: vec2(d, d)
{}

vec2::vec2(float x, float y)
	: x(x), y(y)
{}


float dot(const vec2& a, const vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

float length(const vec2& vec)
{
	return std::sqrt(dot(vec, vec));
}

vec2 normalize(const vec2& vec)
{
	return vec / length(vec);
}
