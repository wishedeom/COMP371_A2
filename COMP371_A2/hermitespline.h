#pragma once

#include <vector>
#include "hermitepolynomial.h"
#include "polyline.h"


// Represents a connected, C1-smooth curve made from the union of several cubic polynomial segments
class HermiteSpline
{
	std::vector<HermitePolynomial> m_segments;

public:

	// Constructor
	HermiteSpline(const std::vector<glm::vec3> points, const std::vector<glm::vec3> tangents);

	// Accessor
	auto segments() const;

	// Returns a polyline approximation of the spline
	Polyline polyline() const;

};