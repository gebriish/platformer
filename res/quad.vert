#version 410 core
layout (location=0) in vec2 aPos;

struct Camera 
{
	vec2 position;
	vec2 resolution; 
};

struct Sprite
{
	vec2 position;
	vec2 size;
};



uniform vec2 uUVmin;
uniform vec2 uUVmax;

uniform Sprite uSprite;
uniform Camera uCamera;

out vec2 vUV;

void main()
{
	vec2 pixel_coordinate = (aPos * uSprite.size) + uSprite.position  - uCamera.position;
	pixel_coordinate = pixel_coordinate * 2.0f / uCamera.resolution;

	vUV = aPos * (uUVmax - uUVmin) + uUVmin;

	gl_Position = vec4(pixel_coordinate, 0.0f, 1.0f);
}
