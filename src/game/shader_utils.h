#pragma once

#include <graphics/shader.h>
#include <scene/camera2d.h>

void shader_upload_camera2d_data(const Shader& shader, const Camera2D &camera)
{
	shader_upload_vec2(shader, "uCamera.position", camera.position.x, camera.position.y);
	shader_upload_vec2(shader, "uCamera.size", camera.size.x * camera.scale, camera.size.y * camera.scale);
}