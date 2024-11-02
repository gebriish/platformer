#version 410 core

in vec2 vPosition;

uniform float uRadius;
uniform vec2 uPosition;
uniform vec2 uSize;
uniform vec2 uViewport;

uniform vec4 uColor;

out vec4 FragColor;


float f(float x, float r, float w)
{
	return (abs(x - (w - r)) + abs(x + (w - r)))/2 - (w - r);
}

float outline_dist(vec2 coordinate, vec2 size, float radius)
{
	return length(vec2(f(coordinate.x - size.x/2, radius, size.x/2), f(coordinate.y - size.y/2, radius, size.y/2)));
}

void main()
{
	vec2 coordinate = vPosition - uPosition;

	float length = outline_dist(coordinate, uSize, uRadius);
	float mask         = smoothstep(uRadius + 0.5,uRadius - 0.5, length);
	float outline_mask = smoothstep(uRadius - 0.5 - 1, uRadius + 0.5 - 1, length);
	
	FragColor = vec4(uColor.rgb, uColor.a * mask);
}