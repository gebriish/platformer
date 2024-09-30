#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 vUV;

uniform vec2 uResolution;
uniform vec2 uCamera;
uniform vec2 uSize;
uniform vec2 uOffset;
uniform vec2 uPosition;

void main()
{
	vUV  = aUV;

	vec2 p = (aPos * uSize)- uOffset + uPosition - uCamera;
	gl_Position = vec4(p * 2 / uResolution, 0.0, 1.0);
}
