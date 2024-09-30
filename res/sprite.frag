#version 410 core


uniform vec4 uColor;

in vec2 vUV;

out vec4 FragColor;

void main()
{
	FragColor = vec4(uColor);
}
