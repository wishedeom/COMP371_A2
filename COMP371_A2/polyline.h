#pragma once

#include <vector>
#include "glm.hpp"
#include "glfw3.h"
#include "hermitepolynomial.h"

// Represents a polyline
class Polyline
{
	std::vector<glm::vec3> m_points;
	std::vector<GLuint> m_indices;
	GLuint VAO, VBO, EBO;
	bool lines; // True if drawing as lines, false if as points

public:
	Polyline();
	std::vector<glm::vec3> points() const;
	std::vector<GLuint> indices() const;
	void pushSegment(const HermitePolynomial& p);
	void draw() const;
	void setLines();
	void setPoints();
};


