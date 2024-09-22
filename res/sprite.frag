#version 410 core

uniform vec4 uColor;

out vec4 FragColor;

void main()
{
	vec4 color = uColor/255.0;
	FragColor = vec4(color);
}
