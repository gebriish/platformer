#pragma once
#include <math/vec2.h>

struct Camera2D
{
	vec2 position{0.0, 0.0};
	vec2 size{512, 512};
	float scale = 1.0;
};
