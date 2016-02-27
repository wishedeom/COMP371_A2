#pragma once

#include "glfw3.h"
#include "glm.hpp"
#include <vector>
#include "polyline.h"

// Represensts an isosceles triangle
class Triangle
{
	// Vertices
	glm::vec4 lowerLeft;
	glm::vec4 lowerRight;
	glm::vec4 top;

	// Dimensions
	GLfloat m_length;
	GLfloat m_width;

	// Position and orientation
	glm::vec3 m_centre;
	glm::vec3 m_orientation;

	// For drawing
	std::vector<GLfloat> coordinates;
	GLuint VAO, VBO;

public:
	Triangle(const GLfloat length, const GLfloat width, const glm::vec3 centre, const glm::vec3 orientation);
	void set(const glm::vec3 centre, const glm::vec3 orientation);
	void orient(const glm::vec3 start, const glm::vec3 end);
	void snapTo(const Polyline& polyline, const int segment);
	void draw() const;
};

// Helper functions
GLfloat angle(const glm::vec3 orientation, const glm::vec3 reference);
GLfloat signum(const GLfloat x);