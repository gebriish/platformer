#version 410 core

layout (location = 0) in vec2 aPos;

out vec2 vUV;

uniform vec2 uResolution;
uniform vec2 uCamera;
uniform vec2 uSize;
uniform vec2 uOffset;
uniform vec2 uPosition;

uniform vec2 uUV0;
uniform vec2 uUV1;


void main()
{
	vUV  = (aPos + 0.5f) * (uUV1 - uUV0) + uUV0;

	vec2 p = (aPos * uSize)- uOffset + uPosition - uCamera;
	gl_Position = vec4(p * 2 / uResolution, 0.0, 1.0);
}
