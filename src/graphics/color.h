#pragma once
#include <cstdint>

struct Color 
{
	uint8_t r, g, b, a;
};

Color color_mix(const Color& a, const Color& b, float t);
Color color_from_hexcode(const char hexcode[6]);