#pragma once
#include <math/vec2.h>
#include <graphics/color.h>


struct SpriteVertex
{
	vec2 	position;
	vec4 	color;
	vec2 	texcoord;
};

struct Sprite
{
	vec2 position{0.0};
	vec2 size{1.0};
	vec2 offset{0.0, 0.0};
	float rotation = 0.0;
	
	Color color = {0xff, 0xff, 0xff, 0xff};
	vec2 texture_coord_min{0.0};
	vec2 texture_coord_max{1.0};
};