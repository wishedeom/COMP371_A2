// ----------------------------------------------------------------------------
//
//							COMP 371 - COMPUTER GRAPHICS
//									ASSIGNMENT 2
//								CONCORDIA UNIVERSITY
//
//								Author: Michael Deom
//						  Submission Date: March 1, 2016
//
// ----------------------------------------------------------------------------


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

// C libraries
#include <climits>

// Project file inclusions
#include "hermitepolynomial.h"
#include "polyline.h"
#include "hermitespline.h"
#include "shaders.h"
#include "vector_constants.h"
#include "point_collector.h"
#include "flatten.h"
#include "triangle.h"
#include "vec3_to_string.h"

// Function prototypes
void initialize();
void keyCallback(const GLFWwindow *window, const int key, const int scancode, const int action, const int mods);
void windowSizeCallback(const GLFWwindow* window, const int width, const int height);
glm::vec3 windowToWorldCoords(const glm::vec2 p);


//----------------------------- CONSTANTS -----------------------------
// Shader paths
const std::string vertexShaderPath   = "vertexShader.vs";
const std::string fragmentShaderPath = "fragmentShader.fs";

// Initial window dimensions
const GLsizei WIDTH  = 800;
const GLsizei HEIGHT = 800;

// Control
const GLfloat controlSensitivity = 0.1f;

// Triangle speed
const int initialSpeed = 50;
const int speedIncremenet = 5;
//----------------------------------------------------------------------


//----------------------------- GLOBAL VARIABLES ----------------------
GLFWwindow* window;		// Pointer to OpenGL window objects
Shader shader;			// Shader program object

// Transformation matrices
glm::mat4 viewMatrix;
glm::mat4 modelMatrix;
glm::mat4 projMatrix;
glm::mat4 transformationMatrix;

// To hold user-provided points
PointCollector* p_pointCollector;

// Polyline
Polyline* p_polyline;

// Triangle speed
int triangleSpeed = initialSpeed;

// Done collecting points
bool doneCollecting = false;

// True for collecting points, false for drawing splines
bool collectMode = true;

bool reset = false;
//----------------------------------------------------------------------


//------------------------- MAIN ---------------------------------------

int main() try
{
	initialize();	// Set up OpenGL context

	std::cout << "Please enter the number of points to interpolate: (>1)";
	int numPoints = 0;
	while (numPoints <= 1)
	{
		std::cin >> numPoints;
	}

	p_pointCollector = new PointCollector(numPoints);

	Polyline polyline(true);
	p_polyline = &polyline;

	int i = 0;

	Triangle triangle(0.1f, 0.05f, origin, up);

	while (!glfwWindowShouldClose(window))
	{
		if (reset)	// For resetting the program
		{
			reset = false;
			std::cout << "Please enter the number of points to interpolate: (>1)";
			int numPoints = 0;
			while (numPoints <= 1)
			{
				std::cin >> numPoints;
			}
			delete p_pointCollector;
			p_pointCollector = new PointCollector(numPoints);
		}

		// Pre-draw preparation
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program and pass the three transformation matrices to the shader program
		transformationMatrix = projMatrix * viewMatrix * modelMatrix;
		shader.use(transformationMatrix);

		// Check to see if there are enough points to create a spline
		if (p_pointCollector->isFull() || doneCollecting)
		{
			if (p_pointCollector->hasMinNumPoints())
			{
				polyline = p_pointCollector->hermiteSpline().polyline();
				collectMode = false;
			}
			else
			{
				doneCollecting = false;
			}
		}

		if (collectMode)	// While collecting
		{
			p_pointCollector->draw();
		}
		else				// After collecting
		{
			polyline.draw();
			triangle.snapTo(polyline, i);
			i = (i + triangleSpeed) % INT_MAX;
			triangle.draw();
		}

		glfwSwapBuffers(window);	// Swap buffers
	}

	// End program
	glfwTerminate();
	delete p_pointCollector;
    return 0;
}
catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
	exit(0);
}


// Manages keyboard input
void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);	// Escape key exits the application
		break;
	case GLFW_KEY_BACKSPACE:	// Backspace resets
		reset = true;
		collectMode = true;
		break;
	case GLFW_KEY_ENTER:	// Enter prematurely ends point collection
		doneCollecting = true;
		break;
	case GLFW_KEY_LEFT:	// Arrow keys translate camera
		viewMatrix = glm::translate(viewMatrix, - controlSensitivity * left);
		break;
	case GLFW_KEY_RIGHT:
		viewMatrix = glm::translate(viewMatrix, - controlSensitivity * right);
		break;
	case GLFW_KEY_UP:
		viewMatrix = glm::translate(viewMatrix, -controlSensitivity * up);
		break;
	case GLFW_KEY_DOWN:
		viewMatrix = glm::translate(viewMatrix, -controlSensitivity * down);
		break;
	case GLFW_KEY_EQUAL: // Plus and minus increase and decrease triangle speed
		if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL)
		{
			triangleSpeed += speedIncremenet;
		}
		break;
	case GLFW_KEY_MINUS:
		if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL)
		{
			triangleSpeed -= speedIncremenet;
		}
		break;
	case GLFW_KEY_P:	// P and L set point/line draw mode
		p_polyline->setPoints();
		break;
	case GLFW_KEY_L:
		p_polyline->setLines();
		break;
	default:
		break;
	}
}


// Manages mouse click input
void mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods)
{
	switch (button)
	{
	case (GLFW_MOUSE_BUTTON_LEFT):
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			if (!p_pointCollector->isFull())
			{
				p_pointCollector->collectPoint(windowToWorldCoords(glm::vec2(x, y)));
			}
			else
			{
				std::cout << "Full\n";
			}
		}
		break;
	default:
		break;
	}
}


// Manages window resizing
void windowSizeCallback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


// Performs OpenGL set-up
void initialize()
{
	// Initialize GLFW
	glfwInit();

	// Create window and check for errors
	window = glfwCreateWindow(WIDTH, HEIGHT, "COMP 371 - Assignment 2", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
	}

	// Make the window the current context
	glfwMakeContextCurrent(window);

	// Register callback functions
	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, windowSizeCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	// Initialize GLEW and check for errors
	glewExperimental = GL_TRUE;	// Required for latest version of GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW." << std::endl;
		exit(0);
	}

	// Compile and link the shaders into a shader program
	shader = Shader(vertexShaderPath, fragmentShaderPath);

	glPointSize(2.f);
}

// Converts a point in window coordinates to world coordinates
glm::vec3 windowToWorldCoords(const glm::vec2 p)
{
	// Get window dimensions
	int w, h;
	glfwGetWindowSize(window, &w, &h);

	// Transform to camera coordinates; we assume the z-coordinate to be 0
	const GLfloat cameraX = 2 * p.x / w - 1;
	const GLfloat cameraY = -(2 * p.y / h - 1);

	// Transform to world coordinates by inverting the transformation matrix
	return glm::vec3(glm::inverse(transformationMatrix) * glm::vec4(cameraX, cameraY, 0.0f, 1.0f));
}