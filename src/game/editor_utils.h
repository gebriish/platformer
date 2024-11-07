#pragma once
#include <math/vec2.h>
#include <graphics/line_batch2d.h>
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

inline float nearest_grid(float x, unsigned int grid_size)
{
	return nearest_grid_floor(x + grid_size * 0.5, grid_size);
}

inline vec2 nearest_grid(vec2 point, unsigned int grid_size)
{
	return {nearest_grid(point.x, grid_size), nearest_grid(point.y, grid_size)};
}


void add_editor_line(LineBatch2d *batch, const Shader& shader,const Camera2D& camera, const Line2d &line)
{
	if(!batch->addLine(line))
	{
		batch->endBatch();

		use_shader_program(shader);
		shader_upload_camera2d_data(shader, camera);
		batch->drawBatch();

		batch->beginBatch();
		batch->addLine(line);
	}
}

void add_editor_box(LineBatch2d *batch, const Shader& shader,const Camera2D& camera, const vec2& pos, const vec2& size, Color c)
{
	add_editor_line(batch, shader, camera, Line2d{pos - size * 0.5, pos + vec2(-size.x, size.y) * 0.5, c});
	add_editor_line(batch, shader, camera, Line2d{pos + vec2(-size.x, size.y) * 0.5, pos + size * 0.5, c});
	add_editor_line(batch, shader, camera, Line2d{pos - size * 0.5, pos + vec2( size.x,-size.y) * 0.5, c});
	add_editor_line(batch, shader, camera, Line2d{pos + vec2( size.x,-size.y) * 0.5, pos + size * 0.5, c});
}