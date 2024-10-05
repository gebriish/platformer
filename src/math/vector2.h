#pragma once
#include "types.h"

namespace ENGINE::MATH
{
	struct vector2 {
		f32 x, y;
	};

	vector2 add(const vector2& a, const vector2& b);
	vector2 sub(const vector2& a, const vector2& b);
	vector2 lerp(const vector2& a, const vector2& b, float t);
	vector2 scale(const vector2& v, float scalar);
	f32 dot(const vector2& a, const vector2& b);
	f32 length(const vector2& v);
}