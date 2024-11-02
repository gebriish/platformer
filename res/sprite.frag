#version 410 core

in vec2 vPos;
in vec2 vTexCoords;
in vec4 vColor;

uniform float uDebugMix;
uniform sampler2D uAlbedo;

out vec4 FragColor;

void main()
{
	vec2 size = textureSize(uAlbedo, 0);
	FragColor = mix(texture(uAlbedo, vTexCoords/size) * vColor, vec4(0, 1, 0, 1), uDebugMix);
}