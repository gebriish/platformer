#version 410 core
layout (location = 0) in vec3 aPos;

uniform float uAspectRatio;

void main()
{
	gl_Position = vec4(aPos, 1.0)/vec4(uAspectRatio, 1.0, 1.0, 1.0);
}