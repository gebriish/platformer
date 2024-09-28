#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec4 vCol;
out vec2 vUV;

uniform vec2 uResolution;

void main()
{
	vUV  = aTexCoord;
	vCol = aCol; 

	vec2 p = aPos;
	gl_Position = vec4(p * 2/ uResolution , 0.0, 1.0);
}
