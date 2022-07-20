#include "Mesh.h"
#include "Noise.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, bool dynamic)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO.Setup(vertices, dynamic);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();

	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::UpdatePosition(Camera& camera, float x, float z)
{
	for (Vertex& vertex : vertices) {
		vertex.position.y = perlin((vertex.position.x + camera.GroundPosition.x) * 0.2, (vertex.position.z + camera.GroundPosition.z) * 0.2) * 5;
		vertex.color.r = vertex.position.y > 2.0f ? 1.0f : 0.8f;
		vertex.color.g = vertex.position.y > 1.5f ? 1.0f : 0.8f;
		vertex.color.b = vertex.position.y > 1.0f ? 1.0f : 0.8f;
	}

	VBO.UpdateMesh(vertices);
}