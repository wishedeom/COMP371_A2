#pragma once

#include "glm.hpp"
#include "glfw3.h"

// Represents a third-degree polynomial function from real numbers to real 3-vectors
class HermitePolynomial
{
	glm::vec3 m_a, m_b, m_c, m_d;	// Polynomial coefficients

public:

	// Constructor
	HermitePolynomial(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3);

	// Accessors
	auto a() const;
	auto b() const;
	auto c() const;
	auto d() const;

	// Evaluates the polynomial function with the given parameter
	glm::vec3 evaluate(const GLfloat u) const;

};