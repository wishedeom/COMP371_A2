#pragma once

#include <vector>
#include "glm.hpp"
#include "glfw3.h"
#include "hermitepolynomial.h"

// Represents a polyline
class Polyline
{
	std::vector<glm::vec3> m_points;

public:
	std::vector<glm::vec3> points() const;
	std::vector<GLuint> indices() const;
	void pushSegment(const HermitePolynomial);
};


