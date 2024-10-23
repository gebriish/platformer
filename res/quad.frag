#version 410 core

in vec2 vPosition;

uniform vec2 uPosition;
uniform vec2 uSize;
uniform vec2 uViewport;

uniform vec4 uColor;


out vec4 FragColor;


float f(float x, float r, float w)
{
	return (abs(x - (w - r)) + abs(x + (w - r)))/2 - (w - r);
}

void main()
{
	vec2 coordinate = vPosition - uPosition;
	float radius = 32.0;

	float length = length(vec2(f(coordinate.x - uSize.x/2, radius, uSize.x/2), f(coordinate.y - uSize.y/2, radius, uSize.y/2)))/(radius+1/radius);
	float mask = 1 - smoothstep(1.0 - 1.414/radius, 1.0, length);

	FragColor = vec4(uColor.rgb, uColor.a * mask);

}