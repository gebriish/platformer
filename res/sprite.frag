#version 410 core

in vec4 vCol;
in vec2 vUV;

out vec4 FragColor;

void main()
{
	FragColor = vec4(vCol);
}
