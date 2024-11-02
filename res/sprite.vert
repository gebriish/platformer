#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec2 vPos;
out vec2 vTexCoords;
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
	vTexCoords = aTexCoord;

	position -= uCamera.position;
	position /= uCamera.size/2.0;

	gl_Position = vec4(position, 0.0, 1.0);
}