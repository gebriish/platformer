#include "vector2.h"
#include <cmath>


namespace ENGINE::MATH {

	vector2 add(const vector2& a, const vector2& b)
	{
		return (vector2) {a.x + b.x , a.y + b.y};
	}

	vector2 sub(const vector2& a, const vector2& b)
	{
		return (vector2) {a.x - b.x , a.y - b.y};
	}
	
	vector2 lerp(const vector2& a, const vector2& b, float t)
	{
		return add (a , scale(sub(b, a), t));
	}

	vector2 scale(const vector2& v, float scalar)
	{
		return (vector2) {v.x * scalar , v.y * scalar};
	}

	f32 dot(const vector2& a, const vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	f32 length(const vector2& v)
	{
		return (f32) sqrt(dot(v,v));
	}

}