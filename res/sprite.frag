#version 410 core
out vec4 FragColor;

uniform sampler2D uSprite;
uniform vec4 uColor;

in vec2 vUV;

void main()
{
	vec4 sprite_color = texture(uSprite, vUV);
	FragColor = uColor * sprite_color;
}