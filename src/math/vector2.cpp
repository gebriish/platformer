#include "vector2.h"
#include <cmath>


namespace ENGINE::MATH {
	
	vector2 lerp(const vector2& a, const vector2& b, float t)
	{
		return a + (b - a) * t;
	}

	f32 dot(const vector2& a, const vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	f32 length(const vector2& v)
	{
		return (f32) sqrt(dot(v,v));
	}

	vector2 normalize(const vector2& v)
	{
		if(v.x == 0 && v.y == 0) { return MATH::vector2{0.0f, 0.0f}; }

		f32 l = length(v);
		return v / l;
	}

}