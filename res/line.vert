#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec2 vPos;
out vec4 vColor;

uniform struct {
	vec2 position;
	vec2 size;
} uCamera;

void main()
{
	vec2 position = aPos;

	vColor = aCol;
	vPos = position;
	
	position -= uCamera.position;
	position /= uCamera.size * 0.5;

	gl_Position = vec4(position, 0.0, 1.0);
}