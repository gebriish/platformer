#include "vec4.h"
#include <cmath>

vec4::vec4()
	: vec4(0.0, 0.0, 0.0, 0.0)
{}

vec4::vec4(float d)
	: vec4(d, d, d, d)
{}

vec4::vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{}


float dot(const vec4& a, const vec4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float length(const vec4& vec)
{
	return std::sqrt(dot(vec, vec));
}

vec4 normalize(const vec4& vec)
{
	return vec / length(vec);
}
