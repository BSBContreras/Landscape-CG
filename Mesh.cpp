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
		if (vertex.position.y < 0.05) {
			vertex.position.y /= 10;
		}

		float waterHeight = 0.05;

		// Deep water
		if (vertex.position.y < waterHeight * 0.5) {
			vertex.color.r = 60.0f / 255; vertex.color.g = 95.0f / 255.0f; vertex.color.b = 190.0f / 255.0f;
		}
		// Shallow water
		if (vertex.position.y >= waterHeight * 0.5 && vertex.position.y < waterHeight) {
			vertex.color.r = 60.0f / 255; vertex.color.g = 100.0f / 255.0f; vertex.color.b = 190.0f / 255.0f;
		}
		// Sand
		if (vertex.position.y >= waterHeight && vertex.position.y < 0.25) {
			vertex.color.r = 210.0f / 255; vertex.color.g = 215.0f / 255.0f; vertex.color.b = 130.0f / 255.0f;
		}
		// Grass 1
		if (vertex.position.y >= 0.25 && vertex.position.y < 0.60) {
			vertex.color.r = 95.0f / 255; vertex.color.g = 165.0f / 255.0f; vertex.color.b = 30.0f / 255.0f;
		}
		// Grass 2
		if (vertex.position.y >= 0.60f && vertex.position.y < 1.0f) {
			vertex.color.r = 65.0f / 255; vertex.color.g = 115.0f / 255.0f; vertex.color.b = 20.0f / 255.0f;
		}
		// Rock 1
		if (vertex.position.y >= 1.0f && vertex.position.y < 1.5f) {
			vertex.color.r = 90.0f / 255; vertex.color.g = 65.0f / 255.0f; vertex.color.b = 60.0f / 255.0f;
		}
		// Rock 2
		if (vertex.position.y >= 1.5f && vertex.position.y < 2.0f) {
			vertex.color.r = 75.0f / 255; vertex.color.g = 60.0f / 255.0f; vertex.color.b = 55.0f / 255.0f;
		}
		// Snow
		if (vertex.position.y >= 2.0f) {
			vertex.color.r = 255.0f / 255; vertex.color.g = 255.0f / 255.0f; vertex.color.b = 255.0f / 255.0f;
		}
	}

	VBO.UpdateMesh(vertices);
}

glm::vec3 Mesh::getTerrainColor(float y) {
	float waterHeight = 0.05;
	return glm::vec3(60 / 255, 95 / 255, 190 / 255);
	// Deep water
	if (y < waterHeight * 0.5) {
		return glm::vec3(60/255, 95/255, 190/255);
	}
	// Shallow water
	if (y >= waterHeight * 0.5 && y < waterHeight) {
		return glm::vec3(60/255, 100/255, 190/255);
	}
	// Sand
	if (y >= waterHeight && y < 0.15) {
		return glm::vec3(210/255, 215/255, 130/255);
	}
	// Grass 1
	if (y >= waterHeight && y < 0.30) {
		return glm::vec3(95/255, 165/255, 30/255);
	}
	// Grass 2
	if (y >= 0.30 && y < 0.40) {
		return glm::vec3(65/255, 115/255, 20/255);
	}
	// Rock 1
	if (y >= 0.40 && y < 0.50) {
		return glm::vec3(90/255, 65/255, 60/255);
	}
	// Rock 2
	if (y >= 0.50 && y < 15.0f) {
		return glm::vec3(75/255, 60/255, 55/255);
	}
	// Snow
	if (y >= 15.0f) {
		return glm::vec3(255/255, 255/255, 255/255);
	}
}