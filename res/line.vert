#version 410 core
layout (location = 0) in vec2 aPos;

struct Camera 
{
	vec2 position;
	vec2 resolution; 
};

uniform Camera uCamera;

uniform vec2 uBegin;
uniform vec2 uEnd;

void main()
{
	vec2 pixel_coordinate = (aPos * (uEnd - uBegin)) + uBegin - uCamera.position;
	pixel_coordinate = pixel_coordinate * 2.0 / uCamera.resolution;

	gl_Position = vec4(pixel_coordinate, 0.0f, 1.0f);
}