#version 410 core

uniform vec4 uColor;
uniform sampler2D uSprite;

in vec2 vUV;

out vec4 FragColor;

void main()
{
	vec4 sprite_color = texture(uSprite, vUV);
	FragColor = sprite_color * uColor;
}