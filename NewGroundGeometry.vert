#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 Normal[];
in vec3 color[];

out vec3 crntPosO;
out vec3 NormalO;
smooth out vec3 colorO;

uniform mat4 camMatrix;
uniform mat4 model;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {
	vec3 normal = GetNormal();

	vec4 vertexPos = gl_in[0].gl_Position;
	crntPosO = vec3(vertexPos[0], vertexPos[1], vertexPos[2]);
	gl_Position = camMatrix * model * vertexPos;
	colorO = color[0];
	NormalO = normal;
	EmitVertex();

	vertexPos = gl_in[1].gl_Position;
	gl_Position = camMatrix * model * vertexPos;
	colorO = color[1];
	NormalO = normal;
	EmitVertex();

	vertexPos = gl_in[2].gl_Position;
	gl_Position = camMatrix * model * vertexPos;
	colorO = color[2];
	NormalO = normal;
	EmitVertex();

	EndPrimitive();
}