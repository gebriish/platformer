#include "vec3.h"
#include <cmath>

vec3::vec3()
	: vec3(0.0, 0.0, 0.0)
{}

vec3::vec3(float d)
	: vec3(d, d, d)
{}

vec3::vec3(float x, float y, float z)
	: x(x), y(y), z(z)
{}


float dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(const vec3& vec)
{
	return std::sqrt(dot(vec, vec));
}

vec3 normalize(const vec3& vec)
{
	return vec / length(vec);
}

vec3 lerp(const vec3& a, const vec3& b, float t)
{
	return a + (b - a) * t;
}