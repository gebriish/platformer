#pragma once
#include <math/vec2.h>
#include <cmath>

inline float nearest_grid_floor(float x, unsigned int grid_size)
{
	return std::floor(x/grid_size) * grid_size;
}	

inline vec2 nearest_grid_floor(vec2 point, unsigned int grid_size)
{
	return {nearest_grid_floor(point.x, grid_size), nearest_grid_floor(point.y, grid_size)};
}

inline float nearest_grid_ceil(float x, unsigned int grid_size)
{
	return std::ceil(x/grid_size) * grid_size;
}

inline vec2 nearest_grid_ceil(vec2 point, unsigned int grid_size)
{
	return {nearest_grid_ceil(point.x, grid_size), nearest_grid_ceil(point.y, grid_size)};
}