// For precompiled headers
#include "stdafx.h"

// OpenGl, GLFW, and GLM library inclusions
#define GLEW_STATIC					// Use static GLEW libraries
#include "glew.h"					// GL Extension Wrangler
#include "glfw3.h"					// GLFW helper library
#include "glm.hpp"					// Vector types
#include "gtc/matrix_transform.hpp"	// Matrix types
#include "gtc/type_ptr.hpp"			// Pointers to the above types
#include "gtc/constants.hpp"		// Various constants

// Standard library inclusions
#include <iostream>
#include <vector>

// Project file inclusions
#include "camera.h"
#include "hermitepolynomial.h"
#include "polyline.h"
#include "hermitespline.h"
#include "shaders.h"

// Function prototypes
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void initialize();
void loadShaders();
std::vector<GLfloat> flatten(const std::vector<glm::vec3> vertices);

// Shader paths
const std::string vertexShaderPath = "vertexShader.vs";
const std::string fragmentShaderPath = "fragmentShader.fs";

// Global variables
GLFWwindow *window;	// Pointer to OpenGL window object
GLuint shaderProgram;
GLuint VAO, VBO, EBO;

int main() try
{
	// TEST
	glm::vec3 p1(-1.0f, -1.0f, 0.0f);
	glm::vec3 p2(0.0f, 1.0f, 0.0f);
	glm::vec3 p3(-1.0f, 1.0f, 0.0f);

	glm::vec3 t1(1.0f, 0.0f, 0.0f);
	glm::vec3 t2(0.5f, 0.5f, 0.0f);
	glm::vec3 t3(0.0f, 1.0f, 0.0f);

	std::vector<glm::vec3> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);

	std::vector<glm::vec3> tangents;
	tangents.push_back(t1);
	tangents.push_back(t2);
	tangents.push_back(t3);

	HermiteSpline spline(points, tangents);
	auto polyline = spline.polyline();
	// END TEST

	auto coordinates = flatten(polyline.points());
	auto indices = polyline.indices();

	initialize();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates[0]) * coordinates.size(), &coordinates[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

    return 0;
}

catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
	exit(0);
}

void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	default:
		break;
	}
}

void initialize()
{
	glfwInit();

	window = glfwCreateWindow(800, 600, "COMP 371 - Assignment 2", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW." << std::endl;
		exit(0);
	}

	glViewport(0, 0, 800, 600);

	shaderProgram = makeShaderProgram(vertexShaderPath, fragmentShaderPath);
}

void loadShaders()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
}

std::vector<GLfloat> flatten(const std::vector<glm::vec3> vertices)
{
	std::vector<GLfloat> coordinates;
	for (auto vertex : vertices)
	{
		coordinates.push_back(vertex.x);
		coordinates.push_back(vertex.y);
		coordinates.push_back(vertex.z);
	}
	return coordinates;
}