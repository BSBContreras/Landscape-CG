#include"Mesh.h"

const unsigned int width = 800;
const unsigned int height = 800;





Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

float func(float x, float z)
{
	return (x * x - 5 * x + 5) * 0.01f - (z * z - 5 * z + 5) * 0.01f;
}

float smoothstep(float a, float b, float x)
{
	if (x < a) return 0.0f;
	if (x > b) return 1.0f;
	float ir = 1.0f / (b - a);
	x = (x - a) * ir;
	return x * x * (3.0 - 2.0 * x);
}

float smoothstepD(float a, float b, float x)
{
	if (x < a) return 0.0;
	if (x > b) return 0.0;
	float ir = 1.0f / (b - a);
	x = (x - a) * ir;
	return 6.0 * x * (1.0 - x) * ir;
}

float terrainMap(float x, float z)
{
	float a = 10.0f;
	float b = 5.0f;
	float c = 1.0f;
	float d = 0.0f;
	return
		(
			a +
			(b - a) * smoothstep(0, 1, x) +
			(c - a) * smoothstep(0, 1, z) +
			(a - b - c - d) * smoothstep(0, 1, x) * smoothstep(0, 1, z)
			);
}

float simpleTerrainMap(float x, float z)
{
	return (x * x - 5 * x + x) * 0.05f + z * 0.2;
}

int main()
{

	std::vector <Vertex> groundVertices;
	glm::vec3 colorGround = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 normalGround = glm::vec3(1.0f, 1.0f, 1.0f);
	int groundSize = 100;
	for (int i = 0; i < groundSize; i++)
		for (int j = 0; j < groundSize; j++) 
		{
			float x = i * 0.2f;
			float z = j * 0.2f;
			groundVertices.push_back(Vertex{ glm::vec3(x, simpleTerrainMap(x, z), z), normalGround, colorGround });
		}

	// Indices for vertices order
	std::vector <GLuint> groundIndices;
	for (int i = 0; i < (groundSize * groundSize); i++)
	{
		if ((i % groundSize + 1) == groundSize) continue;
		if (i + groundSize >= (groundSize * groundSize)) continue;
		groundIndices.push_back(i);
		// std::cout << "p1: " << i << ", ";
		groundIndices.push_back(i + 1);
		// std::cout << "p2: " << i + 1 << ", ";
		groundIndices.push_back(i + groundSize);
		// std::cout << "p3: " << i + groundSize << "\n";;
	}

	for (int i = (groundSize * groundSize) - 1; i >= 0; i--)
	{
		if ((i % groundSize) == 0) continue;
		if ((i - groundSize) < 0) continue;
		groundIndices.push_back(i);
		// std::cout << "p1: " << i << ", ";
		groundIndices.push_back(i - 1);
		// std::cout << "p2: " << i - 1 << ", ";
		groundIndices.push_back(i - groundSize);
		// std::cout << "p3: " << i - groundSize << "\n";;
	}

	/*
	for (int i = 0; i < (groundSize * groundSize); i++)
	{
		std::cout << "V: " << i << ", ";
		std::cout << "R: " << groundVertices[i].color.r << ", ";
		std::cout << "G: " << groundVertices[i].color.g << ", ";
		std::cout << "B: " << groundVertices[i].color.b << "\n";;
	}
	*/

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	Shader groundShader("ground.vert", "ground.frag");
	Mesh ground(groundVertices, groundIndices);


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Crate light mesh
	Mesh light(lightVerts, lightInd);



	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 groundPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 groundModel = glm::mat4(1.0f);
	groundModel = glm::translate(groundModel, groundPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	groundShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(groundShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(groundModel));
	glUniform4f(glGetUniformLocation(groundShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(groundShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Normalize speed interval
	glfwSwapInterval(1);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Draws different meshes
		ground.Draw(groundShader, camera);
		light.Draw(lightShader, camera);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	groundShader.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}