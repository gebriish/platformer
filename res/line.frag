#version 410 core

in vec2 vPos;
in vec4 vColor;

out vec4 FragColor;

void main()
{
	FragColor = vColor;
}