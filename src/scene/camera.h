#pragma once
#include <math/vec2.h>

struct Camera2D
{
	vec2 position{0.0, 0.0};
	vec2 size{512, 512};
	float scale = 1.0;

	vec2 screenToWorld(float x, float y) const
	{
		vec2 corner = this->position - this->size * this->scale * 0.5;
		return corner + vec2(x, y) * scale;
	}
};
