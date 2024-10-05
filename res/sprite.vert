#version 410 core
layout (location = 0) in vec2 aPos;

uniform vec2 uPosition;
uniform vec2 uSize;

uniform vec2 uUVMin;
uniform vec2 uUVMax;

uniform vec2 uResolution;
uniform vec2 uCamera;



out vec2 vUV;

void main()
{
	vUV = (aPos + 0.5f) * (uUVMax - uUVMin) + uUVMin;

	vec2 position = aPos * uSize + uPosition - uCamera;
	position = position * 2.0 / uResolution;
	
	gl_Position = vec4(position, 0.0, 1.0);
}