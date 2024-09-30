#version 410 core


uniform vec4 uColor;
uniform sampler2D uSprite;


in vec2 vUV;

out vec4 FragColor;

void main()
{
	FragColor = texture(uSprite, vUV) * uColor;
}
