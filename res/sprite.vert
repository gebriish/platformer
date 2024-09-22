#version 410 core

#define PI 3.14159265359

layout (location = 0) in vec2 aPos;

uniform vec2 uOffset;
uniform vec2 uSize;
uniform float uRotation;
uniform float uAspectRatio;

float toRadians(float degrees) {
	return degrees * PI/180.0;
}

void main()
{
	vec2 p = aPos * uSize;

	float s = sin(toRadians(uRotation));
	float c = cos(toRadians(uRotation));

	vec2 pr = vec2(p.x * c - p.y * s, p.y * c + p.x * s) + uOffset;

	gl_Position = vec4(pr / vec2(uAspectRatio, 1.0), 0.0, 1.0);
}
