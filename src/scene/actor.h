#pragma once
#include <cstdint>

#include <math/vec2.h>
#include <graphics/texture2d.h>


class Actor
{
	vec2 position;
	vec2 size;
	uint16_t texture_id;
};