#version 410 core
layout (location = 0) in vec2 aPos;

uniform vec2 uPosition;
uniform vec2 uSize;

uniform vec2 uViewport;

out vec2 vPosition;

void main()
{
	vec2 position = aPos * uSize + uPosition;
	vPosition = position;

	position /= uViewport;
	position = position * 2.0f - 1.0;

	gl_Position = vec4(position, 0.0f, 1.0f);
}