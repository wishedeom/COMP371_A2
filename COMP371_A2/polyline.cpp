#include "stdafx.h"
#include "polyline.h"

// Accessor
std::vector<glm::vec3> Polyline::points() const { return m_points; }

std::vector<GLuint> Polyline::indices() const
{
	std::vector<GLuint> indexVector;
	for (int i = 0; i < indexVector.size() - 1; i++)
	{
		indexVector.push_back(i);
		indexVector.push_back(i + 1);
	}
	return indexVector;
}

// Adds a polyline approximation of a single Hermite polynomial segment to the polyline
void Polyline::pushSegment(const HermitePolynomial p)
{
	const GLfloat uStep = 0.1f;
	for (GLfloat u = 0.0f; u <= 1.0f; u += uStep)
	{
		m_points.push_back(p.evaluate(u));
	}
}