#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include <map>

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::map<std::string, float> noiseCache;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;
	VBO VBO;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, bool dynamic);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);

	void UpdatePosition(Camera& camera, float x, float z);
};
#endif