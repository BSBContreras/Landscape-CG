#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 Normal;
smooth out vec3 color;

void main()
{
	Normal = aNormal;
	color = aColor;
		
	gl_Position = vec4(aPos, 1.0);
}